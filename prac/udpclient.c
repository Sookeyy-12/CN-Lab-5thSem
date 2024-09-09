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

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Step 1: create socket 
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Succesfully\n");

    // step 2: send or recieve
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    int isSent = sendto(sockfd, "Hello Devna", strlen("Hello Devna"), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isSent < 0) printf("Send Failed\n");
    else printf("Send Succesful\n");

    // step 3: close socket
    close(sockfd);
    return 0;
}