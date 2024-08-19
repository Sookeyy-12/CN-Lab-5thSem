#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[1024] = {0};
    socklen_t client_address_len = sizeof(client_address);

    // Create socket    
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        printf("Socket creation failed\n");
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    // Bind the socket to the address and port
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = 0;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        printf("Bind failed\n");
        return 1;
    }
    printf("Bind successful. Waiting for messages...\n");

    // Receive message from client
    int recv_len = recvfrom(server_socket, buffer, sizeof(buffer), 0, 
                            (struct sockaddr*)&client_address, &client_address_len);
    if (recv_len < 0) {
        printf("Failed to receive message\n");
        return 1;
    }
    printf("Received message from client: %s\n", buffer);

    pclose(server_socket);
    return 0;
}
