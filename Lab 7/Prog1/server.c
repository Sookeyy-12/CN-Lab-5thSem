#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>

#define PORT 8080
#define BACKLOG 5  // Maximum pending connections
#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024

void handle_client_message(int client_socket, fd_set *all_fds) {
    char buffer[BUFFER_SIZE];
    int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    // If error or client disconnects
    if (bytes_read <= 0) {
        if (bytes_read == 0) {
            printf("Client disconnected from socket %d\n", client_socket);
        } else {
            perror("recv");
        }
        close(client_socket);
        FD_CLR(client_socket, all_fds);
    } else {
        buffer[bytes_read] = '\0';  // Null-terminate the received message
        printf("Received message: %s from socket %d\n", buffer, client_socket);

        // Check for logout message
        if (strcmp(buffer, "logout") == 0) {
            printf("Client requested logout from socket %d\n", client_socket);
            close(client_socket);
            FD_CLR(client_socket, all_fds);  // Remove from set
        } else {
            // Echo the message back to the client
            send(client_socket, buffer, bytes_read, 0);
        }
    }
}

int main() {
    int server_socket, client_socket, max_fd, activity;
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY,
    };
    struct sockaddr_in clientAddr;
    socklen_t addrlen = sizeof(clientAddr);
    fd_set read_fds, all_fds;
    
    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
    }
    printf("Socket created successfully.\n");

    // Bind the socket to the specified port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
    }
    printf("Socket binded successfully.\n");

    // Listen for incoming connections
    if (listen(server_socket, BACKLOG) == -1) {
        perror("Listen failed");
        close(server_socket);
    }
    printf("Listening for incoming connections...\n");

    // Initialize the fd sets
    FD_ZERO(&all_fds);
    FD_SET(server_socket, &all_fds);
    max_fd = server_socket;

    while (1) {
        read_fds = all_fds;

        // Monitor sockets for activity using select
        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0 && errno != EINTR) {
            perror("Select error");
        }

        // Check for new incoming connection
        if (FD_ISSET(server_socket, &read_fds)) {
            client_socket = accept(server_socket, (struct sockaddr*)&clientAddr, &addrlen);
            if (client_socket < 0) {
                perror("Accept failed");
                continue;
            }
            printf("New client connected on socket %d\n", client_socket);

            // Add new socket to the list of file descriptors
            FD_SET(client_socket, &all_fds);
            if (client_socket > max_fd) {
                max_fd = client_socket;
            }
        }

        // Check each client for incoming data
        for (int i = 0; i <= max_fd; i++) {
            if (i != server_socket && FD_ISSET(i, &read_fds)) {
                handle_client_message(i, &all_fds);
            }
        }
    }

    // Cleanup
    close(server_socket);
    return 0;
}
