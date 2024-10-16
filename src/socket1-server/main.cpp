/**
 * @file server.c
 * @brief UNIX domain socket server example.
 * 
 * This program creates a server that listens for connections from clients 
 * using UNIX domain sockets. The server receives a character from the client, 
 * increments it, and sends the modified character back. It demonstrates basic 
 * socket communication with `AF_UNIX` and `SOCK_STREAM`.
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Main function for the server program.
 * 
 * The server creates a UNIX domain socket, binds it to a file path, and listens 
 * for incoming client connections. Upon receiving a connection, the server 
 * reads a character, increments it, and sends the updated character back to 
 * the client. This process repeats indefinitely until the server is stopped.
 * 
 * @return int Exit status of the program.
 */
int main() {
  int server_sockfd, client_sockfd;           ///< Server and client socket file descriptors
  size_t server_len, client_len;              ///< Lengths of the address structures
  struct sockaddr_un server_address;          ///< Server address structure
  struct sockaddr_un client_address;          ///< Client address structure

  // Remove any previous socket with the same name
  unlink("server_socket");

  // Create a new socket for communication using the UNIX domain and stream sockets
  server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

  // Define the address for the server's UNIX domain socket
  server_address.sun_family = AF_UNIX;
  strcpy(server_address.sun_path, "server_socket");
  server_len = sizeof(server_address);

  // Bind the socket to the specified address
  bind(server_sockfd, (struct sockaddr *) &server_address, server_len);

  // Listen for incoming client connections, allowing up to 5 pending connections
  listen(server_sockfd, 5);

  // Server loop to continuously accept and handle client connections
  while (1) {
    char ch;  ///< Character to be received from the client

    // Display a message indicating the server is waiting for a connection
    printf("Server waiting...\n");

    // Accept an incoming client connection
    client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, (socklen_t *) &client_len);

    // Receive a character from the client
    recv(client_sockfd, &ch, 1, 0);

    // Increment the received character
    ch++;

    // Send the incremented character back to the client
    write(client_sockfd, &ch, 1);

    // Close the connection with the client
    close(client_sockfd);
  }
}
