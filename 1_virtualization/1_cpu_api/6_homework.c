#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork(); // Create a child process

  if (pid < 0) {
    // Fork failed
    perror("fork");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child process (PID: %d) is running.\n", getpid());
    sleep(1); // Simulate some work in the child process
    printf("Child process (PID: %d) is done.\n", getpid());
  } else {
    // Parent process
    printf(
        "Parent process (PID: %d) is waiting for child (PID: %d) to finish.\n",
        getpid(), pid);

    int status;
    pid_t result =
        waitpid(pid, &status, 0); // Wait for the specific child process

    if (result == -1) {
      perror("waitpid");
      return 1;
    }

    if (WIFEXITED(status)) {
      printf("Parent process: Child (PID: %d) finished with exit status %d.\n",
             result, WEXITSTATUS(status));
    } else {
      printf("Parent process: Child did not exit normally.\n");
    }
  }

  return 0;
}
