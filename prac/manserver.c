#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void reverseMsg(char *str, char *newmsg, int len) {
    int j = 0;
    for (int i = len - 1; i >= 0; i--) {
        newmsg[j] = str[i];
        j++;
    }
    newmsg[j] = '\0';
}

int main() {
    // create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    // bind socket
    struct sockaddr_in serverAddr = {
        .sin_family=AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddrLen);

    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isBind < 0) printf("Bind Failed\n");
    else printf("Binded Successfully\n");

    // Recieve or Send
    char buff[1024] = {'\0'};
    int isRecv = recvfrom(sockfd, &buff, 1024, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(isRecv < 0) printf("Message couldn't be recieved\n");
    else printf("Message Recieved Successfully\n");

    char newmsg[4];
    reverseMsg(buff, newmsg, 3);
    int isSend = sendto(sockfd, &newmsg, sizeof(newmsg), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    if(isSend < 0) printf("Failed to Send message\n");
    else printf("Message Sent Succesfully\n");

    close (sockfd);
}