#include <stdio.h>
#include <stdlib.h>

int main() {
  // allocate memory for an array of 100 integers
  int *data = (int *)malloc(100 * sizeof(int));

  // check if memory allocation succeeded
  if (data == NULL) {
    printf("Memory allocation failed\n");
    return 1; // exit if allocation failed

    // attempt to set data[100] to 0 (this will cause out-of-bounds access)
    data[100] = 0; // incorrect, should cause a problem

    // print the value at data[100] (this is invalid, but for demonstration)
    printf("data[100] = %d\n", data[100]); // undefined behavior

    // free the allocated memory
    free(data);

    return 0;
  }
}
