#include "server.h"
#include "http.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>

#define BUFFER_SIZE 1048576
#define MAX_EVENTS 100

volatile bool server_running = true;

void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        server_running = false;
    }
}

void handle_request_async(int client_fd, Router *router)
{
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer)
    {
        close(client_fd);
        return;
    }

    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0)
    {
        buffer[bytes_received] = '\0';

        Request request = {0};
        if (parse_request(buffer, &request) == 0)
        {
            Response response = handle_request(router, &request);

            char http_response[BUFFER_SIZE];
            snprintf(http_response, sizeof(http_response),
                     "HTTP/1.1 %s\r\n%s\r\nContent-Length: %zu\r\n\r\n%s",
                     response.status, response.headers, strlen(response.body), response.body);

            send(client_fd, http_response, strlen(http_response), 0);

            free_response(&response);
        }
    }
    else if (bytes_received == 0)
    {
        printf("Client disconnected.\n");
    }
    else
    {
        perror("recv failed");
    }

    free(buffer);
    close(client_fd);
}

void start_server(int port, const char *ip, Router *router)
{
    int server_fd;
    struct sockaddr_in server_addr;

    signal(SIGINT, handle_signal);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation failed");
        return;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt failed");
        close(server_fd);
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
        perror("Invalid IP address");
        close(server_fd);
        return;
    }

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        return;
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        perror("epoll_create1 failed");
        close(server_fd);
        return;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1)
    {
        perror("epoll_ctl failed");
        close(epoll_fd);
        close(server_fd);
        return;
    }

    printf("Server listening on %s:%d\n", ip, port);

    struct epoll_event events[MAX_EVENTS];

    while (server_running)
    {
        int n = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int i = 0; i < n; i++)
        {
            if (events[i].data.fd == server_fd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
                if (client_fd == -1)
                {
                    perror("accept failed");
                    continue;
                }

                fcntl(client_fd, F_SETFL, O_NONBLOCK);

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1)
                {
                    perror("epoll_ctl failed");
                    close(client_fd);
                }
            }
            else
            {
                handle_request_async(events[i].data.fd, router);

                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
            }
        }
    }

    close(epoll_fd);
    close(server_fd);
    printf("Server shut down gracefully.\n");
}
