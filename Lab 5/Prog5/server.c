#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int getSecLargest (int arr[]) {
    int largest = -1, secLargest = -1;
    for (int i = 0; i < 10; i++) {
        if(arr[i] > largest) {
            secLargest = largest;
            largest = arr[i];
        } else if(arr[i] > secLargest && arr[i] != largest) {
            secLargest = arr[i];
        }
    }
    return secLargest;
}

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed.\n");
    else printf("Socket Created Successfully.\n");

    // Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = 0,
    };
    struct sockaddr_in clientAddr;
    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind<0) printf("Socket Bind Failed.\n");
    else printf("Socket Bind Successfull.\n");

    // Listen
    int isListen = listen(sockfd, 5);
    if(isListen<0) printf("Listen Failed.\n");
    else printf("Listening...\n");

    // Accept
    socklen_t clientAddrLen = sizeof(clientAddr);
    int newsockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(newsockfd<0) printf("Accept Failed.\n");
    else printf("Connection from Client Accepted.\n");

    // Recieve Message
    int array[10];
    int isRecv = recv(newsockfd, array, sizeof(array), 0);
    if(isRecv<0) printf("Message couldn't be recieved.\n");
    else printf("Message Recieved: %s\n", array);

    // Process Message
    int secLargest = getSecLargest(array);

    // Send Message
    int isSent = send(newsockfd, &secLargest, sizeof(secLargest), 0);
    if(isSent<0) printf("Message couldn't be sent.\n");
    else printf("Message Sent Successfully.\n");

    // Close
    close(newsockfd);
    close(sockfd);
    return 0;
}