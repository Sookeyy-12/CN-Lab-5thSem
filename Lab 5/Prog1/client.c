#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed.\n");
    else printf("Socket Created Successfully.\n");

    // Connect to Server
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    printf("Connecting to Server...\n");
    int isConnect = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isConnect<0) printf("Connection Failed.\n");
    else printf("Connected to Server.\n");

    // Close
    close(sockfd);
    return 0;
}