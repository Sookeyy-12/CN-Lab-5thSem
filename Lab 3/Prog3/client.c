#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
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

    // Connect to server by sending it a message
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    socklen_t serverAddrLen = sizeof(serverAddr);
    char *message = "Client Connecting to Server Request";
    int isSent = sendto(
        sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, serverAddrLen
    );
    if (isSent < 0) {
        printf("Message Sending Failed\n");
        return 1;
    } else {
        printf("Message Sent: %s\n", message);
    }

    // Recieve from server
    char recieved_fromServer[1024] = {'\0'};
    int recieved = recvfrom(
        sockfd, recieved_fromServer, sizeof(recieved_fromServer), 0, (struct sockaddr*)&serverAddr, &serverAddrLen
    );
    if (recieved < 0) {
        printf("Message Recieving Failed\n");
        return 1;
    } else {
        printf("Message Recieved: %s\n", recieved_fromServer);
    }
    return 0;
}