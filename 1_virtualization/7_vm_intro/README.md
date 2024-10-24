# Virtual Memory Introduction

## Summary

1. **Early Computer Systems**: In the beginning, computers were simple, and users didn’t expect much. The operating system (OS) was just a set of routines that handled one running program at a time, without much abstraction.

2. **Multiprogramming & Time Sharing**: As computers became expensive, users started sharing machines. This led to **multiprogramming**, where several processes could be loaded into memory at once, and the OS would switch between them. Time-sharing allowed multiple users to interact with the machine simultaneously.

3. **Address Space**: The OS creates a virtual view of memory for each program called an **address space**. This contains the program’s code, stack (for function calls), and heap (for dynamic memory like variables). It allows programs to "think" they have their own memory, even though they’re sharing the physical memory.

4. **Virtual Memory**: The OS **virtualizes memory** by creating an illusion for programs, making them believe they have large, private memory spaces. The OS translates virtual addresses (used by programs) to physical addresses (actual memory). This also includes protection so programs can't interfere with each other.

5. **Goals of Virtual Memory**:
   - **Transparency**: The program shouldn’t know it’s using virtual memory.
   - **Efficiency**: Memory management should be fast and use minimal resources.
   - **Protection**: Programs must be isolated to avoid affecting each other.

In short, virtual memory helps make modern systems efficient by allowing multiple programs to run simultaneously, share memory safely, and use memory more effectively.
