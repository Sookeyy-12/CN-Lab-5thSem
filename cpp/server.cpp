#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cout << "Socket Creation Failed.\n";
        close(sockfd);
        return 0;
    } else {
        cout << "Socket Created Successfully.\n";
    }

    // Bind Socket
    struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8080);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    int isBind = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isBind<0) {
        cout << "Failed to Bind Socket.\n";
        close(sockfd);
        return 0;
    } else {
        cout << "Socket Binded Successfully.\n";
    }

    // Listen for Connections
    int isListen = listen(sockfd, 3);
    if(isListen < 0) {
        cout << "Failed to Listen for Clients.\n";
        close(sockfd);
        return 0;
    } else {
        cout << "Listening for Clients...\n";
    }

    // Accept Connections
    int sockfd_1 = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if(sockfd_1 < 0) {
        cout << "Failed to Estabilsh connection with Client.\n";
        close(sockfd);
        close(sockfd_1);
        return 0;
    } else {
        cout << "Connection with Client Established.\n";
    }

    // Send or Recieve
    char user[32] = {'\0'};
    int recvuser = recv(sockfd_1, user, 32, 0);
    string client_username = user;
    cout << "Recognized client as: " << client_username << endl;

    while(true) {
        char buffer[1024] = {'\0'};
        int isRecv = recv(sockfd_1, buffer, 1024, 0);
        // handle recv() error
        cout << client_username << ": " << buffer << endl;
        if(strcmp(buffer, "exitapp")==0) {
            cout << client_username << " Has Exited the Chat..." << endl;
            break;
        }
        string msg;
        cout << "Server: ";
        getline(cin, msg);
        int isSent = send(sockfd_1, msg.c_str(), 1024, 0);
        // handle send() error
    }

    // Close Socket
    close(sockfd);
    close(sockfd_1);
    return 0;
}