# CPU Scheduling: Multi Level Feedback Queue (MLFQ)

- queues: In the Multi-Level Feedback Queue (MLFQ), a queue represents a priority level where jobs are placed. The scheduler uses multiple queues, each associated with a different priority. Jobs in higher-priority queues are given preference for CPU time.
- priority level: The rank or importance assigned to a job in the system. Higher-priority jobs are scheduled to run before lower-priority jobs. MLFQ uses a dynamic priority level system, where jobs can move between different levels based on their behavior.
- allotment: The amount of time a job can spend at a given priority level before the scheduler reduces its priority. If a job uses up its allotted time without yielding the CPU, it is moved to a lower-priority queue.
- starvation: A situation where a long-running job does not get any CPU time because higher-priority jobs continuously preempt it. In MLFQ, starvation can occur if there are too many interactive or short jobs that monopolize the CPU.
- priority boost: A technique used to prevent starvation by periodically moving all jobs in the system back to the highest priority queue. This ensures that long-running jobs still get CPU time and do not starve.
- voo-doo constants: Arbitrary configuration values that are hard to determine precisely and are often set based on experience or guesswork. These constants include parameters like the time slice length or the frequency of priority boosts in MLFQ.
- Ousterhout's Law: A principle that encourages avoiding "voo-doo constants." It suggests that arbitrary or poorly understood constants should be minimized, and if possible, values should be determined dynamically or with a more informed approach.
- decay-usage: A scheduling approach that adjusts a job's priority based on its past CPU usage. Jobs that consume a lot of CPU time have their priority reduced over time, allowing other jobs to run. Decay-usage helps balance CPU-bound and interactive jobs.

## Summary

Pay attention to how jobs behave over time and treat them accordingly

- Rule 1: if Priority(A) > Priority(B), A runs (B doesn't)
- Rule 2: if Priority(A) = Priority(B), A & B run in round-robin fashion using the time slice (quantum length) of the given queue
- Rule 3: When a job enters the system, it is placed at the highest priority (the topmost queue)
- Rule 4: Once a job uses up its time allotment at a given level (regardless of how many times it has given up the CPU), its pritority is reduced (i.e., it moves down one queue)
- Rule 5: After some time period S, move all the jobs in the system to the topmost queue

MLFQ is interesting for the following reason: instead of demanding a priori knowledge of the nature of a job, it observes the execution of a job a prioritizes it accordingly. In this way, it manages to achieve the best of both worlds: it can deliver excellent overall performance (similar to SJF/STCF) for short-running interactive jobs, and is fair and makes progress for long-running CPU-intensive workloads. For this reason, many systems, including BSD Unix derivatives, Solaris, and Windows NT and subsequent Windows operating systems use a form of MLFQ as their base scheduler
