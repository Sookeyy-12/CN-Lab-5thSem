#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    socklen_t serverAddrLen = sizeof(serverAddr);

    char* message = "Hello to the Server!";
    int isSend = sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isSend < 0) printf("Failed to Send Message\n");
    else printf("Message Sent\n");

    char recv[1024] = {'\0'};
    int isRecv = recvfrom(sockfd, recv, 1024, 0, (struct sockaddr*)&serverAddr, &serverAddrLen);
    if (isRecv < 0) printf("Failed to Recieve Message\n");
    else printf("Message Recieved: %s\n", recv);

    close(sockfd);
}