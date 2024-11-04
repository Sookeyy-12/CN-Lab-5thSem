#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8080
#define BACKLOG 5  // Maximum pending connections
#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024
#define IP_ADDRESS "192.168.233.203"

// Link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

typedef struct {
    SOCKET socket;
    int client_number;
} Client;

void handle_client_message(Client *clients, int client_index, fd_set *all_fds) {
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(clients[client_index].socket, buffer, sizeof(buffer), 0);
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            printf("Client %d disconnected\n", clients[client_index].client_number);
        }
        closesocket(clients[client_index].socket);
        FD_CLR(clients[client_index].socket, all_fds);
        clients[client_index].socket = INVALID_SOCKET;
    } else {
        buffer[bytes_read] = '\0';
        printf("client_%d: %s\n", clients[client_index].client_number, buffer);
        if (strcmp(buffer, "logout") == 0) {
            printf("Client %d requested logout\n", clients[client_index].client_number);
            closesocket(clients[client_index].socket);
            FD_CLR(clients[client_index].socket, all_fds);
            clients[client_index].socket = INVALID_SOCKET;
        } else {
            // Broadcast the message to all other clients
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (i != client_index && clients[i].socket != INVALID_SOCKET) {
                    send(clients[i].socket, buffer, bytes_read, 0);
                }
            }
        }
    }
}

int main() {
    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    SOCKET server_socket;
    int max_fd, activity;
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = inet_addr(IP_ADDRESS),
    };
    struct sockaddr_in clientAddr;
    int addrlen = sizeof(clientAddr);
    fd_set read_fds, all_fds;

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    // Bind the socket to the specified port
    int isBind = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (isBind == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    } else {
        printf("Bind successful\n");
    }

    // Listen for incoming connections
    int isListen = listen(server_socket, BACKLOG);
    if (isListen == SOCKET_ERROR) {
        printf("Listening failed: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    } else {
        printf("Listening for connections...\n");
    }

    // Initialize the fd sets
    FD_ZERO(&all_fds);
    FD_SET(server_socket, &all_fds);
    max_fd = (int)server_socket;

    Client clients[MAX_CLIENTS] = {0};
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clients[i].socket = INVALID_SOCKET;
    }

    int client_count = 0;

    while (1) {
        read_fds = all_fds;

        // Monitor sockets for activity using select
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity == SOCKET_ERROR) {
            printf("Select error: %d\n", WSAGetLastError());
            break;
        }

        // Check for new incoming connection
        if (FD_ISSET(server_socket, &read_fds)) {
            SOCKET client_socket = accept(server_socket, (struct sockaddr*)&clientAddr, &addrlen);
            if (client_socket == INVALID_SOCKET) {
                printf("Accept failed: %d\n", WSAGetLastError());
                continue;
            }
            printf("New client connected on socket %d\n", client_socket);

            // Add new socket to the list of file descriptors
            FD_SET(client_socket, &all_fds);
            if ((int)client_socket > max_fd) {
                max_fd = (int)client_socket;
            }

            // Assign client number and store client info
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].socket == INVALID_SOCKET) {
                    clients[i].socket = client_socket;
                    clients[i].client_number = ++client_count;
                    break;
                }
            }
        }

        // Check each client for incoming data
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i].socket != INVALID_SOCKET && FD_ISSET(clients[i].socket, &read_fds)) {
                handle_client_message(clients, i, &all_fds);
            }
        }
    }

    // Cleanup
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
