#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "server.h"

#pragma comment(lib, "Ws2_32.lib")

void handle_client(SOCKET client_socket, Router *router)
{
    char buffer[1024];
    char response[1024];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0)
    {
        perror("recv failed");
        closesocket(client_socket);
        return;
    }

    buffer[bytes_received] = '\0';
    printf("Received request:\n%s\n", buffer);

    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    if (path != NULL)
    {
        path++;
    }

    handle_request(router, path, response, sizeof(response));

    send(client_socket, response, strlen(response), 0);

    closesocket(client_socket);
}

void start_server(int port, Router *router)
{
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET)
    {
        perror("Socket creation failed");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0)
    {
        perror("Listen failed");
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", port);

    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0)
        {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket, router);
    }

    closesocket(server_socket);
    WSACleanup();
}