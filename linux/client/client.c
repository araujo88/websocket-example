#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9002

int main(int argc, char *argv[]) 
{
    int network_socket; // create a socket
    // network_socket = socket(domain, type, protocol)
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    // domain: AF_INET (IPv4 protocol) / AF_INET6 (Ipv6 protocol)
    // type: SOCK_STREAM (TCP protocol) / SOCK_DGRAM (UDP protocol)
    // protocol: Internet Protocol (IP) - 0

    if (network_socket < 0) {
        perror("Socket creation error");
        printf("Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // specifies protocol IPv4
    server_address.sin_port = htons(PORT); // specifies port
    server_address.sin_addr.s_addr = INADDR_ANY;

    // connection 
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for error in the connection
    if (connection_status < 0) {
        perror("Connection error: ");
        printf("Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    // Receive data from the server
    char buffer[256]; // server response
    if ((recv(network_socket, &buffer, sizeof(buffer), 0)) < 0) {
        perror("Receive error:");
        printf("Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    // print the server's response
    printf("The server sent the data: %s\n", buffer);

    // close the socket
    close(network_socket);
    return 0;
}