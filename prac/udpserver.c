/*
UDP -> Connection Less
1. Server
    - create socket
    - bind socket
    - recieve or send
    - close socket
2. Client
    - create socket
    - send or recieve
    - close socket
*/

/*
Client -> Server => direct client can send a message to server
Server -> Client => first client has to send a message to server then server can send a message to client
*/


#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Step 1: Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Succesfully\n");
    // on successful socket creation -> socket ka number
    // else -1

    // Step 2: Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind < 0) printf("Bind Failed\n");
    else printf("Bind Succesful\n");
    // on successful bind -> +ve ya 0
    // else -1

    // Step 3: Recieve or Send
    // UDP -> recvfrom and sendto
    char buffer[1024] = {'\0'};
    int isRecieved = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(isRecieved < 0) printf("Recieve Failed\n");
    else printf("Recieve Succesful\n");
    // if succesfull -> no of bytes recieved
    // else -1
    printf("Recieved: %s\n", buffer);

    // Step 4: Close Socket
    close(sockfd);
    return 0;
}