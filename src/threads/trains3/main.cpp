#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

pthread_mutex_t mutexF1, mutexF2, mutexF3, mutexF4;

char railway_state[9][42] = {
  "   ---[   ]--- ---[   ]--- ---[   ]---   ",
  "  |           |           |           |  ",
  "[   ]       [   ]       [   ]       [   ]",
  "  |           |           |           |  ",
  "   ---[   ]--- ---[   ]--- ---[   ]---   ",
  "  |                                   |  ",
  "[   ]                               [   ]",
  "  |                                   |  ",
  "   ---------------[   ]---------------   "
};

/**
 * @brief Clears the screen and displays the current state of the railway.
 *
 * This function is responsible for printing the railway state to the console.
 */
void display_state()
{
  system("clear");
  printf("┌──────────────────────────────────────────────────────┐\n");
  printf("│          🚂 Welcome to the Express Railway! 🚂       │\n");
  printf("├──────────────────────────────────────────────────────┤\n");
  for (int i = 0; i < 9; i++)
  {
    printf("│      %s       │\n", railway_state[i]);
  }
  printf("└──────────────────────────────────────────────────────┘\n");
};

/**
 * @brief Updates the state of a specific railway track.
 *
 * @param line The line to update in the railway_state array.
 * @param start_column The starting column to begin updating.
 * @param content The content to insert in the specified location.
 *
 * This function updates a specific part of the railway state and then calls
 * display_state() to refresh the display.
 */
void update_railway(int line, int start_column, const char *content)
{
  for (int i = 0; content[i] != '\0'; i++)
  {
    railway_state[line][start_column + i] = content[i];
  }
  display_state();
};

/**
 * @brief The train thread function.
 *
 * This function simulates the movement of a train on the railway. Each train
 * has a different behavior based on its ID, and it interacts with other trains
 * by locking and unlocking specific track sections using mutexes.
 *
 * @param arg The train's ID passed as an argument to the thread.
 * @return NULL when the thread finishes.
 */
void *train_thread(void *arg)
{
  int train_id = *(int *)arg;
  srand(time(NULL) + train_id);

  while (1)
  {
    switch (train_id)
    {
    case 1:
      // T01 -> L01 -> L02 -> L03 -> L04
      
      update_railway(4, 7, "   "); // NULL -> L4
      update_railway(2, 1, "T01"); // T01 -> L01
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(2, 1, "   "); // NULL -> L01
      update_railway(0, 7, "T01"); // T01 -> L02
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(0, 7, "   "); // NULL -> L02
      update_railway(2, 13, "T01"); // T01 -> L03
      sleep(1); // sleep(rand() % 3 + 1);
      
      update_railway(2, 13, "   "); // NULL -> L03
      update_railway(4, 7, "T01"); // T01 -> L04
      sleep(1); // sleep(rand() % 3 + 1);
      break;

    case 2:
      // T02 -> L03 -> L07 -> L05 -> L06

      update_railway(2, 13, "   "); // NULL -> L06
      update_railway(0, 19, "T02"); // T02 -> L03
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(0, 19, "   "); // NULL -> L03
      update_railway(2, 25, "T02"); // T02 -> L07
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(2, 25, "   "); // NULL -> L07
      update_railway(4, 19, "T02"); // T02 -> L05
      sleep(1); // sleep(rand() % 3 + 1);
      
      update_railway(4, 19, "   "); // NULL -> L05
      update_railway(2, 13, "T02"); // T02 -> L06
      sleep(1); // sleep(rand() % 3 + 1);

      break;

    case 3:
      // T03 -> L05 -> L08 -> L09 -> L10

      update_railway(4, 31, "   "); // NULL -> L10
      update_railway(2, 25, "T03"); // T03 -> L05
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(2, 25, "   "); // NULL -> L05
      update_railway(0, 31, "T03"); // T03 -> L08
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(0, 31, "   "); // NULL -> L08
      update_railway(2, 37, "T03"); // T03 -> L09
      sleep(1); // sleep(rand() % 3 + 1);
      
      update_railway(2, 37, "   "); // NULL -> L09
      update_railway(4, 31, "T03"); // T03 -> L10
      sleep(1); // sleep(rand() % 3 + 1);
      
      break;

    case 4:
      // T04 -> L11 -> L04 -> L06 -> L10 -> L12 -> L13

      update_railway(8, 19, "   "); // NULL -> L13
      update_railway(6, 1, "T04"); // T04 -> L11
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(6, 1, "   "); // NULL -> L11
      update_railway(4, 7, "T04"); // T04 -> L04
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(4, 7, "   "); // NULL -> L04
      update_railway(4, 19, "T04"); // T04 -> L06
      sleep(1); // sleep(rand() % 3 + 1);
      
      update_railway(4, 19, "   "); // NULL -> L06
      update_railway(4, 31, "T04"); // T04 -> L10
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(4, 31, "   "); // NULL -> L10
      update_railway(6, 37, "T04"); // T04 -> L12
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(6, 37, "   "); // NULL -> L12
      update_railway(8, 19, "T04"); // T04 -> L13
      sleep(1);

      break;
    }
  }

  return NULL;
};

/**
 * @brief The main function that initializes the railway system and starts the trains.
 *
 * This function initializes the mutexes, creates the train threads, and waits for
 * them to complete. It also sets up the initial display of the railway state.
 *
 * @return 0 on successful execution.
 */
int main()
{
  pthread_mutex_init(&mutexF1, NULL);
  pthread_mutex_init(&mutexF2, NULL);
  pthread_mutex_init(&mutexF3, NULL);
  pthread_mutex_init(&mutexF4, NULL);

  pthread_t train_threads[4];
  int train_ids[4] = {1, 2, 3, 4};

  pthread_create(&train_threads[0], NULL, train_thread, &train_ids[0]);
  pthread_create(&train_threads[1], NULL, train_thread, &train_ids[1]);
  pthread_create(&train_threads[2], NULL, train_thread, &train_ids[2]);
  pthread_create(&train_threads[3], NULL, train_thread, &train_ids[3]);

  for (int i = 0; i < 4; i++)
  {
    pthread_join(train_threads[i], NULL);
  }

  pthread_mutex_destroy(&mutexF1);
  pthread_mutex_destroy(&mutexF2);
  pthread_mutex_destroy(&mutexF3);
  pthread_mutex_destroy(&mutexF4);

  return 0;
};