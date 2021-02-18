#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<winsock.h>

#pragma comment(lib,"Ws2_32.lib")

void main(int argc, char * argv[]){
   
    // Initialize winsock
    WSADATA wsData;
    WORD version = MAKEWORD(2,2);

    int wsok = WSAStartup(version, &wsData);

    if(wsok != 0){
        printf("Can't initialize winsock, exit !");
        exit(1);
    }

    // Create socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket == INVALID_SOCKET){
        printf("Can't create socket, exit !");
        exit(2);
    }

    // Bind the socket to an ip address and port
    int portNumber = 8000;
    char ipAddress[10] = "127.0.0.1";
    struct sockaddr_in serveradd;
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(portNumber); // host to network short
    serveradd.sin_addr.S_un.S_addr = inet_addr(ipAddress);

    bind(serverSocket, (struct sockaddr*) &serveradd , sizeof(serveradd));

    // Listening, one connection is allowed 
    int listening = listen(serverSocket, 1); // SOMAXCONN 

    if(listening != -1){
        printf("Server listening on port %d\n", portNumber);
    }

    // Accept connection
    SOCKET clientSocket;
    clientSocket = accept(serverSocket, NULL, NULL);

    if(clientSocket){
        printf("Client is connected ... \n");
    }

    // send message to client
    char response[256] = "You have requested to this server !";
    send(clientSocket, response, sizeof(response), 0);


    // Shutdown winsock
    shutdown(serverSocket, SD_RECEIVE);
    // 0 : SD_RECEIVE
    // 1 : SD_SEND
    // 2 : SD_BOTH

    // Close socket
    closesocket(serverSocket);

    return;
}