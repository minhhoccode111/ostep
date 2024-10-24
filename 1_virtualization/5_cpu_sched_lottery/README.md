# CPU Scheduling Lottery

- Proportional-share scheduler: A type of scheduler that ensures each process gets a guaranteed percentage of CPU time, based on its share of system resources
- Fair-share scheduler: A scheduler designed to allocate CPU time proportionally based on the needs of users or processes, ensuring fairness in resource distribution
- Lottery scheduling: A probabilistic method for scheduling where each process holds "tickets," and the scheduler picks a random ticket to decide which process gets to run, giving more tickets to processes that need more CPU time
- Ticket currency: A mechanism in lottery scheduling that allows users to allocate tickets in their own currency for their jobs, which the system then converts into a global currency to ensure fair scheduling across all users
- Ticket transfer: A feature in lottery scheduling where a process can temporarily give its tickets to another process, typically used to prioritize server tasks in a client-server system
- Ticket inflation: A technique where a process temporarily increases or decreases its number of tickets to reflect its need for more or less CPU time, applicable in trusted environments
- Stride scheduling: A deterministic method for proportional-share scheduling where each process has a "stride" (inverse of its tickets), and the process with the lowest pass value runs next
- Virtual runtime (vruntime): A concept used in CFS, where each process accumulates a virtual runtime as it runs, and the process with the lowest vruntime is selected to run next
- Completely fair scheduler (CFS): A modern Linux scheduler that aims to fairly divide CPU time among processes based on their vruntime, ensuring efficiency through dynamic time slices
- Sched latency: A parameter used in CFS to determine how long a process should run before switching, calculated by dividing it by the number of running processes
- Min granularity: A parameter in CFS that ensures no process's time slice is smaller than a set minimum, preventing excessive context switching when too many processes are running

## Summary

The chapter explores the concept of **proportional-share scheduling**, which focuses on dividing system resources (like CPU time) among processes or users in proportion to the resources they should receive. Instead of prioritizing response time or turnaround time, this type of scheduling guarantees that each process gets a fair share of CPU time.

Key ideas include:

- **Lottery Scheduling**: A randomized method where processes receive "tickets," and a lottery is held at each scheduling event. Processes with more tickets have a higher chance of being selected to run, though randomness adds flexibility. The scheduler operates probabilistically, ensuring fairness over time.

- **Mechanisms of Lottery Scheduling**:

  - **Ticket currency**: Allows users to assign their own currency of tickets to their jobs, which the system converts into a global currency.
  - **Ticket transfer**: A process can hand over its tickets to another process, such as in a client-server relationship.
  - **Ticket inflation**: In trusted environments, a process can temporarily increase or decrease its number of tickets to adjust its CPU share.

- **Stride Scheduling**: A deterministic alternative to lottery scheduling, where each process has a "stride" (inverse of its number of tickets). The process with the lowest cumulative pass value runs next, ensuring exact proportional sharing without randomness.

- **Completely Fair Scheduler (CFS)**: The modern Linux scheduler, **CFS**, uses **virtual runtime (vruntime)** to track how long a process has run. It picks the process with the lowest vruntime to ensure fairness. It dynamically adjusts time slices using parameters like **sched latency** and **min granularity**, allowing it to efficiently divide CPU time among multiple processes.

This lesson highlights different strategies for fair CPU allocation, balancing efficiency and fairness, with **CFS** being the most widely used scheduler in modern systems due to its scalability and performance.
