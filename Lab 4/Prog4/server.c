#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <limits.h>

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sortArr(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

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

    int isBinded = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isBinded < 0) printf("Failed to Bind\n");
    else printf("Binded Successfully\n");

    int recv_arr[10];
    int n = recvfrom(sockfd, recv_arr, sizeof(recv_arr), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (n < 0) printf("Failed to Receive\n");
    else {
        printf("Array Recieved:\n");
        printArr(recv_arr, 10);
    }

    sortArr(recv_arr, 10);
    int isSent = sendto(sockfd, recv_arr, sizeof(recv_arr), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    if (isSent < 0) printf("Failed to Send\n");
    else printf("Sorted Array Sent Successfully\n");

    close(sockfd);
}