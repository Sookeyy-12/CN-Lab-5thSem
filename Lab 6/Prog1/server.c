#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

// Define a struct to return a pair of indices
struct Pair {
    int l, r;
};

// Function to check for palindrome
struct Pair isPalin(char str[], int n) {
    int l = 0, r = n - 1;
    while (l <= r) {
        if (str[l] == str[r]) {
            l++;
            r--;
        } else {
            struct Pair result = {l, r};
            return result;
        }
    }
    struct Pair result = {-1, -1};
    return result;
}

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) fprintf(stderr, "Socket Creation Failed\n");
    else printf("Socket Created Successfully\n");

    // Bind Socket
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (isBind < 0) fprintf(stderr, "Socket Bind Failed\n");
    else printf("Socket Binded Successfully\n");

    // Receive Message
    char buffer[1024] = {'\0'};
    int isrecv = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (isrecv < 0) fprintf(stderr, "Receive Failed\n");
    else printf("Message Received: %s\n", buffer);

    // Palindrome Operation
    struct Pair pair = isPalin(buffer, strlen(buffer));
    int ispalindrome = (pair.l == -1 && pair.r == -1);

    // Send Message
    if (ispalindrome) {
        char ans[] = "String is Palindrome";
        int isSent = sendto(sockfd, ans, sizeof(ans), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        if (isSent < 0) fprintf(stderr, "Message couldn't be sent.\n");
        else printf("Message sent successfully\n");
    } else {
        int indices[2] = {pair.l, pair.r};  // Send the indices
        int isSent = sendto(sockfd, indices, sizeof(indices), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        if (isSent < 0) fprintf(stderr, "Message couldn't be sent.\n");
        else printf("Message sent successfully\n");
    }

    // Close Socket
    close(sockfd);
    return 0;
}
