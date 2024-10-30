#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORT 9734 ///< Port number for the server

/**
 * @brief Main function to start the TCP server.
 *
 * @return Exit status.
 */
int main()
{
  int server_sockfd, client_sockfd;
  socklen_t client_len;
  struct sockaddr_in server_address, client_address;

  // Create TCP socket
  if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
    perror("=> ❌ Error on bind");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  // Set the socket to listen for connections
  if (listen(server_sockfd, 5) < 0)
  {
    perror("=> ❌ Error listening on socket");
    close(server_sockfd);
    exit(EXIT_FAILURE);
  }

  printf("=> ⏳ Server waiting for connections...\n");

  while (1)
  {
    // Accept a new connection
    client_len = sizeof(client_address);
    if ((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len)) < 0)
    {
      perror("=> ❌ Error accepting connection");
      continue; // Continue to accept new connections
    }

    printf("====================================================================\n");
    printf("=> 🤝 Client connected.\n");

    char buffer[65535]; // Maximum buffer size for receiving data
    ssize_t bytes_received;

    // Loop for receiving and sending data
    while ((bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0)) > 0)
    {
      printf("=> ✅ Received %zd bytes (", bytes_received);
      for (int i = 0; i < 10 && i < bytes_received; i++)
      {
        printf("%c ", buffer[i]);
      }
      printf("...)\n");

      // Increment each character
      for (int i = 0; i < bytes_received; i++)
      {
        buffer[i]++;
      }

      // Send the response back to the client
      if (send(client_sockfd, buffer, bytes_received, 0) < 0)
      {
        perror("=> ❌ Error sending");
        break; // Exit the loop on error
      }
      printf("=> ✅ Response of %zd bytes sent to the client.\n", bytes_received);
    }

    if (bytes_received < 0)
    {
      perror("=> ❌ Error in reception");
    }
    else
    {
      printf("=> 👋 Client disconnected.\n");
    }

    close(client_sockfd); // Close the client socket
  }

  close(server_sockfd); // Close the server socket
  return 0;
}
