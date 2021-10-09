#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9002

int main(int argc, char *argv[]) 
{
    // server message
    char *server_message = "You have reached the server!";

    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET) {
        perror("Socket failed: ");
        printf("Error code: %d\n", errno);
        return EXIT_FAILURE;
    }

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    if ((bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address))) == SOCKET_ERROR) {
        perror("Bind failed");
        printf("Error code: %d\n", errno);
        return EXIT_FAILURE;
    }
    puts("Binding done");

    // listen for connections
    listen(server_socket, 5);

    // accept the connection
    puts("Waiting for incoming connections...");

    int client_socket;
    if (client_socket = accept(server_socket, NULL, NULL) == INVALID_SOCKET) {
        perror("Accept failed");
        printf("Error code: %d\n", errno);
        return EXIT_FAILURE;
    }
    puts("Connection accepted");

    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);
    printf("Message sent!\n");

    // close the socket
    close(server_socket); // unix
    return 0;
}