#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Socket Create
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket Creation Failed\n");
        return 1;
    } else {
        printf("Socket Created Successfully\n");
    }

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = inet_addr("127.0.0.1"),  // assuming server is running on localhost
    };

    // Send String
    char* message = "helloulleh";  // test string
    int isSent = sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isSent < 0) {
        printf("Message couldn't be sent\n");
        close(sockfd);
        return 1;
    } else {
        printf("Message sent successfully\n");
    }

    // Receive Message
    char buffer[1024] = {0};
    socklen_t serverAddrLen = sizeof(serverAddr);
    int isRecv = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, &serverAddrLen);
    if (isRecv < 0) {
        printf("Message couldn't be received\n");
    } else {
        // Interpret the message
        if (strcmp(buffer, "String is Palindrome") == 0) {
            printf("Server Response: %s\n", buffer);
        } else {
            int *indices = (int*)buffer;  // Cast to an integer array to interpret the indices
            printf("String is not a palindrome. Differing indices: %d and %d\n", indices[0], indices[1]);
        }
    }

    // Close Socket
    close(sockfd);
    return 0;
}
