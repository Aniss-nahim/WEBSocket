CC=gcc
SOCKET=-lws2_32
API=-ladvapi32 
APP=./app/

server : ./app/server.c 
	$(CC) -o server $(APP)/server.c $(SOCKET) $(API)
