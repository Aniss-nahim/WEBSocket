#include<stdio.h>
#include<stdlib.h>
#include<winsock.h>

#pragma comment(lib,"Ws2_32.lib")

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

    // server ip address and port 
    int portNumber = 8000;
    char ipAddress[10] = "127.0.0.1";
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8000);
    serveraddr.sin_addr.S_un.S_addr = inet_addr(ipAddress);

    // connect to server
    int connection =  connect(clientSocket, (struct sockaddr*) &serveraddr, sizeof(struct sockaddr));

    if(connection == -1){
        printf("connection error : %ld \n", WSAGetLastError());
        printf("Can't connect to the server, exit !\n");
        closesocket(clientSocket);
        exit(3);
    }

    // recieve data from  the server
    char my_request[256] = "Hello server !";
    char response_server[256];
    int data_len;

    while( (data_len = send(clientSocket, my_request, sizeof(my_request), 0)) > 0){
        memset(my_request, 0,sizeof(my_request));
        recv(clientSocket, response_server, sizeof(response_server), 0);
        printf("server : %s\n", response_server);
        memset(response_server, 0,sizeof(response_server));
        gets(my_request);
    }

    printf("server is down : error 500 \n");

    // Shutdown
    shutdown(clientSocket, 2);

    // close socket
    closesocket(clientSocket);

    return;
}