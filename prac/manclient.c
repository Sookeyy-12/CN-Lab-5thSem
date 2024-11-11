#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    // create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    struct sockaddr_in serverAddr = {
        .sin_family=AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddrLen);

    // send ya recv
    char buffer[1024] = {'\0'};
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);
    int isSend = sendto(sockfd, &buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isSend < 0) printf("Failed to Send Message\n");
    else printf("Message Sent Successfully\n");

    int isRecv = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (isRecv < 0) printf("Failed to Receive Message\n");
    else {
        buffer[isRecv] = '\0';
        printf("Received Message: %s\n", buffer);
        char *words[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        for (int i = 0; i < 3; i++) {
            if (buffer[i] >= '0' && buffer[i] <= '9') {
            printf("%s ", words[buffer[i] - '0']);
            }
        }
        printf("\n");
    }
}