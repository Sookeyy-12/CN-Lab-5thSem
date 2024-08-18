#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket Creation Failed\n");
        return 1;
    } else {
        printf("Socket Created Succesfully\n");
    }

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Bind the Socket
    int isBinded = bind(
        sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)
    );
    if (isBinded < 0) {
        printf("Socket Binding Failed\n");
        return 1;
    } else {
        printf("Socket Binded Successfully\n");
    }

    // Recieve message from Client
    char recieved_fromClient[1024];
    memset(recieved_fromClient, '\0', 1024);
    int recieved = recvfrom(
        sockfd, recieved_fromClient, 1024, 0, (struct sockaddr*)& clientAddr, &clientAddrLen
    );
    if (recieved < 0) {
        printf("Message Recieving Failed\n");
        return 1;
    } else {
        printf("Message Recieved: %s\n", recieved_fromClient);
    }
    
    // Convert the message into UpperCase
    char upperCase[1024];
    for (int i = 0; i < 1024; i++) {
        upperCase[i] = toupper(recieved_fromClient[i]);
    }

    // send to client
    int sended = sendto(
        sockfd, upperCase, 1024, 0, (struct sockaddr*)&clientAddr, clientAddrLen
    );
    if (sended < 0) {
        printf("Message Sending Failed\n");
        return 1;
    } else {
        printf("Message Sent: %s\n", upperCase);
    }
    return 0;
}