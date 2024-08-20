#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

void rev(char* str, int len) {
    for (int i = 0; i < len/2; i++) {
        char temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

int main() {
    // create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    // bind socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int isBinded = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // recieve from client
    char recieved[1024] = {'\0'};
    int isRecv = recvfrom(sockfd, recieved, 1024, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (isRecv < 0) printf("Cannot Recieve Message\n");
    else printf("Message Recived: %s\n", recieved);

    // reverse the string
    rev(recieved, strlen(recieved));

    // send to client
    int isSend = sendto(sockfd, recieved, strlen(recieved), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    if (isSend < 0) printf("Cannot Send Message\n");
    else printf("Message Sent: %s\n", recieved);

    close(sockfd);
}