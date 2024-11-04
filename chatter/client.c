#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP_ADDRESS "192.168.233.203"
#define PORT 8080

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int wsaStartup = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaStartup != 0) {
        printf("WSAStartup failed: %d\n", wsaStartup);
        return 1;
    }

    // Create Socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket created successfully.\n");

    // Define Server Address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS); // Use inet_addr instead of inet_pton
    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        printf("Invalid address/ Address not supported\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Connect to Server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("Connected to server.\n");

    // Communication Loop
    char buffer[1024];
    while (1) {
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Send message to server
        if (send(sockfd, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            printf("Message failed to send: %d\n", WSAGetLastError());
            break;
        }

        // Check for logout command
        if (strcmp(buffer, "logout") == 0) {
            printf("Logging out...\n");
            break;
        }

        // Receive message from server
        int bytes_recv = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_recv == SOCKET_ERROR) {
            printf("Failed to receive message: %d\n", WSAGetLastError());
            break;
        } else if (bytes_recv == 0) {
            printf("Server closed the connection.\n");
            break;
        }
        buffer[bytes_recv] = '\0'; // Null-terminate the received data
        printf("Server: %s\n", buffer);
    }

    // Close the socket
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
