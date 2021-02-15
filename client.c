#include<stdio.h>
#include<stdlib.h>
#include<ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

void main (int argc, char * argv[]){
    // inistialize winsock
    WSADATA wsData;
    WORD version = MAKEWORD(2, 2);

    int wsok = WSAStartup(version, &wsData);

    if(wsok != 0){
        printf("Can't initialize winsock, exit !\n");
        exit(1);
    } 


    //cerate socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSocket == INVALID_SOCKET){
        printf("Can't create client socket, exit !\n");
        exit(2);
    }

    // connect 
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1500);
    serveraddr.sin_addr.S_un.S_addr = INADDR_ANY;

    int connection =  connect(clientSocket, (struct sockaddr*) &clientSocket, sizeof(clientSocket));

    if(connection == -1){
        printf("Can't connect the two sockets, exit !\n");
        exit(3);
    }

    // recieve data from  the server
    char response_server[256];
    recv(clientSocket, response_server, sizeof(response_server), 0);

    printf("server : %s", response_server);

    // Shutdown
    shutdown(clientSocket, 2);

    // close socket
    closesocket(clientSocket);

    return;
}