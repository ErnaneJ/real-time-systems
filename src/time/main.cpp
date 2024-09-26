#include <iostream>
#include <ctime>   
#include <unistd.h>
#include <cstdlib> 

using std::cout;
using std::cin;

/**
 * @brief Main function that measures the execution time of a loop.
 * 
 * This program calculates the current time in seconds since the Unix epoch (00:00:00 on 01/01/1970),
 * executes a loop, and then calculates and displays the elapsed time during the loop's execution.
 *
 * @return int Exit code of the program (0 for success).
 */
int main() {
  time_t startTime, endTime;
  int dummyVariable;

  startTime = time(nullptr); // Get the current time in seconds since the Unix epoch
  
  cout << ">>> Elapsed time: " << startTime << " seconds since 00:00:00 on 01/01/1970." << '\n';
  
  // Execution loop; using dummyVariable prevents loop optimization
  for (int i = 0; i < 10000000; ++i) {
    for (int k = 0; k < 1000; ++k) {
      dummyVariable = k;
    };
  };
  
  // Get the time after the loop execution
  endTime = time(nullptr);
  
  cout << ">>> Elapsed time: " << endTime << " seconds since 00:00:00 on 01/01/1970." << '\n';
  cout << ">>> Execution time of the loop: " << endTime - startTime << " seconds." << '\n';
  
  return EXIT_SUCCESS;
};