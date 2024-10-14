#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int pipe_fd[2];
  char buffer;

  // Create a pipe
  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    return 1;
  }

  // Fork to create a child process
  pid_t pid = fork();

  if (pid < 0) {
    // Fork failed
    perror("fork");
    return 1;
  } else if (pid == 0) {
    // Child process
    close(pipe_fd[0]); // Close the read end of the pipe
    printf("hello\n");

    // Write to the pipe to signal the parent
    write(pipe_fd[1], "x", 1);

    close(pipe_fd[1]); // Close the write end of the pipe
  } else {
    // Parent process
    close(pipe_fd[1]); // Close the write end of the pipe

    // Wait for the child to signal by reading from the pipe
    read(pipe_fd[0], &buffer, 1);

    // Now the parent can print
    printf("goodbye\n");

    close(pipe_fd[0]); // Close the read end of the pipe
  }

  return 0;
}
