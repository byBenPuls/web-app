#include "server.h"
#include "http.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1048576

typedef struct
{
    int client_fd;
    Router *router;
} ClientArgs;

void *client_handler(void *arg)
{
    ClientArgs *client_args = (ClientArgs *)arg;
    int client_fd = client_args->client_fd;
    Router *router = client_args->router;

    free(client_args);

    char *buffer = malloc(BUFFER_SIZE);
    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0)
    {
        buffer[bytes_received] = '\0';

        Request request;
        parse_request(buffer, &request);

        Response response = handle_request(router, &request);

        char http_response[BUFFER_SIZE];
        snprintf(http_response, sizeof(http_response),
                 "HTTP/1.1 %s\r\n%s\r\nContent-Length: %zu\r\n\r\n%s",
                 response.status, response.headers, strlen(response.body), response.body);

        send(client_fd, http_response, strlen(http_response), 0);

        free_response(&response);
    }

    free(buffer);
    close(client_fd);
    return NULL;
}

void start_server(int port, const char *ip, Router *router)
{
    int server_fd;
    struct sockaddr_in server_addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
        perror("invalid IP address");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s:%d\n", ip, port);
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_fd < 0)
        {
            perror("accept failed");
            continue;
        }

        ClientArgs *client_args = malloc(sizeof(ClientArgs));
        client_args->client_fd = client_fd;
        client_args->router = router;

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, client_handler, (void *)client_args);
        pthread_detach(thread_id);
    }

    close(server_fd);
}