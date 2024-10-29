/**
 * @file server2.cpp
 * @brief TCP server example using IPv4.
 *
 * This program creates a TCP server that listens for connections from clients
 * on a specified IP address and port. It receives a character from a client,
 * increments it, and sends the modified character back.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Main function for the server program.
 *
 * The server creates a TCP socket, binds it to an IP address and port, and listens
 * for incoming client connections. Upon receiving a connection, the server reads
 * a character, increments it, and sends the updated character back to the client.
 * This process repeats indefinitely until the server is stopped.
 *
 * @return int Exit status of the program.
 */
int main()
{
  int server_sockfd, client_sockfd;              ///< Server and client socket file descriptors
  size_t server_len;                             ///< Length of the server address structure
  struct sockaddr_in server_address;             ///< Server address structure
  struct sockaddr_in client_address;             ///< Client address structure
  socklen_t client_len = sizeof(client_address); ///< Length of the client address structure

  // Create a new socket for communication using TCP
  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sockfd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Define the server address structure
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
  server_address.sin_port = htons(9734);                   // Set port in network byte order

  // Bind the socket to the specified address
  if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("Binding failed");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming client connections, allowing up to 5 pending connections
  if (listen(server_sockfd, 5) < 0)
  {
    perror("Listen failed");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  // Server loop to continuously accept and handle client connections
  while (1)
  {
    char ch; ///< Character to be received from the client

    printf("Server waiting...\n");

    // Accept an incoming client connection
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
    if (client_sockfd < 0)
    {
      perror("Accept failed");
      continue; // Continue to wait for other clients
    }

    // Receive a character from the client
    read(client_sockfd, &ch, sizeof(ch));

    // Increment the received character
    ch++;

    // Send the incremented character back to the client
    write(client_sockfd, &ch, sizeof(ch));

    // Close the connection with the client
    close(client_sockfd);
  }
}
