/**
 * @file servidor5.cpp
 * @brief TCP server example that sends a structured data to the client.
 *
 * This program creates a TCP server that listens for connections from clients
 * on a specified IP address and port. Upon receiving a connection, it sends
 * a structured data containing a name and age to the client.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Main function for the server program.
 *
 * The server creates a TCP socket, binds it to all interfaces on a specified
 * port, and listens for incoming client connections. Upon receiving a connection,
 * it initializes a data structure with a name and age, and sends this structure
 * to the client. This process repeats indefinitely until the server is stopped.
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

  // Remove any previous socket with the same name (if using UNIX domain socket)
  unlink("server_socket");

  // Create a new socket for communication using TCP
  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sockfd < 0)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Define the server address structure to accept connections from any IP
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
  server_address.sin_port = htons(9734);       // Set port in network byte order

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
    struct dado
    {
      int idade;     ///< Age of the student
      char nome[34]; ///< Name of the student
    };

    dado aluno; // Declare the data structure to hold student information
    aluno.idade = 38;
    strcpy(aluno.nome, "Jose Silva");

    printf("Servidor esperando ...\n");

    // Accept an incoming client connection
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
    if (client_sockfd < 0)
    {
      perror("Accept failed");
      continue; // Continue to wait for other clients
    }

    // Send the structured data to the client
    write(client_sockfd, &aluno, sizeof(aluno));

    // Close the connection with the client
    close(client_sockfd);
  }
}
