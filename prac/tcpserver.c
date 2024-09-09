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
    if (sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Succesfully\n");

    // Step 2: bind socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // bind(socket_to_be_bounded, server_struct, size_of_server_struct)
    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind < 0) printf("Bind Failed\n");
    else printf("Bind Succesful\n");

    // Step 3: Listen for connections
    int isListen = listen(sockfd, 3);
    if(isListen < 0) printf("Listen Failed\n");
    else printf("Listen Succesful\n");

    // Step 4: accept the connection
    int new_sockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(new_sockfd < 0) printf("Accept Failed\n");
    else printf("Accept Succesful\n");

    // Step 5: Send or Recieve
    char buffer[1024] = {'\0'};
    int isRecieved = recv(new_sockfd, buffer, 1024, 0);
    if(isRecieved < 0) printf("Recieve Failed\n");
    else {
        printf("Recieve Succesful\n");
        printf("Message Recieved: %s\n", buffer);
    }

    // Step 6: Close the socket
    close(sockfd);
    close(new_sockfd);
    return 0;
}