#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork(); // Create a child process

  if (pid < 0) {
    // Fork failed
    perror("fork");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child process: This will be printed before closing STDOUT.\n");

    // Close the standard output file descriptor
    close(STDOUT_FILENO);

    // Attempt to print after closing STDOUT
    printf("Child process: You won't see this because STDOUT is closed.\n");

    // Optionally flush output buffers (although STDOUT is closed)
    fflush(stdout);
  } else {
    // Parent process
    printf("Parent process: Waiting for child to complete.\n");
    sleep(1); // Give the child time to execute
  }

  return 0;
}
