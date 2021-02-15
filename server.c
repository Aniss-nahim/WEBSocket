#include<stdio.h>
#include<stdlib.h>
#include<ws2tcpip.h>

#pragma comment(lib,"Ws2_32.lib")

void main(int argc, char * argv){
   
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
    struct sockaddr_in serveradd;
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons(1500); // host to network short
    serveradd.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*) &serveradd , sizeof(serveradd));

    // Listening
    listen(serverSocket, SOMAXCONN); // SOMAXCONN 

    // Wait for connexion
    
    // Close listening socket
    closesocket(serverSocket);

    // Loop : accept and echo message back to client


    // Close socket


    // Shutdown winsock

}

void init(){
    printf("Hello this is init methode ! \n");
}