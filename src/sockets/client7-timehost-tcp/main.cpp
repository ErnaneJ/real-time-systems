#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <cstring>

#define MAX_BUFFER_SIZE 64000 // 64 KB
#define RESULT_FILE "../results.csv"

/**
 * @brief Saves the results of the transmission to a CSV file.
 *
 * @param buffer_size Size of the buffer sent.
 * @param time_s Time in seconds for the round trip.
 * @param time_ms Time in milliseconds for the round trip.
 * @param time_us Time in microseconds for the round trip.
 * @param time_ns Time in nanoseconds for the round trip.
 * @param first_10_chars First ten characters received.
 */
void saveResultsToFile(int buffer_size, long time_s, long time_ms, long time_us, long time_ns, const char *first_10_chars)
{
  std::ofstream outFile(RESULT_FILE, std::ios::app);
  outFile << buffer_size << "," << time_s << "," << time_ms << "," << time_us << "," << first_10_chars << "\n";
}

/**
 * @brief Sends data to the server and measures the round trip time.
 *
 * @param buffer_size Size of the buffer to send.
 */
void sendData(int buffer_size)
{
  printf("====================================================================\n");

  int sockfd;
  struct sockaddr_in server_address;
  char *char_array = new char[buffer_size];
  unsigned short port = 9734;

  srand(time(NULL));

  for (int i = 0; i < buffer_size; i++)
  {
    char_array[i] = 'A' + (rand() % 26); // Generate random characters (A-Z)
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("=> ❌ Error creating socket");
    delete[] char_array;
    exit(1);
  }

  // Set timeout for socket
  struct timeval timeout;
  timeout.tv_sec = 5; // Increased timeout for larger buffers
  timeout.tv_usec = 0;
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_address.sin_port = htons(port);

  // Connect to the server
  if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    perror("=> ❌ Error connecting to server");
    delete[] char_array;
    close(sockfd);
    exit(1);
  }

  printf("=> ✅ Client sending %d bytes (", buffer_size);
  for (int i = 0; i < 10; i++)
  {
    printf("%c ", char_array[i]);
  }
  printf(") to the server.\n");

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // Send the data
  send(sockfd, char_array, buffer_size, 0);

  ssize_t bytes_received = recv(sockfd, char_array, buffer_size, 0);
  if (bytes_received < 0)
  {
    perror("=> ❌ Error receiving data");
  }
  else
  {
    char first_10_chars[11];
    memcpy(first_10_chars, char_array, 10);
    first_10_chars[10] = '\0';

    clock_gettime(CLOCK_MONOTONIC, &end);

    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    long rtt_ns = seconds * 1e9 + nanoseconds;
    long rtt_ms = rtt_ns / 1e6;
    long rtt_us = rtt_ns / 1e3;

    printf("=> ✅ Client received %zd bytes (", bytes_received);
    for (int i = 0; i < 10 && i < bytes_received; i++)
    {
      printf("%c ", char_array[i]);
    }
    printf(")\n");

    printf("=> ✅ Round trip time: %ld ns | %ld us | %ld ms | %ld s\n", rtt_ns, rtt_us, rtt_ms, seconds);
    saveResultsToFile(buffer_size, seconds, rtt_ms, rtt_us, rtt_ns, first_10_chars);
  }

  // Close the socket after receiving
  close(sockfd);
  delete[] char_array;
}

/**
 * @brief Main function to initiate data sending in varying buffer sizes.
 *
 * @return Exit status.
 */
int main()
{
  for (int buffer_size = 10; buffer_size <= MAX_BUFFER_SIZE; buffer_size += 1024)
  {
    sendData(buffer_size);
  }

  // Execute the plotting script
  system("cd $(pwd)/../plot && source venv/bin/activate && pip install -r requirements.txt && python main.py");

  return 0;
}
