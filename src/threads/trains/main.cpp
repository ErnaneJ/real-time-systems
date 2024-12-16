#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

pthread_mutex_t mutexTrackL3, mutexTrackL5;

char railway_state[5][100] = {
  "   ---[   ]--- ---[   ]--- ---[   ]---- ",
  "  |           |           |            |",
  "[   ]       [   ]       [   ]        [   ]",
  "  |           |           |            |",
  "   ---[   ]--- ---[   ]--- ---[   ]---- "
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
  for (int i = 0; i < 5; i++)
  {
    if (i != 2)
    {
      printf("│%s  │\n", railway_state[i]);
    }
    else
    {
      printf("│%s│\n", railway_state[i]);
    }
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
      update_railway(0, 7, "T01"); // Track 2
      sleep(rand() % 3 + 1);

      pthread_mutex_lock(&mutexTrackL3);
      update_railway(0, 7, "   ");  // Track 2
      update_railway(2, 13, "T01"); // Track 3
      sleep(rand() % 3 + 1);
      pthread_mutex_unlock(&mutexTrackL3);

      update_railway(2, 13, "   "); // Track 3
      update_railway(4, 7, "T01");  // Track 4
      sleep(rand() % 3 + 1);

      update_railway(4, 7, "   "); // Track 4
      update_railway(2, 1, "T01"); // Track 1
      sleep(rand() % 3 + 1);
      update_railway(2, 1, "   "); // Track 1
      break;

    case 2:
      update_railway(4, 19, "T02"); // Track 6
      sleep(rand() % 3 + 1);

      pthread_mutex_lock(&mutexTrackL3);
      update_railway(4, 19, "   "); // Track 6
      update_railway(2, 13, "T02"); // Track 3
      sleep(rand() % 3 + 1);
      update_railway(2, 13, "   "); // Track 3
      pthread_mutex_unlock(&mutexTrackL3);

      update_railway(0, 19, "T02"); // Track 7
      sleep(rand() % 3 + 1);

      pthread_mutex_lock(&mutexTrackL5);
      update_railway(0, 19, "   "); // Track 7
      update_railway(2, 25, "T02"); // Track 5
      sleep(rand() % 3 + 1);
      update_railway(2, 25, "   "); // Track 5
      pthread_mutex_unlock(&mutexTrackL5);
      break;

    case 3:
      update_railway(4, 31, "T03"); // Track 9
      sleep(rand() % 3 + 1);

      pthread_mutex_lock(&mutexTrackL5);
      update_railway(4, 31, "   "); // Track 9
      update_railway(2, 25, "T03"); // Track 5
      sleep(rand() % 3 + 1);
      update_railway(2, 25, "   "); // Track 5
      pthread_mutex_unlock(&mutexTrackL5);

      update_railway(0, 31, "T03"); // Track 10
      sleep(rand() % 3 + 1);
      update_railway(0, 31, "   "); // Track 10

      update_railway(2, 38, "T03"); // Track 8
      sleep(rand() % 3 + 1);
      update_railway(2, 38, "   "); // Track 8
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
  pthread_mutex_init(&mutexTrackL3, NULL);
  pthread_mutex_init(&mutexTrackL5, NULL);

  pthread_t train_threads[3];
  int train_ids[3] = {1, 2, 3};

  pthread_create(&train_threads[0], NULL, train_thread, &train_ids[0]);
  pthread_create(&train_threads[1], NULL, train_thread, &train_ids[1]);
  pthread_create(&train_threads[2], NULL, train_thread, &train_ids[2]);

  for (int i = 0; i < 3; i++)
  {
    pthread_join(train_threads[i], NULL);
  }

  pthread_mutex_destroy(&mutexTrackL3);
  pthread_mutex_destroy(&mutexTrackL5);

  return 0;
};