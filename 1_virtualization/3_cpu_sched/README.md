# CPU Scheduling

Explains different CPU scheduling algorithms like FIFO, SJF, STCF, and Round Robin, and discusses key performance metrics such as turnaround time, response time, and the trade-offs between them

- turnaround time: of a job is defined as the time at which the job completes minus the time at which the job arrived in the system
- convoy effect: occurs in scheduling when a large, resource-heavy job (or process) holds up smaller, shorter jobs that are queued behind it
- preempt:
- Shortest Time-to-Complete First (STCF):
- round robin:
- time slice:
- scheduling quantum:
- response time:
- translation lookaside buffers (TLBs):
- overlap:
-

## CPU Scheduling Summary

1. **Introduction to Scheduling:**

   - Scheduling is the process of deciding which jobs or processes should run on the CPU at any given time
   - Early scheduling approaches came from operations management, with a focus on efficiency

2. **Workload Assumptions:**

   - To explore scheduling, the document initially makes several simplifying assumptions:
     1. All jobs run for the same time
     2. All jobs arrive simultaneously
     3. Jobs run to completion without interruption
     4. Jobs only use the CPU (no I/O operations)
     5. Job run times are known in advance
   - These assumptions are later relaxed to consider more realistic situations

3. **Scheduling Metrics:**

   - **Turnaround Time** is introduced as a key performance metric, defined as the time from job arrival to job completion
   - **Fairness** is another important metric, often in conflict with performance. For example, optimizing for performance might unfairly delay some jobs

4. **Basic Scheduling Algorithms:**

   - **First In, First Out (FIFO)**: Jobs are executed in the order they arrive. It is simple but can cause long delays for short jobs if a long job is scheduled first (the **convoy effect**)
   - **Shortest Job First (SJF)**: Prioritizes the shortest job first, reducing average turnaround time but requiring knowledge of job lengths, which is often unrealistic
   - **Shortest Time-to-Completion First (STCF)**: An improvement over SJF that allows preemption, running the job with the least remaining time left whenever a new job arrives

5. **New Metrics - Response Time:**

   - **Response Time** is introduced, focusing on how long it takes for a job to start running after arriving in the system. This metric becomes important in time-sharing systems where users expect quick feedback

6. **Round Robin (RR) Scheduling:**

   - RR solves the response time issue by running each job for a small time slice (quantum) before moving to the next. This improves response time but worsens turnaround time
   - A key consideration in RR is the length of the time slice, which should balance responsiveness and the overhead of context switching

7. **Incorporating I/O:**

   - Realistic scheduling must consider jobs that perform I/O operations. A good scheduler can overlap CPU and I/O tasks to maximize CPU utilization

8. **Dealing with Unknown Job Lengths:**

   - In real systems, the scheduler typically doesn't know the length of a job. The document hints at using past behavior to predict future performance, leading to advanced scheduling techniques like **Multi-Level Feedback Queues** (MLFQ), which will be discussed in later sections

9. **Trade-offs in Scheduling:**
   - There's a fundamental trade-off between metrics like **turnaround time** and **response time**, and schedulers must balance these depending on the system's needs
