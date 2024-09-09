#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    // Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind < 0) printf("Bind Failed\n");
    else printf("Bind Successfull\n");

    // Listen
    int isListen = listen(sockfd, 5);
    if (isListen < 0) printf("Listen Failed\n");
    else printf("Listening on Socket...\n");

    // Accept
    int new_sockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(new_sockfd < 0) printf("Connection with Client Failed\n");
    else printf("Connection with Client Established\n");

    // recieve
    char str1[1024] = {'\0'};
    char str2[1024] = {'\0'};
    int isRecv = recv(new_sockfd, str1, 1024, 0);
    isRecv = recv(new_sockfd, str2, 1024, 0);
    printf("Recieved String 1: %s\n", str1);
    printf("Recieved String 2: %s\n", str2);

    // Send
    int isSame = strcmp(str1, str2);
    int isSend = send(new_sockfd, &isSame, sizeof(isSame), 0);
    if(isSend < 0) printf("Send Failed\n");
    else printf("Send Successfully\n");

    // Close
    close(sockfd);
    close(new_sockfd);
    return 0;
}