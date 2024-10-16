/**
 * @file server_ipv4.c
 * @brief IPv4 TCP socket server example.
 * 
 * This program creates a TCP server using IPv4 sockets that listens for 
 * incoming connections from clients. Upon accepting a client connection, 
 * the server reads a character sent by the client, increments it, and 
 * sends the modified character back. This process repeats indefinitely.
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Main function for the TCP server program.
 * 
 * The server creates a TCP socket, binds it to a specific IP address and port, 
 * and listens for incoming client connections. Upon accepting a connection, 
 * it reads a character from the client, increments it, and sends the result 
 * back. This process continues indefinitely until the server is stopped.
 * 
 * @return int Exit status of the program.
 */
int main() {
  int server_sockfd, client_sockfd;              ///< Server and client socket file descriptors
  size_t server_len;                             ///< Length of the server address structure
  struct sockaddr_in server_address;             ///< Server address structure
  struct sockaddr_in client_address;             ///< Client address structure

  // Create a new socket for communication using IPv4 and stream sockets
  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // Define the address for the TCP server
  server_address.sin_family = AF_INET;                       ///< Address family: IPv4
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  ///< Server IP address
  server_address.sin_port = htons(9734);                     ///< Server port number
  
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
    read(client_sockfd, &ch, 1);

    // Increment the received character
    ch++;

    // Send the incremented character back to the client
    write(client_sockfd, &ch, 1);
    
    // Close the connection with the client
    close(client_sockfd);
  }

  return 0;  // Exit the program (not reachable in the current loop)
}
