#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main() {
    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0) {
        cout << "Socket Creation Failed.\n";
        close(sockfd);
        return 0;
    } else {
        cout << "Socket Created Successfully.\n";
    }

    // Connect to Server
    struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(8080);
        serverAddr.sin_addr.s_addr = 0;

    int isConnect = connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isConnect < 0) {
        cout << "Connection with Server Failed.\n";
        close(sockfd);
        return 0;
    } else {
        cout << "Connection with Server Established.\n";
    }

    // Send or Recieve
    
    cout << "Enter Username: ";
    string name; cin >> name;
    int senduser = send(sockfd, name.c_str(), 32, 0);

    while(true) {
        string msg;
        cout << name << ": ";
        getline(cin, msg);
        int isSent = send(sockfd, msg.c_str(), 1024, 0);

        if(msg=="exitapp") {
            cout << "Exiting the Chat...." << endl;
            break;
        }

        // handle send() error
        char buffer[1024];
        int isRecv = recv(sockfd, buffer, 1024, 0);
        // handle recv() error
        cout << "Server: " << buffer << endl;
    }

    // Close Socket
    close(sockfd);
    return 0;
}