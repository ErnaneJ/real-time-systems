/**
 * @file servidor7.cpp
 * @brief UDP server example that reads and writes a character array.
 *
 * This program creates a UDP server that listens for incoming messages from
 * clients, increments the characters received in a fixed-size array, and sends
 * the modified array back to the client.
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
 * specified port, and listens for incoming messages. Upon receiving a message,
 * it increments the characters in the received array and sends it back to the
 * client. This process repeats indefinitely until the server is stopped.
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

  // Server loop to continuously receive and respond to client messages
  while (1)
  {
    char vetor_ch[4]; ///< Array to hold characters received from the client

    printf("Servidor esperando ...\n");

    // Receive a message from the client
    client_len = sizeof(client_address);
    if (recvfrom(server_sockfd, vetor_ch, sizeof(vetor_ch), 0,
                 (struct sockaddr *)&client_address, &client_len) < 0)
    {
      perror("Error in recvfrom");
      exit(EXIT_FAILURE);
    }

    // Increment each character in the received array
    for (int i = 0; i < 4; i++)
    {
      vetor_ch[i]++;
    }

    // Send the modified array back to the client
    if (sendto(server_sockfd, vetor_ch, sizeof(vetor_ch), 0,
               (struct sockaddr *)&client_address, client_len) < 0)
    {
      perror("Error in sendto");
      exit(EXIT_FAILURE);
    }
  }

  // Close the server socket (not reached in this implementation)
  close(server_sockfd);
  return 0;
}
