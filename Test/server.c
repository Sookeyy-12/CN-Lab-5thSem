#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int revnum(int num) {
    int newnum = 0;
    while(num>0) {
        int tmp = num%10;
        newnum = newnum*10 + tmp;
        num/=10;
    }
    return newnum;
}

int printArr(int arr[], int n) {
    for(int i=0; i<n; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isBind < 0) printf("Bind Failed\n");
    else printf("Bind Successfull\n");

    int isListen = listen(sockfd, 3);
    if(isListen < 0) printf("Listening Failed\n");
    else printf("Listening for Clients...\n");

    int newsockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(newsockfd < 0) printf("Failed to Connect with Client\n");
    else printf("Connected to Client\n");

    int arr[6];
    int isRecv = recv(newsockfd, arr, sizeof(arr), 0);
    if(isRecv < 0) printf("Recieve Failed\n");
    else printf("Array Recieved\n");
    printArr(arr, 6);   
    for (int i = 0; i < 6; i++) {
        if(arr[i]%2==0) {
            arr[i] = revnum(arr[i]);
        }
    }
    int isSend = send(newsockfd, arr, sizeof(arr), 0);
    if(isSend < 0) printf("Send Failed\n");
    else printf("Message Sent Successfully\n");

    close(newsockfd);
    close(sockfd);
    return 0;
}