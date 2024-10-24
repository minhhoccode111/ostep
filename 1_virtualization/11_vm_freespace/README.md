# Virtual Memory Freespace

- external fragmentation
- internal fragmentation
- combat fragmentation
-

## Summary

Chapter 17 from the OSTEP book focuses on **Free-Space Management**, a crucial part of memory management systems. It discusses the challenges of managing free memory space, especially when dealing with variable-sized units, which leads to **external fragmentation**. This occurs when free memory is split into small pieces, preventing large contiguous allocations, even though enough free space is available overall.

Key points from the chapter include:

- **Fragmentation**: The core problem of external fragmentation arises when the memory becomes divided into scattered free blocks. Even if the total free memory is sufficient, a request might fail due to lack of contiguous space.
- **Memory Allocation**: Various methods for managing free memory include:

  - **Best Fit**: Finds the smallest available block that fits the request, minimizing wasted space but often leaving many small unusable fragments.
  - **Worst Fit**: Allocates the largest block, aiming to keep large blocks available but often leading to inefficient use of memory.
  - **First Fit**: Returns the first block large enough to satisfy the request, balancing speed and memory usage.
  - **Next Fit**: Similar to First Fit but continues searching from where the last search left off, spreading allocations more evenly.

- **Coalescing**: This technique merges adjacent free blocks into larger ones to combat fragmentation, allowing larger allocations to succeed.

- **Splitting**: A method where a free block is divided to accommodate a request, with the remaining portion added back to the free list.

- **Free Lists**: The data structure used to keep track of free memory, and how it can be embedded in the free space itself to minimize overhead.

- **Advanced Techniques**: Approaches like **Segregated Lists** and **Buddy Allocation** are discussed. Segregated lists manage objects of similar sizes separately, reducing fragmentation. Buddy Allocation ensures easier coalescing by splitting memory into power-of-two-sized blocks.

In summary, free-space management is a balancing act between minimizing fragmentation and ensuring quick allocation. Various strategies and techniques are employed to manage memory efficiently, but each comes with trade-offs depending on the workload and memory access patterns.
