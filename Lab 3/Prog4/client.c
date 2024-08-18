#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    // Create Socket
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
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Connect to server by sending it a message
    char *message = "hello there this is a message";
    int sent = sendto(
        sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)
    );
    if(sent < 0) {
        printf("Message Sending Failed\n");
        return 1;
    } else {
        printf("Message Sent\n");
    }

    // Recieve the message from server
    char recieved_fromServer[1024];
    memset(recieved_fromServer, '\0', 1024);
    socklen_t serverAddrLen = sizeof(serverAddr);
    int recieved = recvfrom(
        sockfd, recieved_fromServer, 1024, 0, (struct sockaddr*)&serverAddr, &serverAddrLen
    );
    if (recieved < 0) {
        printf("Message Recieving Failed\n");
        return 1;
    } else {
        printf("Message Recieved: %s\n", recieved_fromServer);
    }
    return 0;
}