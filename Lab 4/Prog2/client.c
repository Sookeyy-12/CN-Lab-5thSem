#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
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
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int array[10] = {7, 9, 9, 9, 1, 8, 5, 2, 2, 7};
    
    int isSent = sendto(sockfd, array, sizeof(array), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isSent < 0) printf("Failed to Send\n");
    else printf("Array Sent Successfully\n");

    close(sockfd);
}