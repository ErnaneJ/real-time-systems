/**
 * @file client6.cpp
 * @brief Simple client program to read a structure using the hostname.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <netdb.h>

using std::cout;
using std::endl;

/**
 * @brief 
 * 
 */
struct Person
{
  int age;
  char name[34];
};

/**
 * @brief Main function for the client.
 *
 * Creates a socket, resolves the hostname to an IP address, connects to the server at a specified port,
 * receives a Person structure from the server, and prints the data.
 *
 * @return int 0 on success, 1 on failure.
 */
int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  struct hostent *host_info;
  char hostname[256];
  unsigned short port = 9734; // Port number
  Person person;

  // Set the hostname of the target machine
  strcpy(hostname, "NOME-DA-SUA-MAQUINA");
  host_info = gethostbyname(hostname); // Get the machine to connect to
  if (host_info == nullptr)
  {
    fprintf(stderr, "gethostbyname failed\n");
    exit(2);
  }

  // Create the socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("Error creating socket");
    exit(1);
  }

  // Set up the server address struct
  server_address.sin_family = AF_INET;
  server_address.sin_addr = *(struct in_addr *)*host_info->h_addr_list;
  server_address.sin_port = htons(port);

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
