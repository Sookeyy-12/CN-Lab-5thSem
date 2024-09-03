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

    // Define the server address
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = inet_addr("127.0.0.1"),  // Server is running on localhost
    };

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server\n");

    // Send two strings to the server
    char str1[1024] = "hello";
    char str2[1024] = "hello";

    send(sockfd, str1, strlen(str1) + 1, 0);
    send(sockfd, str2, strlen(str2) + 1, 0);

    printf("Strings sent to server\n");

    // Close the socket
    close(sockfd);

    return 0;
}
