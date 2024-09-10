#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };

    int isConnect = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isConnect < 0) printf("Connection with Server Failed\n");
    else printf("Connection Established\n");

    int arr[] = {25, 128, 45, 232, 74, 11};
    int isSend = send(sockfd, arr, sizeof(arr), 0);
    if(isSend < 0) printf("Send Failed\n");
    else printf("Array Sent to Server\n");

    int newarr[6];
    int isRecv = recv(sockfd, newarr, sizeof(newarr), 0);
    if(isRecv < 0) printf("Recieve Failed\n");
    else printf("MEssage Recieved\n");

    for (int i = 0 ; i < 6; i++) {
        printf("%d\t", newarr[i]);
    }
    printf("\n");

    close(sockfd);
    return 0;
}