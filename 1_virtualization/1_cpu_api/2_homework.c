#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  char parent_message[] = "Parent writing\n";
  char child_message[] = "Child writing\n";

  // Open a file with the open() system call
  fd = open("2_homework_output", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

  if (fd < 0) {
    // If opening the file fails
    printf("Error opening file\n");
    return 1;
  }

  // Call fork() to create a new process
  pid_t pid = fork();

  if (pid < 0) {
    // Fork failed
    printf("Fork failed\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    write(fd, child_message, sizeof(child_message) - 1); // Write to file
  } else {
    // Parent process
    write(fd, parent_message, sizeof(parent_message) - 1); // Write to file
  }

  // Both parent and child close the file descriptor
  close(fd);

  return 0;
}
