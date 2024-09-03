#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MATRIX_SIZE 3

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

    // Receive the matrix from the client
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    read(newSocket, matrix, sizeof(matrix));

    // Display the received matrix
    printf("Received Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Calculate the sum of the main diagonal elements
    int sum = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        sum += matrix[i][i];
    }

    // Send the result back to the client
    send(newSocket, &sum, sizeof(sum), 0);
    printf("Sum of main diagonal elements sent to client\n");

    // Close the sockets
    close(newSocket);
    close(sockfd);

    return 0;
}
