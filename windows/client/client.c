#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>

#ifndef WIN32_LEAN_AND_MEAN // windows
#define WIN32_LEAN_AND_MEAN // windows
#endif // windows
#include <winsock2.h> // windows
#include <windows.h> // windows
#include <ws2tcpip.h> // windows
#include <iphlpapi.h> // windows
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// #include <sys/socket.h> // unix
// #include <netinet/in.h> // unix

#define PORT 9002

int main(int argc, char *argv[]) 
{
    WSADATA wsa; // windows

    // windows
    printf("\nInitializing Winsock... ");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
    printf("Initialized.\n");
    // windows

    int network_socket; // create a socket
    // network_socket = socket(domain, type, protocol)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    // domain: AF_INET (IPv4 protocol) / AF_INET6 (Ipv6 protocol)
    // type: SOCK_STREAM (TCP protocol) / SOCK_DGRAM (UDP protocol)
    // protocol: Internet Protocol (IP) - 0

    if (network_socket == INVALID_SOCKET) {
        //perror("Socket creation error");
        //printf("Error code: %d\n", errno);
        printf("Socket creation error: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // specifies protocol IPv4
    server_address.sin_port = htons(PORT); // specifies port
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0 ) {
        //perror("Invalid address / Address not supported");
        //printf("Error code: %d\n", errno);
        printf("Invalid address / Address not supported: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // connection 
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for error in the connection
    if (connection_status < 0) {
        //perror("Connection error: ");
        //printf("Error code: %d\n", errno);
        printf("Connection error: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // Receive data from the server
    char *buffer; // server response
    if ((recv(network_socket, buffer, sizeof(buffer), 0)) == SOCKET_ERROR) {
        //perror("Receive error:");
        //printf("Error code: %d\n", errno);
        printf("Receive error: %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }

    // print the server's response
    printf("The server sent the data: %s\n", buffer);

    // close the socket
    closesocket(network_socket); // windows
    // close(socket); // unix
    WSACleanup(); // windows
    return 0;
}