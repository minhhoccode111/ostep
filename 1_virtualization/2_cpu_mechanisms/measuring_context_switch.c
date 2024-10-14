#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipe1[2], pipe2[2];
  pipe(pipe1); // Pipe from parent to child
  pipe(pipe2); // Pipe from child to parent

  struct timeval start, end;
  int iterations = 100000; // Number of iterations
  char buffer[1] = {'a'};

  if (fork() == 0) { // Child process
    for (int i = 0; i < iterations; i++) {
      read(pipe1[0], buffer, 1);  // Read from parent
      write(pipe2[1], buffer, 1); // Write back to parent
    }
  } else { // Parent process
    // Start timing
    gettimeofday(&start, NULL);

    for (int i = 0; i < iterations; i++) {
      write(pipe1[1], buffer, 1); // Write to child
      read(pipe2[0], buffer, 1);  // Read back from child
    }

    // End timing
    gettimeofday(&end, NULL);

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long total_time = (seconds * 1000000) + microseconds;

    printf("Time taken for %d context switches: %ld microseconds\n", iterations,
           total_time);
    printf("Average time per context switch: %f microseconds\n",
           (double)total_time / (iterations * 2));

    wait(NULL); // Wait for child to finish
  }

  return 0;
}
