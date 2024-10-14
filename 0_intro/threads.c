// #include "common.h"
#include "common_threads.h"
#include <stdio.h>
#include <stdlib.h>

// Global variable to be shared between threads
volatile int counter =
    0;     // Volatile to prevent compiler optimization for threading
int loops; // Number of times each thread will increment the counter

// Function executed by each thread
void *worker(void *arg) {
  int i;
  // Each thread increments the counter 'loops' times
  for (i = 0; i < loops; i++) {
    counter++; // Non-atomic increment (prone to race conditions)
  }
  return NULL; // Return NULL when done
}

int main(int argc, char *argv[]) {
  // Check if the user provided the correct number of arguments
  if (argc != 2) {
    // If not, print usage instructions and exit
    fprintf(stderr, "usage: threads <loops>\n");
    exit(1);
  }

  // Convert the argument to an integer (the number of loops for each thread)
  loops = atoi(argv[1]);

  // Declare two thread handles
  pthread_t p1, p2;

  // Print the initial value of the counter (should be 0)
  printf("Initial value : %d\n", counter);

  // Create two threads, both running the 'worker' function
  Pthread_create(&p1, NULL, worker, NULL);
  Pthread_create(&p2, NULL, worker, NULL);

  // Wait for both threads to finish execution
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);

  // Print the final value of the counter after both threads have finished
  // Ideally, the final value should be 2 * loops, but race conditions can occur
  printf("Final value   : %d\n", counter);

  return 0; // Program ends
}
