#include <stdio.h>
#include <stdlib.h>

int main() {
  // allocate memory for an array of 100 int
  int *data = (int *)malloc(100 * sizeof(int));

  // check if memory allocation succeeded
  if (data == NULL) {
    printf("Memory allocation failed\n");
    return 1; // exit if allocation failed
  }

  // set the value of the first element
  data[0] = 42;

  // free the memory
  free(data);

  // now try to access the freed memory (this is incorrect and leads to
  // undefined behavior)
  printf("After free, data[0] = %d\n", data[0]); // undefined behavior
  return 0;
}
