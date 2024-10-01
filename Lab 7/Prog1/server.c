#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 8080
#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
        if(bytes_read <= 0) {
            break;
        }
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
        if (strcmp(buffer, "logout") == 0) {
            printf("Client requested logout.\n");
            break;
        }
        send(client_socket, buffer, bytes_read, 0);
    }
    close(client_socket);
    printf("Connection closed.\n");
}

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed.\n");
    else printf("Socket Created Successfully");

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY,
    };
    struct sockaddr_in clientAddr;
    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind < 0) printf("Socket Bind Failed.\n");
    else printf("Socket Binded Successfully.\n");

    // Listen
    int isListen = listen(sockfd, MAX_CLIENTS);
    if(isListen < 0) printf("Listening Failed.\n");
    else printf("Listening for incoming connections...\n");

    // Accept and Handle Multiple Clients
    socklen_t clientAddrLen = sizeof(clientAddr);
    while(1) {
        int clientSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if(clientSocket < 0) printf("Failed to Accept Client.\n");
        else printf("Connection Established with Client.\n");
        
        handle_client(clientSocket);
    }

    // Close
    close(sockfd);
    printf("Server Closed.");

    return 0;
}