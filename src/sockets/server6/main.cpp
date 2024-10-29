/**
 * @file servidor6.cpp
 * @brief TCP server example using hostname.
 *
 * This program creates a TCP server that listens for connections from clients
 * on a specified IP address and port. Upon receiving a connection, it sends
 * structured data containing a name and age to the client.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

  unsigned short porta = 9734; ///< Port number to listen on

  // Create a new socket for communication using TCP
  if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("Houve erro na abertura do socket");
    exit(EXIT_FAILURE);
  }

  // Define the server address structure to accept connections from any IP
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
  server_address.sin_port = htons(porta);      // Set port in network byte order

  // Bind the socket to the specified address
  if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("Houve erro no Bind");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming client connections
  if (listen(server_sockfd, 5) != 0)
  {
    perror("Houve erro no Listen");
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
      perror("Houve erro no Accept");
      continue; // Continue to wait for other clients
    }

    printf("O Cliente %d se conectou ao servidor\n", client_sockfd);

    // Send the structured data to the client
    if (write(client_sockfd, &aluno, sizeof(aluno)) < 0)
    {
      perror("Houve erro na escrita WRITE()");
      close(client_sockfd);
      continue; // Continue to wait for other clients
    }

    printf("O Servidor executou o WRITE\n");
    close(client_sockfd); // Close the connection with the client
  }
}
