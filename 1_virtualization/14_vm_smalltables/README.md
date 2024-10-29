# Virtual Memory Smaller Tables

## Why it matters

- Traditional linear page tables grow too large as systems scale, consuming substantial memory resources that could be better utilized by applications
- Manageing this efficiently is crucial because page tables can occupy hundreds of megabytes, especially on systems with multiple processes - each needing its own page table

- **Memory efficiency**: large page tables waste memory, making it difficult to scale systems efficiently. Optimizations like multi-level tables allow for memory savings, which directly benefits resource-limited environments or systems with many active processes
- **Performance**: Smaller, optimized page tables reduct cache pressure and speed up memory access time on TLB misses, improving overall system performance. Systems with poor memory management suffer from latency and inefficiencies that slow down processing, especially for high-demand applications
- **Complexity vs. Utility**: highlights a core OS challenge - balancing the benefits of smaller page tables with added system complexity. For example, while multi-level and hybrid tables save memory, they introduce more complex lookup mechanisms, impacting system design and maintenance
