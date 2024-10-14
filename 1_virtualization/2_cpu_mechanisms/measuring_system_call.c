#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
  struct timeval start, end;
  int iterations = 1000000; // Number of iterations
  char buffer[1];

  // Start timing
  gettimeofday(&start, NULL);

  for (int i = 0; i < iterations; i++) {
    read(0, buffer, 0); // Perform a 0-byte read system call
  }

  // End timing
  gettimeofday(&end, NULL);

  // Calculate time in microseconds
  long seconds = end.tv_sec - start.tv_sec;
  long microseconds = end.tv_usec - start.tv_usec;
  long total_time = (seconds * 1000000) + microseconds;

  printf("Time taken for %d system calls: %ld microseconds\n", iterations,
         total_time);
  printf("Average time per system call: %f microseconds\n",
         (double)total_time / iterations);

  return 0;
}
