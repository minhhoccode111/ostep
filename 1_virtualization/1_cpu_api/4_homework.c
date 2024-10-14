#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t pid = fork(); // Create a child process

  if (pid < 0) {
    // Fork failed
    perror("fork");
    return 1;
  } else if (pid == 0) {
    // Child process: replace its memory space with the /bin/ls program

    // Example 1: execl()
    execl("/bin/ls", "ls", "-l", NULL); // execl(path, arg0, arg1, ..., NULL)
    perror("execl");

    // Example 2: execle()
    char *envp[] = {"HOME=/usr/home", "LOGNAME=home", NULL};
    execle("/bin/ls", "ls", "-l", NULL,
           envp); // execle(path, arg0, arg1, ..., NULL, envp)
    perror("execle");

    // Example 3: execlp()
    execlp("ls", "ls", "-l", NULL); // execlp(file, arg0, arg1, ..., NULL)
    perror("execlp");

    // Example 4: execv()
    char *args[] = {"ls", "-l", NULL};
    execv("/bin/ls", args); // execv(path, args)
    perror("execv");

    // Example 5: execvp()
    execvp("ls", args); // execvp(file, args)
    perror("execvp");

    // Removed execvpe() as it may not be supported on all systems
    exit(1); // Exit if exec() fails
  } else {
    // Parent process
    printf("Parent process: Child has been replaced by /bin/ls\n");
  }

  return 0;
}
