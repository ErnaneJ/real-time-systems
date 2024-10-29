/**
 * @file client1.c
 * @brief UNIX domain socket client example.
 *
 * This program creates a client that connects to a UNIX domain socket server,
 * sends a character, and receives a response. It demonstrates basic socket
 * communication using `AF_UNIX` and `SOCK_STREAM`.
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Main function for the client program.
 *
 * The client establishes a connection to a UNIX domain socket server, sends a
 * single character, and receives a response. If the connection fails, the
 * program will print an error message and terminate.
 *
 * @return int Exit status of the program.
 */
int main()
{
  int sockfd;                 ///< Socket file descriptor
  int len;                    ///< Length of the address structure
  struct sockaddr_un address; ///< Address structure for the UNIX domain socket
  int result;                 ///< Result of the connection attempt
  char ch = 'A';              ///< Character to be sent to the server

  // Create a socket for communication using the UNIX domain and stream sockets
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

  // Define the address for the UNIX domain socket
  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, "../../server1/build/server_socket");
  len = sizeof(address);

  // Attempt to connect to the server
  result = connect(sockfd, (struct sockaddr *)&address, len);

  // Check if the connection was successful
  if (result == -1)
  {
    perror("Error connecting to the server");
    exit(1);
  }

  // Send and receive a single character to/from the server
  write(sockfd, &ch, 1); // Send character to the server
  read(sockfd, &ch, 1);  // Receive character from the server

  // Print the character received from the server
  printf("Character received from the server = %c\n", ch);

  // Close the socket and exit
  close(sockfd);
  return 0;
}
