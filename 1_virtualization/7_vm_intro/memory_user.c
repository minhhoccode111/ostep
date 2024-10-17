#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <number_of_megabytes>\n", argv[0]);
    return -1;
  }

  // Get the amount of memory to allocate in megabytes
  int megabytes = atoi(argv[1]);

  // Convert megabytes to bytes
  size_t size = megabytes * 1024 * 1024;

  // Allocate the memory
  int *array = (int *)malloc(size);
  if (array == NULL) {
    printf("Memory allocation failed!\n");
    return -1;
  }

  // Stream through the array, touching each entry indefinitely
  for (size_t i = 0;; i++) {
    array[i % (size / sizeof(int))] = i;
    if (i % 1000000 == 0) {
      printf("Still running, touched %zu elements...\n", i);
      sleep(1); // Just to slow down the loop and make it observable
    }
  }

  // Free the memory (we'll never reach here since the loop is infinite)
  free(array);

  return 0;
}
