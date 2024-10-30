#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT 9734 ///< Port number for the server

/**
 * @brief Main function to start the UDP server.
 *
 * @return Exit status.
 */
int main()
{
  int server_sockfd;
  socklen_t client_len;
  struct sockaddr_in server_address, client_address;

  // Create UDP socket
  if ((server_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("=> ❌ Error opening socket");
    exit(EXIT_FAILURE);
  }

  // Configure server address
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(PORT);

  // Bind the socket to the address
  if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("=> ❌ Error in bind");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  printf("=> ⏳ Server waiting for messages...\n");

  while (1)
  {
    char buffer[65507]; // Max buffer size for UDP
    client_len = sizeof(client_address);

    // Attempt to receive data with byte check
    ssize_t bytes_received = recvfrom(server_sockfd, buffer, sizeof(buffer), 0,
                                      (struct sockaddr *)&client_address, &client_len);
    if (bytes_received < 0)
    {
      perror("=> ❌ Error in recvfrom");
      continue; // Avoid crashing on error
    }

    // Log the success of the reception
    printf("=> ✅ Received %zd bytes\n", bytes_received);
    printf("=> First 10 characters received: ");
    for (int i = 0; i < 10 && i < bytes_received; i++)
    {
      printf("%c ", buffer[i]);
    }
    printf("\n");

    // Increment each character
    for (int i = 0; i < bytes_received; i++)
    {
      buffer[i]++;
    }

    // Check for successful sending and log response
    if (sendto(server_sockfd, buffer, bytes_received, 0,
               (struct sockaddr *)&client_address, client_len) < 0)
    {
      perror("=> ❌ Error in sendto");
      continue;
    }

    printf("=> ✅ Response of %zd bytes sent to the client.\n", bytes_received);
  }

  close(server_sockfd); // Close the server socket
  return 0;
}
