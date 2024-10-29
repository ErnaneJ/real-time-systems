/**
 * @file client8.cpp
 * @brief Simple UDP client to send integer values to a server.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/**
 * @brief Main function for the UDP client.
 *
 * Creates a UDP socket, sets up the server address, and sends integer values
 * to the server in a loop with a one-second delay between each send.
 *
 * @return int 0 on success, 1 on failure.
 */
int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  unsigned short port = 9734;

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

  printf("Client 8 is starting to send data.\n");

  // Send integer values to the server in a loop
  for (int i = 0; i < 30; i++)
  {
    printf("Sending: %d\n", i);
    sendto(sockfd, &i, sizeof(i), 0, (struct sockaddr *)&server_address, sizeof(server_address));
    sleep(1); // Wait for one second before sending the next value
  }

  // Close the socket and exit
  close(sockfd);
  return 0;
}
