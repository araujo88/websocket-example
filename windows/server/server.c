#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define PORT 9002

int main(int argc, char *argv[]) 
{
    WSADATA wsa;

    printf("\nInitializing Winsock... ");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
    printf("Initialized.\n");

    // server message
    char *server_message = "You have reached the server!";

    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    if ((bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address))) == SOCKET_ERROR) {
        printf("Binding failed: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }
    puts("Binding done");

    // listen for connections
    listen(server_socket, 5);

    // accept the connection
    puts("Waiting for incoming connections...");

    int client_socket;
    if (client_socket = accept(server_socket, NULL, NULL) == INVALID_SOCKET) {
        printf("Error accepting connections: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }
    puts("Connection accepted");

    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);
    printf("Message sent!\n");

    // close the socket
    closesocket(server_socket);
    WSACleanup();
    return 0;
}