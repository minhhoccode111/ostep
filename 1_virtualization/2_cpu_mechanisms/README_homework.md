# Homework: Measuring System Call and Context Switch Costs

## Overview

This homework involves measuring the performance of two key operating system operations: **system calls** and **context switches**. The goal is to quantify the time taken by each operation on your system and report the results.

You will implement two small programs in C:

1. **System Call Measurement**: Measure the cost of making a simple system call (e.g., `read()`).
2. **Context Switch Measurement**: Measure the cost of switching between two processes using inter-process communication (IPC).

## Requirements

### 1. **System Call Cost Measurement**

You are required to measure how long it takes to make a system call in your operating system. A simple system call like a 0-byte `read()` can be used for this measurement.

#### Steps

- Implement a C program that:
  - Repeatedly calls a system call (e.g., `read()`).
  - Times how long it takes to make a large number of calls.
  - Calculates the average time per system call.
- **Output**:
  - Total time taken for all system calls.
  - Average time taken for a single system call.

### 2. **Context Switch Cost Measurement**

You are also required to measure how long it takes to perform a context switch between two processes. This can be done by using pipes to force two processes to communicate back and forth.

#### Steps

- Implement a C program that:
  - Forks two processes.
  - Uses pipes to send data back and forth between the parent and child processes.
  - Times the total duration of multiple context switches between the processes.
  - Calculates the average time per context switch.
- **Output**:
  - Total time taken for all context switches.
  - Average time taken for a single context switch.

## Usage Instructions

### 1. Compile the programs

#### System Call Measurement

```bash
gcc -o measure_syscall syscall_measure.c
```

#### Context Switch Measurement

```bash
gcc -o measure_context_switch context_switch_measure.c
```

### 2. Run the programs

#### System Call Measurement

```bash
./measure_syscall
```

#### Context Switch Measurement

```bash
./measure_context_switch
```

### Example Output

#### System Call Measurement

```bash
Time taken for 1000000 system calls: 4000 microseconds
Average time per system call: 0.004 microseconds
```

#### Context Switch Measurement

```bash
Time taken for 100000 context switches: 20000 microseconds
Average time per context switch: 0.2 microseconds
```

## Important Notes

- Ensure you run these programs on a **single-core** CPU or bind them to the same processor if using a multi-core system to get accurate context switch timings.
- On multi-core systems, you can use the `sched_setaffinity()` function to bind both processes to the same core.

## Conclusion

The purpose of this homework is to give you practical experience in measuring operating system performance. You will gain insights into how costly system calls and context switches are, which can affect overall system performance, especially in systems with frequent context switching or I/O operations.

## References

- Documentation for `gettimeofday()` and `sched_setaffinity()` on Linux.
- Details on system calls and context switches from the course material.
