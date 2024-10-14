#include "common.h"
#include <stdio.h>
#include <stdlib.h>

// code that loops and prints
int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: cpu <string>\n");
    exit(1);
  }
  char *str = argv[1];

  while (1) {
    printf("%s\n", str);
    // wait 1 second
    Spin(1);
  }
  return 0;
}
