#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pipe_fd[2]; // Array to hold the file descriptors for the pipe
  pid_t pid1, pid2;

  // Create a pipe
  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    return 1;
  }

  // Create the first child
  pid1 = fork();

  if (pid1 < 0) {
    perror("fork");
    return 1;
  } else if (pid1 == 0) {
    // First child process

    // Close the read end of the pipe
    close(pipe_fd[0]);

    // Redirect standard output to the write end of the pipe
    dup2(pipe_fd[1], STDOUT_FILENO);

    // Close the now-unused write end of the pipe
    close(pipe_fd[1]);

    // Execute a command that generates output, e.g., `ls`
    execlp("ls", "ls", NULL);

    // If exec fails
    perror("execlp");
    return 1;
  }

  // Create the second child
  pid2 = fork();

  if (pid2 < 0) {
    perror("fork");
    return 1;
  } else if (pid2 == 0) {
    // Second child process

    // Close the write end of the pipe
    close(pipe_fd[1]);

    // Redirect standard input to the read end of the pipe
    dup2(pipe_fd[0], STDIN_FILENO);

    // Close the now-unused read end of the pipe
    close(pipe_fd[0]);

    // Execute a command that reads input, e.g., `wc -l` (to count lines)
    execlp("wc", "wc", "-l", NULL);

    // If exec fails
    perror("execlp");
    return 1;
  }

  // Parent process

  // Close both ends of the pipe, as they are no longer needed by the parent
  close(pipe_fd[0]);
  close(pipe_fd[1]);

  // Wait for both child processes to finish
  wait(NULL); // Wait for the first child
  wait(NULL); // Wait for the second child

  return 0;
}
