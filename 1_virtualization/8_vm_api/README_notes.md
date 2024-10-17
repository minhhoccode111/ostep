# Virtual Memory API

## Summary

This lesson is about memory management in UNIX and C programming, specifically focusing on how to allocate and manage memory. Here's a simplified summary:

1. **Types of Memory**:

   - **Stack Memory**: Automatically managed by the system; used for temporary data, such as variables in functions. It’s freed when the function exits.
   - **Heap Memory**: Manually managed by the programmer using functions like `malloc()` and `free()`. You need to be careful because it can lead to bugs if not handled properly.

2. **The `malloc()` Function**:

   - This function allocates memory on the heap. You specify the size of the memory block you need, and `malloc()` gives you a pointer to that memory. If it fails, it returns `NULL`.
   - You use the `sizeof()` function to get the right amount of memory for different data types.

3. **The `free()` Function**:

   - After you’re done using heap memory, you have to manually free it using `free()` to avoid memory leaks (unused memory that you can no longer access).

4. **Common Errors**:

   - Forgetting to allocate memory.
   - Not allocating enough memory, which leads to issues like buffer overflows.
   - Forgetting to initialize or free memory, causing memory leaks.
   - Freeing memory more than once (double free) or freeing the wrong memory (invalid free).

5. **Memory Debugging Tools**:
   - Tools like **gdb** (a debugger) and **valgrind** (a memory error detector) help you find bugs in memory usage, like uninitialized memory or memory leaks.

In simple terms, this lesson teaches how to allocate, manage, and free memory correctly in C, and emphasizes the importance of using tools to find and fix memory-related errors.
