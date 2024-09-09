#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    // Connect
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int isConnect = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isConnect < 0) printf("Connection Failed\n");
    else printf("Connection Established\n");

    // SEnd
    char str1[1024] = {"Hello There"};
    char str2[1024] = {"Hello There"};
    int isSend1 = send(sockfd, str1, 1024, 0);
    int isSend2 = send(sockfd, str2, 1024, 0);
    if(isSend1 < 0 || isSend2 < 0) printf("Send Failed\n");
    else printf("Send Successfully\n");

    // Reciee
    int isSame;
    int isRecv = recv(sockfd, &isSame, sizeof(isSame), 0);
    if(isRecv < 0) {
        printf("Recieve Failed\n");
    } else {
        printf("Recieved Successfully\n");
        if(isSame == 0) printf("Strings are Same\n");
        else printf("Strings are Different\n");
    }

    // Close
    close(sockfd);
    return 0;
}