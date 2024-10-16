/**
 * @file client_ipv4.c
 * @brief IPv4 TCP socket client example.
 * 
 * This program creates a client that connects to a TCP server using IPv4 
 * sockets. The client sends a character to the server, receives a response, 
 * and increments the character. This process repeats until the character 
 * reaches 'Z'. 
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Main function for the TCP client program.
 * 
 * The client establishes a connection to a TCP server, sends a character, 
 * receives a response, increments the character, and continues this process 
 * until the character 'Z' is reached. If the connection fails, the program 
 * prints an error message and terminates.
 * 
 * @return int Exit status of the program.
 */
int main() {
  int sockfd;                  ///< Socket file descriptor
  int len;                    ///< Length of the address structure
  struct sockaddr_in address; ///< Address structure for the IPv4 socket
  int result;                 ///< Result of the connection attempt
  char ch = 'A';             ///< Character to be sent to the server

  // Create a socket for communication using IPv4 and stream sockets
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // Define the address for the TCP server
  address.sin_family = AF_INET;                      ///< Address family: IPv4
  address.sin_addr.s_addr = inet_addr("127.0.0.1"); ///< Server IP address
  address.sin_port = htons(9734);                    ///< Server port number
  len = sizeof(address);

  // Attempt to connect to the server
  result = connect(sockfd, (struct sockaddr *) &address, len);

  // Check if the connection was successful
  if (result == -1) {
    perror("Error connecting to the server");
    exit(1);
  }

  // Continuously send and receive characters until 'Z' is reached
  while (1) {
    // Send character to the server
    write(sockfd, &ch, 1);
    
    // Receive character from the server
    read(sockfd, &ch, 1);
    
    // Print the character received from the server
    printf("Character received from the server = %c\n", ch);
    
    // Increment the character
    ch++;
    
    // Close the socket after the first iteration
    close(sockfd);
    
    // Sleep for 1 second before the next iteration
    sleep(1);
    
    // Break the loop if the character reaches 'Z'
    if (ch == 'Z') break;
  }
  
  return 0;  // Exit the program
}
