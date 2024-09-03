#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket Creation Failed\n");
        return 1;
    }
    printf("Socket Created Successfully\n");

    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = inet_addr("127.0.0.1"),  // assuming server is running on localhost
    };

    // Prepare the array to send
    int arr[] = {10, 29, 11, 18, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    int buffer[1024];
    buffer[0] = n;  // First element is the size of the array
    memcpy(&buffer[1], arr, n * sizeof(int));

    // Send the array to the server
    int isSent = sendto(sockfd, buffer, (n + 1) * sizeof(int), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isSent < 0) {
        printf("Message couldn't be sent\n");
        close(sockfd);
        return 1;
    }
    printf("Array sent to server successfully\n");

    // Receive the result from the server
    int primeCount;
    socklen_t serverAddrLen = sizeof(serverAddr);
    int isRecv = recvfrom(sockfd, &primeCount, sizeof(primeCount), 0, (struct sockaddr*)&serverAddr, &serverAddrLen);
    if (isRecv < 0) {
        printf("Message couldn't be received\n");
    } else {
        printf("Number of primes in the array: %d\n", primeCount);
    }

    // Close Socket
    close(sockfd);
    return 0;
}
