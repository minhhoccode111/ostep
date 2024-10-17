# CPU Scheduling Multi

- **Multiprocessor scheduling**: The process of determining how to distribute tasks across multiple CPUs in a system to optimize performance, ensuring tasks are run efficiently and resources are shared appropriately.

- **Caches**: Small, fast memory storage located close to the CPU that holds frequently accessed data to speed up processing by avoiding slower accesses to main memory.

- **Hardware caches**: Physical cache memory built into the CPU that stores copies of frequently used data from main memory, reducing the time needed to access this data during future operations.

- **Locality**: The principle that programs tend to access the same data or nearby data repeatedly over short periods of time, making caching effective. It comes in two types: temporal and spatial locality.

- **Temporal locality**: The tendency of programs to access the same data or instructions multiple times over a short period. If a piece of data is used once, it is likely to be used again soon.

- **Spatial locality**: The tendency of programs to access data that is located close together in memory. If one memory address is accessed, nearby addresses are likely to be accessed soon after.

- **Cache coherence**:

  - A well-known challenge in bus-based systems.
  - It ensures that changes made to data by one CPU are reflected in the caches of other CPUs, maintaining consistency across the system.

- **Bus snooping**:

  - A technique where each CPU's cache controller monitors ("snoops") the bus for memory operations, such as writes, made by other CPUs.
  - If a CPU detects that another CPU has modified a memory address it has cached, it either invalidates its cached copy or updates it with the new value.
  - This ensures that all CPUs have a consistent view of shared memory.

- **Bus-based system**: A computer architecture where multiple CPUs, memory, and peripherals communicate via a shared data pathway called a bus. This allows components to share data but requires mechanisms like bus snooping to maintain cache coherence.

- **Locks**: Synchronization mechanisms used to control access to shared resources in concurrent systems, ensuring that only one thread or process can access a critical section at a time, preventing race conditions.

- **Cache affinity**: The concept that a process should ideally be scheduled on the same CPU where it was previously run, as its data is likely still in the cache, making the process run faster.

- **Single-queue multiprocessor scheduling (SQMS)**: An approach where all jobs are placed into a single queue and the scheduler selects jobs to run on multiple CPUs from this centralized queue. It is simple but has issues with scalability and cache affinity.

- **Multi-queue multiprocessor scheduling (MQMS)**:

  - A scheduling system that consists of multiple queues, typically one per CPU.
  - Each queue follows its own scheduling discipline, and when a job enters the system, it is placed on exactly one queue based on some heuristic.
  - Jobs are scheduled independently, reducing contention and synchronization issues found in single-queue approaches.

- **Load imbalance (in MQMS)**: A problem in multi-queue systems where some CPUs may end up with too few or too many tasks, leading to inefficient CPU usage and performance degradation.

- **Migration**: The act of moving tasks from one CPU to another to balance the workload across processors and alleviate load imbalance.

- **Work-stealing approach**:

  - A technique where a queue with few jobs (source) checks another queue (target) that is more heavily loaded.
  - If the target queue has more jobs, the source queue "steals" one or more jobs to balance the load.

- **O(1) scheduler**: A multiprocessor scheduler that uses a priority-based system, where processes are scheduled based on priority in constant time (O(1) complexity), meaning the scheduling decision time does not increase with the number of processes.

- **The Completely Fair Scheduler (CFS)**: A Linux scheduler that uses a proportional-share algorithm, aiming to divide CPU time among processes fairly. It prioritizes tasks to ensure that each gets a proportional share of the CPU based on its importance.

- **The BF Scheduler (BFS)**: A simpler, more straightforward scheduler compared to CFS, which uses a single queue and focuses on minimizing latency and maximizing fairness by using the Earliest Eligible Virtual Deadline First (EEVDF) algorithm.

- **Proportional-share**: A scheduling approach where each task is allocated CPU resources proportional to its assigned weight, ensuring that higher-priority tasks get more CPU time relative to lower-priority ones.

## Summary

This lesson focuses on **multiprocessor scheduling**, which is the process of determining how tasks are assigned to multiple CPUs in a computer system to maximize performance.

Here are the key points, explained simply:

1. **Why we need multiprocessor scheduling**: Modern systems have multiple CPUs (or cores), but most programs are written to use just one. To speed things up, programs need to be rewritten to run on multiple CPUs, using methods like threading. The operating system then has to manage how these threads are scheduled across CPUs.

2. **Caches**: CPUs use fast memory called **caches** to store frequently accessed data, so they don't have to retrieve it from slower main memory all the time. But with multiple CPUs, managing caches becomes tricky because CPUs need to stay in sync. For example, if one CPU changes data, the others need to know about it to avoid using outdated information—this is called **cache coherence**.

3. **Scheduling strategies**:

   - **Single-queue scheduling (SQMS)**: All tasks are placed in one queue, and CPUs pick jobs from this queue. While this is simple, it doesn’t scale well as more CPUs are added.
   - **Multi-queue scheduling (MQMS)**: Each CPU gets its own queue, which helps with performance and **cache affinity** (keeping tasks on the same CPU), but it can lead to **load imbalance**, where some CPUs get overloaded while others are idle.

4. **Fixing imbalances**: To solve load imbalances, tasks can be **migrated** between CPUs, or **work-stealing** can be used, where less busy CPUs take jobs from more overloaded ones.

5. **Real-world schedulers**: Different scheduling algorithms exist in practice, like **O(1) scheduler** and **Completely Fair Scheduler (CFS)**. They balance fairness, speed, and complexity differently depending on system needs.

In short, this lesson teaches how operating systems manage and optimize the distribution of tasks across multiple CPUs, while dealing with challenges like cache management, performance optimization, and load balancing.
