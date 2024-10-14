# CPU Mechanisms

- direct execution: running a user process directly on the cpu to achieve high performance.
- limited direct execution: running a process directly on the cpu, but with limits imposed by the os to retain control, like restricted access to certain operations.
- user mode: a restricted cpu mode where user processes run with limited access to system resources.
- kernel mode: a privileged cpu mode where the operating system runs with full control over hardware and resources.
- system call: a request from a user process to the os for performing privileged operations like i/o, memory management, etc.
- trap: an instruction that switches the cpu from user mode to kernel mode, allowing the os to handle privileged tasks requested by the process.
- return-from-trap: a special instruction that switches the cpu from kernel mode back to user mode after the os completes handling a system call or interrupt.
- kernel stack: a dedicated memory space for storing the cpu's state and variables during kernel mode operations, including system calls and interrupts.
- trap table: a table set up by the os at boot time, specifying the addresses of code to handle various exceptional events like system calls and interrupts.
- trap handlers: code functions specified in the trap table that handle specific system calls or interrupts when a trap is triggered.
- system-call number: a unique identifier for each system call, used by the os to determine which function to execute when a system call is made.
- cooperative: a scheduling approach where processes voluntarily yield control to the os by making system calls.
- non-cooperative: a scheduling approach where the os forcibly regains control of the cpu, usually through a timer interrupt, without relying on process cooperation.
- interrupt handler: the code executed by the os in response to an interrupt, such as a timer or device event, to handle the event.
- scheduler: the os component responsible for deciding which process runs on the cpu at any given time, often triggered by interrupts or system calls.
- context switch: the process of saving the state of one running process and restoring the state of another, allowing the os to switch between processes.
- kernel stack: (duplicate) a stack used by the operating system to save cpu state during kernel operations.
- disable interrupt: a technique where the os temporarily disables hardware interrupts to ensure that critical operations, like handling multiple interrupts, are not interrupted further.

## Key CPU virtualization terms (mechanisms)

- The CPU should support at least two modes of execution: a restricted user mode and a privileged (non-restricted) kernel mode
- Typical user applications run in user mode, and use a system call to trap into the kernel to request operating system services
- The trap instruction saves register state carefully, changes the hardware status to kernel mode, and jumps into the OS to a pre-specified destination: the trap table
- When the OS finishes servicing a system call, it returns to the user program via another special return-from-trap instruction, which reduces privilege and returns control to the instruction after the trap that jumped into the OS
- The trap tables must be set up by the OS at boot time, and make sure that they connot be readily modified by user programs. All of this part of the limited direct execution protocol which runs programs efficiently but without loss of OS control
- Once a program is running, the OS must use hardware mechanisms to ensure the user program does not run forever, namely the timer interrupt. This approach is a non-cooperative approach to CPU scheduling
- Sometimes the OS, during a timer interrupt or system call, might wish to switch from running the current process to a different one, a low-level technique known as a context switch
