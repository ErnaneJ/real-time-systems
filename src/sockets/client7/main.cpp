/**
 * @file client7.cpp
 * @brief Simple client program to read a character array using UDP protocol.
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
 * Creates a UDP socket, sets up the server address, sends a character array to the server,
 * receives a response, and prints the data.
 *
 * @return int 0 on success, 1 on failure.
 */
int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  char char_array[4] = {'A', 'B', 'C', 'D'};
  unsigned short port = 9734;
  socklen_t addr_len;

  // Create the socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("Error creating socket");
    exit(1);
  }

  // Set up the server address struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
  server_address.sin_port = htons(port);

  addr_len = sizeof(server_address);

  printf("The client is about to send the message to the server.\n");

  // Send and receive data to/from the server
  sendto(sockfd, char_array, sizeof(char_array), 0, (struct sockaddr *)&server_address, addr_len);
  recvfrom(sockfd, char_array, sizeof(char_array), 0, (struct sockaddr *)&server_address, &addr_len);

  // Output the received data
  printf("Characters received from server: %c %c %c %c\n",
         char_array[0], char_array[1], char_array[2], char_array[3]);

  // Close the socket and exit
  close(sockfd);
  return 0;
}
