# Homework (Code)

In this homework, you will gain some familiarity with memory allocation. First, you’ll write some buggy programs (fun!). Then, you’ll use some tools to help you find the bugs you inserted. Then, you will realize how awesome these tools are and use them in the future, thus making yourself more happy and productive. The tools are the debugger (e.g., gdb) and a memory-bug detector called valgrind.

### Questions

1. First, write a simple program called `null.c` that creates a pointer to an integer, sets it to `NULL`, and then tries to dereference it. Compile this into an executable called `null`. What happens when you run this program?

Answer: `Segmentation fault (core dumped)` Error

2. Next, compile this program with symbol information included (with the `-g` flag). Doing so lets you put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing `gdb null` and then, once `gdb` is running, typing `run`. What does `gdb` show you?

Output: `gdb null`

```
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from null...
(gdb) run
Starting program: /home/mhc/project/ostep/1_virtualization/8_vm_api/null
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at null.c:5
5         printf("try to dereference the pointer: %d\n", *pointer);
```

3. Finally, use the `valgrind` tool on this program. We’ll use `memcheck` that is a part of valgrind to analyze what happens. Run this by typing in the following: `valgrind --leak-check=yes null`. What happens when you run this? Can you interpret the output from the tool?

Output: `valgrind --leak-check=yes ./null`

```
==43148== Command: ./null
==43148==
==43148== Invalid read of size 4
==43148==    at 0x109161: main (null.c:5)
==43148==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==43148==
==43148==
==43148== Process terminating with default action of signal 11 (SIGSEGV)
==43148==  Access not within mapped region at address 0x0
==43148==    at 0x109161: main (null.c:5)
==43148==  If you believe this happened as a result of a stack
==43148==  overflow in your program's main thread (unlikely but
==43148==  possible), you can try to increase the size of the
==43148==  main thread stack using the --main-stacksize= flag.
==43148==  The main thread stack size used in this run was 8388608.
==43148==
==43148== HEAP SUMMARY:
==43148==     in use at exit: 0 bytes in 0 blocks
==43148==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==43148==
==43148== All heap blocks were freed -- no leaks are possible
==43148==
==43148== For lists of detected and suppressed errors, rerun with: -s
==43148== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault (core dumped)
```

4. Write a simple program that allocates memory using `malloc()` but forgets to free it before exiting. What happens when this program runs? Can you use `gdb` to find any problems with it? How about `valgrind` (again with the `--leak-check=yes` flag)?

Output: `gdb malloc`

```
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from malloc...
(gdb) run
Starting program: /home/mhc/project/ostep/1_virtualization/8_vm_api/malloc
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Inferior 1 (process 45941) exited normally]
```

Output: `valgrind --leak-check=yes ./malloc`

```
==46585== Command: ./malloc
==46585==
==46585==
==46585== HEAP SUMMARY:
==46585==     in use at exit: 4 bytes in 1 blocks
==46585==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==46585==
==46585== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==46585==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==46585==    by 0x109166: main (malloc.c:7)
==46585==
==46585== LEAK SUMMARY:
==46585==    definitely lost: 4 bytes in 1 blocks
==46585==    indirectly lost: 0 bytes in 0 blocks
==46585==      possibly lost: 0 bytes in 0 blocks
==46585==    still reachable: 0 bytes in 0 blocks
==46585==         suppressed: 0 bytes in 0 blocks
==46585==
==46585== For lists of detected and suppressed errors, rerun with: -s
==46585== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

5. Write a program that creates an array of integers called `data` of size 100 using `malloc`; then, set `data[100]` to zero. What happens when you run this program? What happens when you run this program using `valgrind`? Is the program correct?

Answer: The program runs successfully but 2 errors using `valgrind`

Output: `valgrind --leak-check=yes ./array0`

```
==52833== Command: ./array
==52833==
==52833== Invalid write of size 4
==52833==    at 0x1091EA: main (array.c:15)
==52833==  Address 0x4a9c1d0 is 0 bytes after a block of size 400 alloc'd
==52833==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52833==    by 0x1091BE: main (array.c:6)
==52833==
==52833== Invalid read of size 4
==52833==    at 0x1091FA: main (array.c:18)
==52833==  Address 0x4a9c1d0 is 0 bytes after a block of size 400 alloc'd
==52833==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==52833==    by 0x1091BE: main (array.c:6)
==52833==
data[100] = 0
==52833==
==52833== HEAP SUMMARY:
==52833==     in use at exit: 0 bytes in 0 blocks
==52833==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==52833==
==52833== All heap blocks were freed -- no leaks are possible
==52833==
==52833== For lists of detected and suppressed errors, rerun with: -s
==52833== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use `valgrind` on it?

Answer: The program run and print something like `-1913611356` value (which is incorrect)

Output: `valgrind --leak-check=yes ./array1`

```
==57582== Command: ./array1
==57582==
==57582== Invalid read of size 4
==57582==    at 0x1091FA: main (array1.c:22)
==57582==  Address 0x4a9c040 is 0 bytes inside a block of size 400 free'd
==57582==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==57582==    by 0x1091F5: main (array1.c:18)
==57582==  Block was alloc'd at
==57582==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==57582==    by 0x1091BE: main (array1.c:6)
==57582==
After free, data[0] = 42
==57582==
==57582== HEAP SUMMARY:
==57582==     in use at exit: 0 bytes in 0 blocks
==57582==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==57582==
==57582== All heap blocks were freed -- no leaks are possible
==57582==
==57582== For lists of detected and suppressed errors, rerun with: -s
==57582== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

7. Now pass a funny value to `free` (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

Answer: only the pointer returned by `malloc()` should be passed to `free()`; otherwise, you risk undefined behavior, which may result in crashes or memory corruption

8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use `realloc()` to manage the vector. Use an array to store the vector's elements; when a user adds an entry to the vector, use `realloc()` to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use `valgrind` to help you find bugs.

9. Spend more time and read about using `gdb` and `valgrind`. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.
