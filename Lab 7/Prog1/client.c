#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Creation Failed.\n");
    else printf("Socket Created Successfully.\n");

    // Connect to Server
    struct sockaddr_in serverAddr = {
        .sin_family = AF_INET,
        .sin_port = htons(8080),
        .sin_addr.s_addr = INADDR_ANY,
    };
    int isConnect = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isConnect < 0) printf("Connection Failed.\n");
    else printf("Connected to Server.\n");

    // Communication Loop
    char buffer[1024];
    while(1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        int isSend = send(sockfd, buffer, strlen(buffer), 0);
        if(isSend < 0) printf("Message failed to send.\n");
        // else printf("Message Sent.\n");

        if(strcmp(buffer, "logout") == 0) {
            printf("Logging out...\n");
            break;
        }
        
        int bytes_recv = recv(sockfd, buffer, sizeof(buffer), 0);
        if(bytes_recv > 0) buffer[bytes_recv] = '\0';
        printf("Server: %s\n", buffer);
    }

    // Close
    close(sockfd);
    return 0;
}