/**
 * @file client5.cpp
 * @brief Simple client program to receive a structure from a server.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;

/**
 * @brief Structure to hold person data.
 */
struct Person
{
  int age;
  char name[34];
};

/**
 * @brief Main function for the client.
 *
 * Creates a socket, connects to the server at a specified IP address and port,
 * receives a Person structure from the server, and prints the data.
 *
 * @return int 0 on success, 1 on failure.
 */
int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  struct Person person;

  // Create the socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("Error creating socket");
    exit(1);
  }

  // Set up the server address struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost
  server_address.sin_port = htons(9734);                   // Port number

  // Attempt to connect to the server
  if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
  {
    perror("Error connecting to server");
    close(sockfd);
    exit(1);
  }

  // Read data from the server
  if (read(sockfd, &person, sizeof(person)) == -1)
  {
    perror("Error reading from socket");
  }

  // Output the received data
  cout << "Name: " << person.name << endl;
  cout << "Age: " << person.age << endl;

  // Close the socket and exit
  close(sockfd);
  return 0;
}
