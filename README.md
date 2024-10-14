# Operating Systems: Three Easy Pieces Book

### [Book Content](https://pages.cs.wisc.edu/~remzi/OSTEP/)

### [Book Source Code](https://github.com/remzi-arpacidusseau/ostep-code)

### [Book Homework](https://github.com/remzi-arpacidusseau/ostep-homework/)

### [Book Projects](https://github.com/remzi-arpacidusseau/ostep-projects)

### How to use this repo

- Each folder usually a chapter (e.g., `cpu_api`)
- I read the chapter's content (e.g., `cpu_api.pdf`)
- I take notes to `README_notes.md`
- I learn more about the chapter's code example with `README_code.md`
- I do chapter's homework with `README_homework.md` (both `simulation` and `coding`)

## Virtualization

How the OS abstracts and manages hardware resources to create the illusion of separate processes.

CPU Virtualization Chapters:

- Processes
- Process API
- Direct Execution
- CPU Scheduling
- Multi-level Feedback
- Lottery Scheduling
- Multi-CPU Scheduling

Memory Virtualization Chapters:

- Address Spaces
- Memory API
- Address Translation
- Segmentation
- Free Space Management
- Introduction to Paging
- Translation Lookaside Buffers
- Advanced Page Tables
- Swapping: Mechanisms
- Swapping: Policies
- Complete VM Systems

## Concurrency

Techniques for managing multiple tasks and processes running at the same time.

Concurrency Chapters:

- Concurrency and Threads
- Threads API
- Locks
- Locked Data Structures
- Condition Variables
- Semaphores
- Concurrency Bugs
- Event-based Concurrency

## Persistence

How data is stored and managed, ensuring durability and reliability.

Persistence Chapters:

- I/O Devices
- Hard Disk Drives
- Redundant Disk Arrays (RAID)
- Files and Directories
- File System Implementation
- Fast File System (FFS)
- FSCK and Journaling
- Log-structured File System (LFS)
- Flash-based SSDs
- Data Integrity and Protection
- Distributed Systems
- Network File System (NFS)
- Andrew File System (AFS)

## Security

Mechanisms and policies used by the operating system to protect data, resources, and users from unauthorized access and malicious attacks.

Security Chapters:

- Intro Security
- Authentication
- Access Control
- Cryptography
- Distributed
