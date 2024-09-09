/*
TCP Server
1. Server
    - create socket
    - bind socket
    - listen
    - accept
    - recieve or send
    - close
2. Client
    - create socket
    - connect
    - send or recieve
    - close
*/


#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Step 1: create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    // Step 2: connect to server
    struct sockaddr_in serverAddr = {
        .sin_family=AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int isConnect = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isConnect < 0) printf("Connetion Failed\n");
    else printf("Connection Succesfuk\n");

    // Step 3: send ya recieve
    // char* message = "Devna now knows TCP and UDP Socket Programming.";
    char message[] = "Devna now knows TCP and UDP Socket Programming.";
    int isSent = send(sockfd, message, strlen(message), 0);
    if (isSent < 0) printf("Sent Failed\n");
    else printf("MEssage Sent\n");

    // Step 4: close socket
    close(sockfd);
    return 0;
}