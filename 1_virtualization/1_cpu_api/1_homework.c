
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int x = 100; // Initialize variable x

  printf("Before fork: x = %d\n", x);

  pid_t pid = fork(); // Create a new process

  if (pid < 0) {
    // Fork failed
    fprintf(stderr, "Fork failed\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child process: x = %d\n", x);
    x = 200; // Change x in child
    printf("Child process: x changed to %d\n", x);
  } else {
    // Parent process
    printf("Parent process: x = %d\n", x);
    x = 300; // Change x in parent
    printf("Parent process: x changed to %d\n", x);
  }

  // Both child and parent process will execute this
  printf("Process %d: Final value of x = %d\n", getpid(), x);

  return 0;
}
