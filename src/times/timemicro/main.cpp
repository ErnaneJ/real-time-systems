#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    int i, j;
    struct timeval start_time, end_time;
    int elapsed_time_millis;
    float elapsed_time_seconds;

    // Record the start time. The 'struct timeval' contains two fields: tv_sec and tv_usec.
    gettimeofday(&start_time, NULL);  
    
    /* Replace the following for loop with the section of code
       for which the execution time is to be measured. */
    
    for (j = 0; j < 10; j++) {
      for (i = 0; i < 1387634340; i++);
    }
    
    // Record the end time.
    gettimeofday(&end_time, NULL);
    
    // Calculate the elapsed time in milliseconds.
    elapsed_time_millis = (int)(1000 * (end_time.tv_sec - start_time.tv_sec) + 
                                  (end_time.tv_usec - start_time.tv_usec) / 1000);
    
    // Convert elapsed time to seconds.
    elapsed_time_seconds = elapsed_time_millis / 1000.0f;
    
    // Print the elapsed time in milliseconds.
    printf("Elapsed time: %f milliseconds\n", elapsed_time_seconds);
   
    return 0;
}
