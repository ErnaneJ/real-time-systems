#include <iostream>
#include <ctime>   
#include <unistd.h>
#include <cstdlib> 

using std::cout;
using std::cin;

/**
 * @brief Main function that calculates the elapsed time between two events.
 * 
 * The program records the current time, waits for 4 seconds, and then records 
 * the time again. It calculates the difference between the two time points and 
 * prints the elapsed time in seconds.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main() {
  time_t startTime, endTime, deltaTime;
  
  startTime = time(nullptr);

  sleep(4); // Pause the program for 4 seconds
  
  endTime = time(nullptr);
  
  deltaTime = endTime - startTime;
  
  cout << ">>> Elapsed time: " << deltaTime << " seconds\n";

  return 0;
}
