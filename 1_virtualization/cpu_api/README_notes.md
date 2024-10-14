# Process API

- `fork()` creates a new process, and both child and parent continue from the same point after the fork call
- `wait()` ensures the child completes before the parent continues
- `exec()` replaces the child process with a new executable (e.g., `wc`)
- `kill()` sends signals to processes, enabling control over their execution
- Process ID (PID): Each process has a unique identifier called a process ID
- Child Process: Created by the `fork()` system call; it's almost identical to the parent but starts from where the fork occurred
- Parent Process: The process that creates the child process using `fork()`
- Standard Input/Output Redirection: Redirection of the output of a process (e.g., using `>`) allows output to be sent to a file or another process
- Superuser (root): A special user with elevated privileges to control all processes, including terminating them or performing administrative tasks
- Shells: Commonly use `fork()`, `exec()`, and `wait()` to launch and manage user commands. This enables features like input/output redirection and pipelines without changing the core programs
- File Descriptors: Open file descriptors are passed across exec calls, making input/output redirection possible
- Pipes: The `pipe()` system call connects the output of one process to the input of another, allowing chaining of commands (e.g., `grep | wc`)
