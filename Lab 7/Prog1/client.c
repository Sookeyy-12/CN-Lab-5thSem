#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP_ADDRESS "172.24.73.144"
#define PORT 8080

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket Creation Failed");
        return 1;
    }
    printf("Socket Created Successfully.\n");

    // Define Server Address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP_ADDRESS, &serverAddr.sin_addr) <= 0) {
        perror("Invalid Address/ Address Not Supported");
        close(sockfd);
        return 1;
    }

    // Connect to Server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection Failed");
        close(sockfd);
        return 1;
    }
    printf("Connected to Server.\n");

    // Communication Loop
    char buffer[1024];
    while (1) {
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Send message to server
        if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
            perror("Message failed to send");
            break;
        }

        // Check for logout command
        if (strcmp(buffer, "logout") == 0) {
            printf("Logging out...\n");
            break;
        }

        // Receive message from server
        int bytes_recv = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recv < 0) {
            perror("Failed to receive message");
            break;
        } else if (bytes_recv == 0) {
            printf("Server closed the connection.\n");
            break;
        }
        buffer[bytes_recv] = '\0'; // Null-terminate the received data
        printf("Server: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);
    return 0;
}
