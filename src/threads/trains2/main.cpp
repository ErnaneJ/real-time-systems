#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

pthread_mutex_t mutexF1, mutexF2, mutexF3;

char railway_state[9][100] = {
  "   ---[   ]--- ---[   ]---   ",
  "  |           |           |  ",
  "[   ]       [   ]       [   ]",
  "  |           |           |  ",
  "   ---[   ]--- ---[   ]---   ",
  "  |                       |  ",
  "[   ]                   [   ]",
  "  |                       |  ",
  "   ---------[   ]---------   "
};

/**
 * @brief Clears the screen and displays the current state of the railway.
 *
 * This function is responsible for printing the railway state to the console.
 */
void display_state()
{
  system("clear");
  printf("┌──────────────────────────────────────────┐\n");
  printf("│   🚂 Welcome to the Express Railway! 🚂  │\n");
  printf("├──────────────────────────────────────────┤\n");
  for (int i = 0; i < 9; i++)
  {
    printf("│      %s       │\n", railway_state[i]);
  }
  printf("└──────────────────────────────────────────┘\n");
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
      // T01 -> L3 -> L4 -> L1 -> L2;
      update_railway(4, 7, "   "); // NULL -> L4
      update_railway(2, 1, "T01"); // T01 -> L1
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(2, 1, "   "); // NULL -> L1
      update_railway(0, 7, "T01"); // T01 -> L2
      sleep(1); // sleep(rand() % 3 + 1);

      printf("T01 is waiting for L3\n");
      pthread_mutex_lock(&mutexF1);
      update_railway(0, 7, "   "); // NULL -> L2
      update_railway(2, 13, "T01"); // T01 -> L3
      sleep(1); // sleep(rand() % 3 + 1);
      printf("T01 in L3-L8 is waiting for L4-L9\n");
      
      pthread_mutex_lock(&mutexF2);
      pthread_mutex_unlock(&mutexF1);
      
      update_railway(2, 13, "   "); // NULL -> L3
      update_railway(4, 7, "T01"); // T01 -> L4
      sleep(1); // sleep(rand() % 3 + 1);
      pthread_mutex_unlock(&mutexF2);
      break;

    case 2:
      // T02 -> L7 -> L8 -> L5 -> L6;
      update_railway(2, 13, "   "); // NULL -> L3(L8)
      update_railway(0, 19, "T02"); // T02 -> L5
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(0, 19, "   "); // NULL -> L5
      update_railway(2, 25, "T02"); // T02 -> L6
      sleep(1); // sleep(rand() % 3 + 1);

      printf("T02 in L7-L10 is waiting for L7\n");
      pthread_mutex_lock(&mutexF3);
      update_railway(2, 25, "   "); // NULL -> L6
      update_railway(4, 19, "T02"); // T02 -> L7
      sleep(1); // sleep(rand() % 3 + 1);
      printf("T02 in L7-L10 is waiting for L3-L8\n");
      
      pthread_mutex_lock(&mutexF1);
      pthread_mutex_unlock(&mutexF3);
      
      update_railway(4, 19, "   "); // NULL -> L7
      update_railway(2, 13, "T02"); // T02 -> L3(L8)
      sleep(1); // sleep(rand() % 3 + 1);
      pthread_mutex_unlock(&mutexF1);
      break;

    case 3:
      // T03 -> L4(L9) -> L7(L10) -> L11 -> L12 -> L8;
      update_railway(6, 25, "   "); // NULL -> L11
      update_railway(8, 13, "T03"); // T02 -> L12
      sleep(1); // sleep(rand() % 3 + 1);

      update_railway(8, 13, "   "); // NULL -> L12
      update_railway(6, 1, "T03"); // T02 -> L8
      sleep(1); // sleep(rand() % 3 + 1);

      printf("T03 is waiting for L9\n");
      pthread_mutex_lock(&mutexF2);
      update_railway(6, 1, "   "); // NULL -> L8
      update_railway(4, 7, "T03"); // T03 -> L4(L9)
      sleep(1); // sleep(rand() % 3 + 1);
      printf("T03 L4-L9 is waiting for L7-L10\n");
      
      pthread_mutex_unlock(&mutexF2); // Critical order, reversing these two lines causes deadlock
      pthread_mutex_lock(&mutexF3); // Critical order, reversing these two lines causes deadlock
      
      update_railway(4, 7, "   "); // NULL -> L4(L9)
      update_railway(4, 19, "T03"); // T03 -> L7(L10)
      sleep(1); // sleep(rand() % 3 + 1);
      update_railway(4, 19, "   "); // NULL -> L7(L10)
      update_railway(6, 25, "T03"); // T02 -> L11
      sleep(1); // sleep(rand() % 3 + 1);
      pthread_mutex_unlock(&mutexF3);
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

  pthread_t train_threads[3];
  int train_ids[3] = {1, 2, 3};

  pthread_create(&train_threads[0], NULL, train_thread, &train_ids[0]);
  pthread_create(&train_threads[1], NULL, train_thread, &train_ids[1]);
  pthread_create(&train_threads[2], NULL, train_thread, &train_ids[2]);

  for (int i = 0; i < 3; i++)
  {
    pthread_join(train_threads[i], NULL);
  }

  pthread_mutex_destroy(&mutexF1);
  pthread_mutex_destroy(&mutexF2);
  pthread_mutex_destroy(&mutexF3);

  return 0;
};