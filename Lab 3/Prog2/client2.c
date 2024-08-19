#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char *message = "Hello KIIT";

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        printf("Socket creation failed\n");
        return 1;
    } else {
        printf("Socket created successfully\n");
    }

    // Set up server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = 0;

    // Send message to server
    if (sendto(client_socket, message, strlen(message), 0, 
                (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        printf("Message sending failed\n");
        return 1;
    }
    printf("Message sent to server: %s\n", message);

    close(client_socket);
    return 0;
}
