/**
 * @file servidor8.cpp
 * @brief UDP server example that receives and displays an integer value.
 *
 * This program creates a UDP server that listens for incoming integer values
 * from clients, prints the received values to the console, and continues to
 * wait for more messages. It demonstrates basic UDP communication in C.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Main function for the UDP server program.
 *
 * The server creates a UDP socket, binds it to all available interfaces on a
 * specified port, and listens for incoming integer values. Upon receiving a
 * message, it prints the integer value to the console. This process repeats
 * indefinitely until the server is stopped.
 *
 * @return int Exit status of the program.
 */
int main()
{
  int server_sockfd;                 ///< Server socket file descriptor
  size_t server_len;                 ///< Length of the server address structure
  socklen_t client_len;              ///< Length of the client address structure
  struct sockaddr_in server_address; ///< Server address structure
  struct sockaddr_in client_address; ///< Client address structure

  unsigned short porta = 9734; ///< Port number

  // Create a new socket for communication using UDP
  if ((server_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("Error opening socket");
    exit(EXIT_FAILURE);
  }

  // Define the server address structure to accept connections from any IP
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP
  server_address.sin_port = htons(porta);             // Set port in network byte order

  // Bind the socket to the specified address
  if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("Error in bind");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  // Server loop to continuously receive and display integer values from clients
  while (1)
  {
    int valor; ///< Variable to hold the received integer value

    printf("Servidor esperando ...\n");

    // Receive an integer value from the client
    client_len = sizeof(client_address);
    if (recvfrom(server_sockfd, &valor, sizeof(valor), 0,
                 (struct sockaddr *)&client_address, &client_len) < 0)
    {
      perror("Error in recvfrom");
      exit(EXIT_FAILURE);
    }

    // Print the received value to the console
    printf("Valor recebido foi = %d\n", valor);
  }

  // Close the server socket (not reached in this implementation)
  close(server_sockfd);
  return 0;
}
