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

    // Define the matrix to send
    int matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Send the matrix to the server
    send(sockfd, matrix, sizeof(matrix), 0);
    printf("Matrix sent to server\n");

    // Receive the sum of the main diagonal elements from the server
    int sum = 0;
    read(sockfd, &sum, sizeof(sum));
    printf("Sum of main diagonal elements received from server: %d\n", sum);

    // Close the socket
    close(sockfd);

    return 0;
}
