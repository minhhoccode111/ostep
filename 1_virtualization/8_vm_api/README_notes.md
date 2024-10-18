# Virtual Memory API

- **Stack Memory**:

  - Memory automatically managed by the system, used for temporary variables in functions. It’s freed when a function finishes execution.

- **Heap Memory**:

  - Memory manually managed by the programmer, used for long-lived data that persists beyond a function's execution. Allocated using functions like `malloc()` and freed with `free()`.

- **`malloc()`**:

  - A function that allocates a block of memory on the heap. The size of the block is specified as an argument, and it returns a pointer to the allocated memory or `NULL` if it fails.

- **`free()`**:

  - A function that releases memory previously allocated by `malloc()` back to the system. If you don’t free memory, it causes a **memory leak**.

- **`sizeof()`**:

  - An operator used to determine the size (in bytes) of a data type or variable. Commonly used with `malloc()` to allocate the right amount of memory.

- **Memory Leak**:

  - A situation where memory is allocated but never freed, leading to wasted memory and potential crashes in long-running programs.

- **Buffer Overflow**:

  - A bug where a program writes more data to a block of memory than it was allocated, often leading to security vulnerabilities.

- **Dangling Pointer**:

  - A pointer that references memory that has already been freed. Using a dangling pointer can lead to crashes or undefined behavior.

- **Double Free**:

  - A bug where memory is freed more than once. This can corrupt the memory management system and cause crashes.

- **`calloc()`**:

  - A variant of `malloc()` that allocates memory and initializes all the allocated bytes to zero, preventing uninitialized reads.

- **`realloc()`**:

  - A function used to resize previously allocated memory blocks. It’s useful for dynamically growing or shrinking memory for structures like arrays.

- **Valgrind**:

  - A tool used to detect memory errors, such as leaks and invalid memory accesses, in programs. It helps in identifying bugs related to memory management.

- **GDB**:

  - The GNU Debugger, used to debug programs by inspecting memory, setting breakpoints, and stepping through code to find bugs.

- **Virtual Address Space**:

  - The memory management model used by modern operating systems, where each process is given its own view of memory, separate from other processes.

- **`sbrk()` and `brk()`**:

  - System calls used to adjust the size of the heap, though typically not used directly by programmers. Instead, these are managed by the `malloc()` library.

- **Segmentation Fault**:

  - An error that occurs when a program tries to access memory that it shouldn’t, often due to dereferencing null or invalid pointers.

- **Null Pointer**:

  - A pointer that doesn't point to any valid memory address. Dereferencing a null pointer typically leads to a segmentation fault.

- **Pointer Casting**:

  - The act of converting one pointer type to another, for example, casting the result of `malloc()` (which returns a `void*`) to a specific data type like `int*`.

- **Uninitialized Read**:

  - Accessing memory that has been allocated but not initialized, leading to unpredictable behavior as the values in that memory are random.

- **Anonymous Memory Region**:

  - A block of memory allocated using system calls like `mmap()` which is not associated with any file but can be treated like heap memory. Useful for low-level memory management.

- **Garbage Collection**:

  - A feature in higher-level programming languages where the system automatically frees memory that is no longer in use. C does not have garbage collection, requiring manual memory management.

- **Memory Allocation Library**:

  - A collection of functions like `malloc()`, `free()`, `calloc()`, and `realloc()` that manage heap memory for a program.

- **`strcpy()` and `strdup()`**:

  - `strcpy()` copies a string from a source to a destination, requiring enough allocated memory in the destination. `strdup()` both allocates memory for the string and copies it, making it more convenient.

- **`mmap()`**:

  - A system call used to map files or devices into memory. It can also be used to allocate anonymous memory, which can be managed like a heap.

- **Overwriting Memory**:

  - When a program accidentally writes data past the end of a memory block (e.g., array overflow), causing unpredictable behavior or security vulnerabilities.

- **Memory Fragmentation**:

  - A condition where free memory is broken into small, non-contiguous blocks, making it difficult to allocate large memory chunks efficiently.

- **Address Space Layout**:

  - Refers to how different memory segments (stack, heap, code) are organized within a program’s virtual address space.

- **Heap Overflow**:

  - Similar to buffer overflow, but specifically refers to writing beyond the allocated space in the heap, which may corrupt data or crash the program.

- **Use-After-Free**:

  - A bug that occurs when a program continues to use memory after it has been freed, which can cause unpredictable behavior, crashes, or security exploits.

- **Memory Alignment**:
  - The process of organizing data in memory according to specific boundaries to optimize access speed. Misaligned data accesses can lead to performance degradation or hardware faults.

## Summary

This lesson is about memory management in UNIX and C programming, specifically focusing on how to allocate and manage memory. Here's a simplified summary:

- **Types of Memory**:

  - **Stack Memory**: Automatically managed by the system; used for temporary data, such as variables in functions. It’s freed when the function exits.
  - **Heap Memory**: Manually managed by the programmer using functions like `malloc()` and `free()`. You need to be careful because it can lead to bugs if not handled properly.

- **The `malloc()` Function**:

  - This function allocates memory on the heap. You specify the size of the memory block you need, and `malloc()` gives you a pointer to that memory. If it fails, it returns `NULL`.
  - You use the `sizeof()` function to get the right amount of memory for different data types.

- **The `free()` Function**:

  - After you’re done using heap memory, you have to manually free it using `free()` to avoid memory leaks (unused memory that you can no longer access).

- **Common Errors**:

  - Forgetting to allocate memory.
  - Not allocating enough memory, which leads to issues like buffer overflows.
  - Forgetting to initialize or free memory, causing memory leaks.
  - Freeing memory more than once (double free) or freeing the wrong memory (invalid free).

- **Memory Debugging Tools**:
  - Tools like **gdb** (a debugger) and **valgrind** (a memory error detector) help you find bugs in memory usage, like uninitialized memory or memory leaks.

In simple terms, this lesson teaches how to allocate, manage, and free memory correctly in C, and emphasizes the importance of using tools to find and fix memory-related errors.
