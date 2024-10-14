# Introduction to Operating Systems

- **Von Neumann Model**: A program executes instructions fetched from memory, decoded, and executed in sequence.
- **Operating System (OS)**: A body of software that virtualizes physical resources (CPU, memory, disk) to make the system easy to use.
  - **Virtualization**: OS transforms physical resources into more general, easy-to-use virtual resources (e.g., virtual CPU, virtual memory).
- **Resource Manager**: The OS manages resources like CPU, memory, and disk, ensuring efficient and fair usage.
- **System Calls**: Interface provided by the OS for programs to run, allocate memory, access files, etc.
- **Multiprogramming**: The OS loads multiple jobs into memory and switches between them to improve CPU utilization, particularly during I/O operations.
- **Concurrency**: Managing multiple tasks at once introduces challenges, like ensuring correct program execution when tasks run simultaneously (handled in later chapters).
- **Persistence**: OS manages long-term data storage through file systems, enabling reliable data storage on hardware (e.g., SSDs, HDDs).
- **Protection and Isolation**: The OS isolates processes from each other to prevent interference, ensuring system stability and security.
- **Historical Evolution**:
  - Early OSes were just libraries for common tasks, run one program at a time.
  - The concept of **system calls** was introduced to control privileged operations.
  - **Multiprogramming** allowed efficient use of CPU and memory, handling multiple jobs concurrently.
  - **UNIX**: A major advancement in OS design, emphasizing simplicity, small reusable programs, and a robust environment for developers.
- **Modern OS Goals**:
  - High performance, protection, energy efficiency, reliability, and security.

### Key Concepts

- **Process**: A running program.
- **Thread**: A function running within the same memory space as other functions.
- **CPU Virtualization**: Creating the illusion of multiple CPUs to run multiple programs.
- **Memory Virtualization**: Each program has its own private memory space (address space) that the OS maps to physical memory.
