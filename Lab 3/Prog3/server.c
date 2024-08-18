#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket creation failed\n");
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);


    // Bind Socket
    int bindStatus = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(bindStatus == -1) {
        printf("Bind failed\n");
        return 1;
    } else {
        printf("Bind successful\n");
    }

    // Recieve from client
    /*
    since in UDP, it is not possible for server to directly send a message to client,
    client first needs to send a message to server so that the server can identify the client
    */
    char* recieved_fromClient[1024];
    int isRecieved = recvfrom(
        sockfd, recieved_fromClient, sizeof(recieved_fromClient), 0, (struct sockaddr*)&clientAddr, &clientAddrLen
        );
    if(isRecieved < 0) {
        printf("Message Recieving Failed\n");
        return 1;
    } else {
        printf("Message Recieved: %s\n", recieved_fromClient);
    }

    // Send to client
    char *message = "Thank You!! from the Server";
    int isSent = sendto(
        sockfd, message, strlen(message), 0, (struct sockaddr*)&clientAddr, clientAddrLen
    );
    if(isSent < 0) {
        printf("Message Sending Failed\n");
        return 1;
    } else {
        printf("Message Sent: %s\n", message);
    }
    return 0;
}