/**
 * @file client4.cpp
 * @brief Simple client program to read a character array from a server.
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
 * sends a character array to the server, receives a response, and prints it.
 *
 * @return int 0 on success, 1 on failure.
 */
int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  char char_array[4] = {'A', 'B', 'C', 'D'};

  // Create the socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("Error creating socket");
    exit(1);
  }

  // Set up the server address struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
  server_address.sin_port = htons(9734);                   // Port number

  // Attempt to connect to the server
  if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
  {
    perror("Error connecting to server");
    close(sockfd);
    exit(1);
  }

  // Send and receive data to/from the server
  send(sockfd, char_array, sizeof(char_array), 0);
  recv(sockfd, char_array, sizeof(char_array), 0);

  printf("Characters received from server: %c %c %c %c\n",
         char_array[0], char_array[1], char_array[2], char_array[3]);

  // Close the socket and exit
  close(sockfd);
  return 0;
}
