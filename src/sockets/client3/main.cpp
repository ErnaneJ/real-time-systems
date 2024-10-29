/**
 * @file client3.cpp
 * @brief Simple client program to connect to a server and exchange a character.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Main function for the client.
 *
 * Creates a socket, connects to the server at a specified IP address and port,
 * sends a character to the server, reads the response, and prints it.
 *
 * @return int 0 on success, 1 on failure.
 */
int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  char ch = 'A';

  // Create the socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("Error creating socket");
    exit(1);
  }

  // Set up the server address struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("10.13.110.65"); // Server IP address
  server_address.sin_port = htons(9734);                      // Port number

  // Attempt to connect to the server
  if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
  {
    perror("Error connecting to server");
    close(sockfd);
    exit(1);
  }

  // Write and read data to/from the server
  if (write(sockfd, &ch, 1) == -1)
  {
    perror("Error writing to socket");
  }
  if (read(sockfd, &ch, 1) == -1)
  {
    perror("Error reading from socket");
  }

  printf("Character received from server: %c\n", ch);

  // Close the socket and exit
  close(sockfd);
  return 0;
}
