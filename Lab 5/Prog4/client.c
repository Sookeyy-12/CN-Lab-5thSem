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

    // Send Message
    int array[10] = {7,9,9,9,1,8,5,2,2,7};
    int isSend = send(sockfd, array, sizeof(array), 0); 
    if(isSend<0) printf("Message couldn't be sent.\n");
    else printf("Message Sent Successfully.\n");

    // Recieve Message
    int sum;
    int isRecv = recv(sockfd, &sum, sizeof(sum), 0);
    if(isRecv<0) printf("Message couldn't be recieved.\n");
    else {
        printf("Message Recieved...\n");
        printf("Sum of Array: %d\n", sum);
    }

    // Close
    close(sockfd);
    return 0;
}