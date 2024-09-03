#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    // Bind the socket to a port
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Socket bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Socket binded successfully\n");

    // Listen for incoming connections
    if (listen(sockfd, 3) < 0) {
        perror("Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Listening for incoming connections...\n");

    // Accept a connection
    int newSocket;
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    newSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &addrLen);
    if (newSocket < 0) {
        perror("Accept failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted from client\n");

    // Receive the two strings from the client
    char str1[1024] = {0};
    char str2[1024] = {0};

    read(newSocket, str1, sizeof(str1));
    read(newSocket, str2, sizeof(str2));

    printf("Received String 1: %s\n", str1);
    printf("Received String 2: %s\n", str2);

    // Check if the strings are the same or different
    if (strcmp(str1, str2) == 0) {
        printf("Strings are the same\n");
    } else {
        printf("Strings are different\n");
    }

    // Close the sockets
    close(newSocket);
    close(sockfd);

    return 0;
}