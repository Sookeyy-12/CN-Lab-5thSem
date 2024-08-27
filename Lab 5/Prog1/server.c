#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed.\n");
    else printf("Socket Created Successfully.\n");

    // Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind<0) printf("Socket Bind Failed.\n");
    else printf("Socket Bind Successfull.\n");

    // Listen
    int isListen = listen(sockfd, 5);
    if(isListen<0) printf("Listen Failed.\n");
    else printf("Listening...\n");

    // Accept
    socklen_t clientAddrLen = sizeof(clientAddr);
    int newsockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(newsockfd<0) printf("Accept Failed.\n");
    else printf("Connection from Client Accepted.\n");

    // Close
    close(newsockfd);
    close(sockfd);
    return 0;
}