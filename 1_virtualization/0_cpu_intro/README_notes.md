# CPU Intro

Provides an introduction to central processing units (CPUs), covering their history, basic structure, and fundamental operation in computing systems

- Process: is a running program
- Virtualizing: to create a illusion of many CPUs
- Time sharing: allows users to run as many concurrent processes as they would like; the potential cost is performance, as each will run more slowly if the CPU(s) must be shared
- Space sharing: where a resource is divided (in space) among those who wish to use it
- Mechanisms: are low-level methods or protocols that implement a needed piece of functionality
  - providing answer to a _how_ question. e.g how does an operating sysatem perform a context switch?
- Policies: are algorithms for making some kind of decision within the OS
  - providing answer to _which_ question. e.g. which process should the operating system run right now
- Context switch: gives the OS the ability to stop running one program and start running another on a given CPU
- Scheduling policy: decide which program should the OS run, using historical information, workload knowledge, performance metrics
- machine state: what a program can read or update when it is running
- address space: is part of the process machine state, the memory that the process can address
- registers: is part of the process machine state; many instructions explicitly read or update registers and thus clearly they are important to the execution of the process
- program counter (PC) aka instruction pointer (IP): tell us which instruction of the program will execute next
- stack pointer: similar to instruction pointer
- frame pointer: similar to instruction pointer
- modularity: change policies without having to rethink the mechanism
- Process API
  - Create
  - Destroy
  - Wait
  - Miscellaneous Control
  - Status
- load its code: the first thing that the OS must do to run a program
- flash-based SSDs:
- executable format: programs reside on disk
- eagerly: (in early or simple OSes)loading pieces of code or data all at once before running the program
- lazily: (in modern OSes) loading pieces of code or data only as they are needed during program execution
- paging:
- swapping:
- run-time stack (or just stack): C programs use the stack for local variables, function parameters and return addresses
- heap: C programs use the heap for explicitly requested dynamically-allocated data
- file descriptors: let programs easily read input from the terminal and print output to the screen
- process states: states a process can be in at a given time
  - running: a process is running on a processor, mean it is executing instructions
  - ready: a process is ready to run but for some reason the OS has chosen not to runit at this given moment
  - blocked: a process has performed some kind of operation that makes it not ready to run until some other event takes place, a common example: when a process initiates an I/O request to a disk, it becomes blocked and thus some other process can use the processor
- scheduled: a process move from ready to running
- descheduled: a process move from running to ready
- scheduler: make decisions which process should run
- process list: to track the state of each process of system that has the ability to run multiple programs at once
  - or task list
- process control block (PCB): the individual stucture that store information about a process
  - or process descriptor
- register context: refers to the saved state of a CPU's registers (e.g. program counter, stack pointer, general-purpose registers) during a context switch, allowing processes or threads to resume execution later without losing progress
- context switch: saving the state of currently running process or thread and loading the state of another, allowing multitasking and process management
- zombie: a process could be placed in a final state where it has exited but has not yet been cleaned up (in UNIX-based systems, this is called the zombie state)

### Key Process Terms

- the process is the major OS abstraction of a running program. At any point in time, the process can be described by its state: the contents of memory in its address space, the contents of CPU registers (including the program counter and stack pointer, among others), and information about i/o (such as open files which can be read or written)
- the process API consists of called programs can make related to processes. Typically, this includes creation, destruction, and other useful calls
- process exist in one of many different process states, including running, ready to run, and blocked. Differnt events (e.g. getting scheduled or descheduled, or waiting for an i/o to complete) transition a process from one of these states to the other
- a process list contains information about all processes in the system. Each entry is found in what is sometimes called a process control block (PCB), which is really just a structure that contains information about a specific process
