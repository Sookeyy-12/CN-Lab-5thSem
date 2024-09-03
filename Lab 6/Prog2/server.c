#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to count primes in the array
int countPrimes(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (isPrime(arr[i])) {
            count++;
        }
    }
    return count;
}

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Socket Creation Failed\n");
        return 1;
    }
    printf("Socket Created Successfully\n");

    // Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Socket Bind Failed\n");
        close(sockfd);
        return 1;
    }
    printf("Socket Binded Successfully\n");

    // Receive the array from client
    int buffer[1024];
    int isRecv = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (isRecv < 0) {
        fprintf(stderr, "Receive Failed\n");
        close(sockfd);
        return 1;
    }
    int n = buffer[0];
    printf("Received array of size: %d\n", n);

    // Count the number of prime numbers in the array
    int primeCount = countPrimes(&buffer[1], n);
    printf("Number of primes in the array: %d\n", primeCount);

    // Send the result back to the client
    int isSent = sendto(sockfd, &primeCount, sizeof(primeCount), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
    if (isSent < 0) {
        fprintf(stderr, "Message couldn't be sent.\n");
    } else {
        printf("Result sent to client successfully\n");
    }

    // Close Socket
    close(sockfd);
    return 0;
}
