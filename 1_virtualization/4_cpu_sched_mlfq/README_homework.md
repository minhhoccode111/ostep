This program, `mlfq.py`, allows you to see how the MLFQ scheduler
presented in this chapter behaves. As before, you can use this to generate
problems for yourself using random seeds, or use it to construct a
carefully-designed experiment to see how MLFQ works under different
circumstances. To run the program, type:

```sh
prompt> ./mlfq.py
```

Use the help flag (-h) to see the options:

```sh
Usage: mlfq.py [options]

Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -n NUMQUEUES, --numQueues=NUMQUEUES
                        number of queues in MLFQ (if not using -Q)
  -q QUANTUM, --quantum=QUANTUM
                        length of time slice (if not using -Q)
  -a ALLOTMENT, --allotment=ALLOTMENT
                        length of allotment (if not using -A)
  -Q QUANTUMLIST, --quantumList=QUANTUMLIST
                        length of time slice per queue level, specified as
                        x,y,z,... where x is the quantum length for the
                        highest priority queue, y the next highest, and so
                        forth
  -A ALLOTMENTLIST, --allotmentList=ALLOTMENTLIST
                        length of time allotment per queue level, specified as
                        x,y,z,... where x is the # of time slices for the
                        highest priority queue, y the next highest, and so
                        forth
  -j NUMJOBS, --numJobs=NUMJOBS
                        number of jobs in the system
  -m MAXLEN, --maxlen=MAXLEN
                        max run-time of a job (if randomly generating)
  -M MAXIO, --maxio=MAXIO
                        max I/O frequency of a job (if randomly generating)
  -B BOOST, --boost=BOOST
                        how often to boost the priority of all jobs back to
                        high priority
  -i IOTIME, --iotime=IOTIME
                        how long an I/O should last (fixed constant)
  -S, --stay            reset and stay at same priority level when issuing I/O
  -I, --iobump          if specified, jobs that finished I/O move immediately
                        to front of current queue
  -l JLIST, --jlist=JLIST
                        a comma-separated list of jobs to run, in the form
                        x1,y1,z1:x2,y2,z2:... where x is start time, y is run
                        time, and z is how often the job issues an I/O request
  -c                    compute answers for me
```

There are a few different ways to use the simulator. One way is to generate
some random jobs and see if you can figure out how they will behave given the
MLFQ scheduler. For example, if you wanted to create a randomly-generated
three-job workload, you would simply type:

```sh
prompt> ./mlfq.py -j 3
```

What you would then see is the specific problem definition:

```sh
Here is the list of inputs:
OPTIONS jobs 3
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime  84 - ioFreq   7
  Job  1: startTime   0 - runTime  42 - ioFreq   3
  Job  2: startTime   0 - runTime  51 - ioFreq   4

Compute the execution trace for the given workloads
If you would like, also compute the response and turnaround
times for each of the jobs

Use the -c flag to get the exact results when you are finished
```

This generates a random workload of three jobs (as specified), on the default
number of queues with a number of default settings. If you run again with the
solve flag on (-c), you'll see the same print out as above, plus the
following:

```sh
Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] JOB BEGINS by JOB 2
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 83 (of 84) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 82 (of 84) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 81 (of 84) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 80 (of 84) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 79 (of 84) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 78 (of 84) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 77 (of 84) ]
[ time 7 ] IO_START by JOB 0
IO DONE
[ time 7 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 41 (of 42) ]
[ time 8 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 40 (of 42) ]
[ time 9 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 39 (of 42) ]
..

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 175
  Job  1: startTime   0 - response   7 - turnaround 191
  Job  2: startTime   0 - response   9 - turnaround 168

  Avg  2: startTime n/a - response 5.33 - turnaround 178.00
```

The trace shows exactly, on a millisecond-by-millisecond time scale, what the
scheduler decided to do. In this example, it begins by running Job 0 for 7 ms
until Job 0 issues an I/O; this is entirely predictable, as Job 0's I/O
frequency is set to 7 ms, meaning that every 7 ms it runs, it will issue an
I/O and wait for it to complete before continuing. At that point, the
scheduler switches to Job 1, which only runs 2 ms before issuing an I/O
The scheduler prints the entire execution trace in this manner, and
finally also computes the response and turnaround times for each job
as well as an average

You can also control various other aspects of the simulation. For example, you
can specify how many queues you'd like to have in the system (-n) and what the
quantum length should be for all of those queues (-q); if you want even more
control and varied quanta length per queue, you can instead specify the length
of the quantum (time slice) for each queue with -Q, e.g., -Q 10,20,30]
simulates a scheduler with three queues, with the highest-priority queue
having a 10-ms time slice, the next-highest a 20-ms time-slice, and the
low-priority queue a 30-ms time slice

You can separately control how much time allotment there is per queue
too. This can be set for all queues with -a, or per queue with -A, e.g., -A
20,40,60 sets the time allotment per queue to 20ms, 40ms, and 60ms,
respectively. Note that while the chapter talks about allotments in
terms of time, here it is done in terms of number of time slices,
i.e., if the time slice length for a given queue is 10 ms, and the
allotment is 2, the job can run for 2 time slices (20 ms) at that
queue level before moving down in priority

If you are randomly generating jobs, you can also control how long they might
run for (-m), or how often they generate I/O (-M). If you, however, want more
control over the exact characteristics of the jobs running in the system, you
can use -l (lower-case L) or --jlist, which allows you to specify the exact
set of jobs you wish to simulate. The list is of the form:
x1,y1,z1:x2,y2,z2:... where x is the start time of the job, y is the run time
(i.e., how much CPU time it needs), and z the I/O frequency (i.e., after
running z ms, the job issues an I/O; if z is 0, no I/Os are issued)

For example, if you wanted to recreate the example in Figure 8.3
you would specify a job list as follows:

```sh
prompt> ./mlfq.py --jlist 0,180,0:100,20,0 -q 10
```

Running the simulator in this way creates a three-level MLFQ, with each level
having a 10-ms time slice. Two jobs are created: Job 0 which starts at time 0,
runs for 180 ms total, and never issues an I/O; Job 1 starts at 100 ms, needs
only 20 ms of CPU time to complete, and also never issues I/Os

Finally, there are three more parameters of interest. The -B flag, if set to a
non-zero value, boosts all jobs to the highest-priority queue every N
milliseconds, when invoked as such:

```sh
  prompt> ./mlfq.py -B N
```

The scheduler uses this feature to avoid starvation as discussed in the
chapter. However, it is off by default

The -S flag invokes older Rules 4a and 4b, which means that if a job
issues an I/O before completing its time slice, it will return to that
same priority queue when it resumes execution, with its full allotment
intact. This enables gaming of the scheduler

Finally, you can easily change how long an I/O lasts by using the -i flag. By
default in this simplistic model, each I/O takes a fixed amount of time of 5
milliseconds or whatever you set it to with this flag

You can also play around with whether jobs that just complete an I/O are moved
to the head of the queue they are in or to the back, with the -I flag. Check
it out, it's fun!

## Homework Questions (Simulation)

1. Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

`python mlfq.py -n 2 -j 2 -m 50 -M 0 -c`

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime  42 - ioFreq   0
  Job  1: startTime   0 - runTime  21 - ioFreq   0


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 41 (of 42) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 40 (of 42) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 39 (of 42) ]
[ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 38 (of 42) ]
[ time 4 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 37 (of 42) ]
[ time 5 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 36 (of 42) ]
[ time 6 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 35 (of 42) ]
[ time 7 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 34 (of 42) ]
[ time 8 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 33 (of 42) ]
[ time 9 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 32 (of 42) ]
[ time 10 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 20 (of 21) ]
[ time 11 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 19 (of 21) ]
[ time 12 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 18 (of 21) ]
[ time 13 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 17 (of 21) ]
[ time 14 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 16 (of 21) ]
[ time 15 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 15 (of 21) ]
[ time 16 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 14 (of 21) ]
[ time 17 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 13 (of 21) ]
[ time 18 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 12 (of 21) ]
[ time 19 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 11 (of 21) ]
[ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 31 (of 42) ]
[ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 30 (of 42) ]
[ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 29 (of 42) ]
[ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 28 (of 42) ]
[ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 27 (of 42) ]
[ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 26 (of 42) ]
[ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 25 (of 42) ]
[ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 24 (of 42) ]
[ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 23 (of 42) ]
[ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 22 (of 42) ]
[ time 30 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 10 (of 21) ]
[ time 31 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 9 (of 21) ]
[ time 32 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 8 (of 21) ]
[ time 33 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 7 (of 21) ]
[ time 34 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 6 (of 21) ]
[ time 35 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 5 (of 21) ]
[ time 36 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 4 (of 21) ]
[ time 37 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 3 (of 21) ]
[ time 38 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 2 (of 21) ]
[ time 39 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 1 (of 21) ]
[ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 21 (of 42) ]
[ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 20 (of 42) ]
[ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 19 (of 42) ]
[ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 18 (of 42) ]
[ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 17 (of 42) ]
[ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 16 (of 42) ]
[ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 15 (of 42) ]
[ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 14 (of 42) ]
[ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 13 (of 42) ]
[ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 12 (of 42) ]
[ time 50 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 0 (of 21) ]
[ time 51 ] FINISHED JOB 1
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 11 (of 42) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 10 (of 42) ]
[ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 9 (of 42) ]
[ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 8 (of 42) ]
[ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 7 (of 42) ]
[ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 6 (of 42) ]
[ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 5 (of 42) ]
[ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 4 (of 42) ]
[ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 3 (of 42) ]
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 2 (of 42) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 1 (of 42) ]
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 0 (of 42) ]
[ time 63 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  63
  Job  1: startTime   0 - response  10 - turnaround  51

  Avg  1: startTime n/a - response 5.00 - turnaround 57.00
```

This sets up the MLFQ with 2 queues, 2 jobs, a maximum job length of 50, and no I/O (using `-M 0` to turn off I/O).

2. How would you run the scheduler to reproduce each of the examples in the chapter?

For Example 1:

`python mlfq.py -n 3 -Q 10,20,30 -l 0,200,0 -c`

```
Here is the list of inputs:
OPTIONS jobs 1
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  20
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  30
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime 200 - ioFreq   0


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 200) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 200) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 200) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 200) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 200) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 200) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 200) ]
[ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 200) ]
[ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 200) ]
[ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 200) ]
[ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 189 (of 200) ]
[ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 188 (of 200) ]
[ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 187 (of 200) ]
[ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 186 (of 200) ]
[ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 185 (of 200) ]
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 184 (of 200) ]
[ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 183 (of 200) ]
[ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 182 (of 200) ]
[ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 181 (of 200) ]
[ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 180 (of 200) ]
[ time 20 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 179 (of 200) ]
[ time 21 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 178 (of 200) ]
[ time 22 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 177 (of 200) ]
[ time 23 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 176 (of 200) ]
[ time 24 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 175 (of 200) ]
[ time 25 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 174 (of 200) ]
[ time 26 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 173 (of 200) ]
[ time 27 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 172 (of 200) ]
[ time 28 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 171 (of 200) ]
[ time 29 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 170 (of 200) ]
[ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 169 (of 200) ]
[ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 168 (of 200) ]
[ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 167 (of 200) ]
[ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 166 (of 200) ]
[ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 165 (of 200) ]
[ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 164 (of 200) ]
[ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 163 (of 200) ]
[ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 162 (of 200) ]
[ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 161 (of 200) ]
[ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 160 (of 200) ]
[ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 159 (of 200) ]
[ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 158 (of 200) ]
[ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 157 (of 200) ]
[ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 156 (of 200) ]
[ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 155 (of 200) ]
[ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 154 (of 200) ]
[ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 153 (of 200) ]
[ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 152 (of 200) ]
[ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 151 (of 200) ]
[ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 150 (of 200) ]
[ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 149 (of 200) ]
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 148 (of 200) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 147 (of 200) ]
[ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 146 (of 200) ]
[ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 145 (of 200) ]
[ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 144 (of 200) ]
[ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 143 (of 200) ]
[ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 142 (of 200) ]
[ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 141 (of 200) ]
[ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 140 (of 200) ]
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 139 (of 200) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 138 (of 200) ]
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 137 (of 200) ]
[ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 136 (of 200) ]
[ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 135 (of 200) ]
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 134 (of 200) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 133 (of 200) ]
[ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 132 (of 200) ]
[ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 131 (of 200) ]
[ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 130 (of 200) ]
[ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 129 (of 200) ]
[ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 128 (of 200) ]
[ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 127 (of 200) ]
[ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 126 (of 200) ]
[ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 125 (of 200) ]
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 124 (of 200) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 123 (of 200) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 122 (of 200) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 121 (of 200) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 120 (of 200) ]
[ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 119 (of 200) ]
[ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 118 (of 200) ]
[ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 117 (of 200) ]
[ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 116 (of 200) ]
[ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 115 (of 200) ]
[ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 114 (of 200) ]
[ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 113 (of 200) ]
[ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 112 (of 200) ]
[ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 111 (of 200) ]
[ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 110 (of 200) ]
[ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 109 (of 200) ]
[ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 108 (of 200) ]
[ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 107 (of 200) ]
[ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 106 (of 200) ]
[ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 105 (of 200) ]
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 104 (of 200) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 103 (of 200) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 102 (of 200) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 101 (of 200) ]
[ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 100 (of 200) ]
[ time 100 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 99 (of 200) ]
[ time 101 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 98 (of 200) ]
[ time 102 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 97 (of 200) ]
[ time 103 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 96 (of 200) ]
[ time 104 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 95 (of 200) ]
[ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 94 (of 200) ]
[ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 93 (of 200) ]
[ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 92 (of 200) ]
[ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 91 (of 200) ]
[ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 90 (of 200) ]
[ time 110 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 89 (of 200) ]
[ time 111 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 88 (of 200) ]
[ time 112 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 87 (of 200) ]
[ time 113 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 86 (of 200) ]
[ time 114 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 85 (of 200) ]
[ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 84 (of 200) ]
[ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 83 (of 200) ]
[ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 82 (of 200) ]
[ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 81 (of 200) ]
[ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 80 (of 200) ]
[ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 79 (of 200) ]
[ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 78 (of 200) ]
[ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 77 (of 200) ]
[ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 76 (of 200) ]
[ time 124 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 75 (of 200) ]
[ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 74 (of 200) ]
[ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 73 (of 200) ]
[ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 72 (of 200) ]
[ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 71 (of 200) ]
[ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 70 (of 200) ]
[ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 69 (of 200) ]
[ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 68 (of 200) ]
[ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 67 (of 200) ]
[ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 66 (of 200) ]
[ time 134 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 65 (of 200) ]
[ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 64 (of 200) ]
[ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 63 (of 200) ]
[ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 62 (of 200) ]
[ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 61 (of 200) ]
[ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 60 (of 200) ]
[ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 200) ]
[ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 200) ]
[ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 200) ]
[ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 200) ]
[ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 200) ]
[ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 200) ]
[ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 200) ]
[ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 200) ]
[ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 200) ]
[ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 200) ]
[ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 49 (of 200) ]
[ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 48 (of 200) ]
[ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 47 (of 200) ]
[ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 46 (of 200) ]
[ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 45 (of 200) ]
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 44 (of 200) ]
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 43 (of 200) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 42 (of 200) ]
[ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 41 (of 200) ]
[ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 40 (of 200) ]
[ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 39 (of 200) ]
[ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 38 (of 200) ]
[ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 37 (of 200) ]
[ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 36 (of 200) ]
[ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 35 (of 200) ]
[ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 34 (of 200) ]
[ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 33 (of 200) ]
[ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 32 (of 200) ]
[ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 31 (of 200) ]
[ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 30 (of 200) ]
[ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 200) ]
[ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 200) ]
[ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 200) ]
[ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 200) ]
[ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 200) ]
[ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 200) ]
[ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 200) ]
[ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 200) ]
[ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 200) ]
[ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 200) ]
[ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 19 (of 200) ]
[ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 18 (of 200) ]
[ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 17 (of 200) ]
[ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 16 (of 200) ]
[ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 15 (of 200) ]
[ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 14 (of 200) ]
[ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 13 (of 200) ]
[ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 12 (of 200) ]
[ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 11 (of 200) ]
[ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 10 (of 200) ]
[ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 200) ]
[ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 200) ]
[ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 200) ]
[ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 200) ]
[ time 194 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 200) ]
[ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 200) ]
[ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 200) ]
[ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 200) ]
[ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 200) ]
[ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 0 (of 200) ]
[ time 200 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 200

  Avg  0: startTime n/a - response 0.00 - turnaround 200.00
```

For Example 2 (Short job arrives):

`python mlfq.py -n 3 -Q 10,20,30 -l 0,200,0:100,20,0 -c`

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  20
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  30
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime 200 - ioFreq   0
  Job  1: startTime 100 - runTime  20 - ioFreq   0


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 200) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 200) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 200) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 200) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 200) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 200) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 200) ]
[ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 200) ]
[ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 200) ]
[ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 200) ]
[ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 189 (of 200) ]
[ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 188 (of 200) ]
[ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 187 (of 200) ]
[ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 186 (of 200) ]
[ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 185 (of 200) ]
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 184 (of 200) ]
[ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 183 (of 200) ]
[ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 182 (of 200) ]
[ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 181 (of 200) ]
[ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 180 (of 200) ]
[ time 20 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 179 (of 200) ]
[ time 21 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 178 (of 200) ]
[ time 22 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 177 (of 200) ]
[ time 23 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 176 (of 200) ]
[ time 24 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 175 (of 200) ]
[ time 25 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 174 (of 200) ]
[ time 26 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 173 (of 200) ]
[ time 27 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 172 (of 200) ]
[ time 28 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 171 (of 200) ]
[ time 29 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 170 (of 200) ]
[ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 169 (of 200) ]
[ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 168 (of 200) ]
[ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 167 (of 200) ]
[ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 166 (of 200) ]
[ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 165 (of 200) ]
[ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 164 (of 200) ]
[ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 163 (of 200) ]
[ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 162 (of 200) ]
[ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 161 (of 200) ]
[ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 160 (of 200) ]
[ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 159 (of 200) ]
[ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 158 (of 200) ]
[ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 157 (of 200) ]
[ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 156 (of 200) ]
[ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 155 (of 200) ]
[ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 154 (of 200) ]
[ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 153 (of 200) ]
[ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 152 (of 200) ]
[ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 151 (of 200) ]
[ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 150 (of 200) ]
[ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 149 (of 200) ]
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 148 (of 200) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 147 (of 200) ]
[ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 146 (of 200) ]
[ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 145 (of 200) ]
[ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 144 (of 200) ]
[ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 143 (of 200) ]
[ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 142 (of 200) ]
[ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 141 (of 200) ]
[ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 140 (of 200) ]
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 139 (of 200) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 138 (of 200) ]
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 137 (of 200) ]
[ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 136 (of 200) ]
[ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 135 (of 200) ]
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 134 (of 200) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 133 (of 200) ]
[ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 132 (of 200) ]
[ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 131 (of 200) ]
[ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 130 (of 200) ]
[ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 129 (of 200) ]
[ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 128 (of 200) ]
[ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 127 (of 200) ]
[ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 126 (of 200) ]
[ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 125 (of 200) ]
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 124 (of 200) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 123 (of 200) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 122 (of 200) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 121 (of 200) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 120 (of 200) ]
[ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 119 (of 200) ]
[ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 118 (of 200) ]
[ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 117 (of 200) ]
[ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 116 (of 200) ]
[ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 115 (of 200) ]
[ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 114 (of 200) ]
[ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 113 (of 200) ]
[ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 112 (of 200) ]
[ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 111 (of 200) ]
[ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 110 (of 200) ]
[ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 109 (of 200) ]
[ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 108 (of 200) ]
[ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 107 (of 200) ]
[ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 106 (of 200) ]
[ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 105 (of 200) ]
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 104 (of 200) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 103 (of 200) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 102 (of 200) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 101 (of 200) ]
[ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 100 (of 200) ]
[ time 100 ] JOB BEGINS by JOB 1
[ time 100 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 19 (of 20) ]
[ time 101 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 18 (of 20) ]
[ time 102 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 17 (of 20) ]
[ time 103 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 16 (of 20) ]
[ time 104 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 15 (of 20) ]
[ time 105 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 14 (of 20) ]
[ time 106 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 13 (of 20) ]
[ time 107 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 12 (of 20) ]
[ time 108 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 11 (of 20) ]
[ time 109 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 10 (of 20) ]
[ time 110 ] Run JOB 1 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 9 (of 20) ]
[ time 111 ] Run JOB 1 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 8 (of 20) ]
[ time 112 ] Run JOB 1 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 7 (of 20) ]
[ time 113 ] Run JOB 1 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 6 (of 20) ]
[ time 114 ] Run JOB 1 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 5 (of 20) ]
[ time 115 ] Run JOB 1 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 4 (of 20) ]
[ time 116 ] Run JOB 1 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 3 (of 20) ]
[ time 117 ] Run JOB 1 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 2 (of 20) ]
[ time 118 ] Run JOB 1 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 1 (of 20) ]
[ time 119 ] Run JOB 1 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 0 (of 20) ]
[ time 120 ] FINISHED JOB 1
[ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 99 (of 200) ]
[ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 98 (of 200) ]
[ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 97 (of 200) ]
[ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 96 (of 200) ]
[ time 124 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 95 (of 200) ]
[ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 94 (of 200) ]
[ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 93 (of 200) ]
[ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 92 (of 200) ]
[ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 91 (of 200) ]
[ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 90 (of 200) ]
[ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 89 (of 200) ]
[ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 88 (of 200) ]
[ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 87 (of 200) ]
[ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 86 (of 200) ]
[ time 134 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 85 (of 200) ]
[ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 84 (of 200) ]
[ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 83 (of 200) ]
[ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 82 (of 200) ]
[ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 81 (of 200) ]
[ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 80 (of 200) ]
[ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 79 (of 200) ]
[ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 78 (of 200) ]
[ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 77 (of 200) ]
[ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 76 (of 200) ]
[ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 75 (of 200) ]
[ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 74 (of 200) ]
[ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 73 (of 200) ]
[ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 72 (of 200) ]
[ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 71 (of 200) ]
[ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 70 (of 200) ]
[ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 69 (of 200) ]
[ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 68 (of 200) ]
[ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 67 (of 200) ]
[ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 66 (of 200) ]
[ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 65 (of 200) ]
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 64 (of 200) ]
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 63 (of 200) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 62 (of 200) ]
[ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 61 (of 200) ]
[ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 60 (of 200) ]
[ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 200) ]
[ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 200) ]
[ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 200) ]
[ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 200) ]
[ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 200) ]
[ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 200) ]
[ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 200) ]
[ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 200) ]
[ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 200) ]
[ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 200) ]
[ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 49 (of 200) ]
[ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 48 (of 200) ]
[ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 47 (of 200) ]
[ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 46 (of 200) ]
[ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 45 (of 200) ]
[ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 44 (of 200) ]
[ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 43 (of 200) ]
[ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 42 (of 200) ]
[ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 41 (of 200) ]
[ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 40 (of 200) ]
[ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 39 (of 200) ]
[ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 38 (of 200) ]
[ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 37 (of 200) ]
[ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 36 (of 200) ]
[ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 35 (of 200) ]
[ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 34 (of 200) ]
[ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 33 (of 200) ]
[ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 32 (of 200) ]
[ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 31 (of 200) ]
[ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 30 (of 200) ]
[ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 200) ]
[ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 200) ]
[ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 200) ]
[ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 200) ]
[ time 194 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 200) ]
[ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 200) ]
[ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 200) ]
[ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 200) ]
[ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 200) ]
[ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 200) ]
[ time 200 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 19 (of 200) ]
[ time 201 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 18 (of 200) ]
[ time 202 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 17 (of 200) ]
[ time 203 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 16 (of 200) ]
[ time 204 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 15 (of 200) ]
[ time 205 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 14 (of 200) ]
[ time 206 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 13 (of 200) ]
[ time 207 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 12 (of 200) ]
[ time 208 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 11 (of 200) ]
[ time 209 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 10 (of 200) ]
[ time 210 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 200) ]
[ time 211 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 200) ]
[ time 212 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 200) ]
[ time 213 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 200) ]
[ time 214 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 200) ]
[ time 215 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 200) ]
[ time 216 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 200) ]
[ time 217 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 200) ]
[ time 218 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 200) ]
[ time 219 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 0 (of 200) ]
[ time 220 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 220
  Job  1: startTime 100 - response   0 - turnaround  20

  Avg  1: startTime n/a - response 0.00 - turnaround 120.00
```

For Example 3 (With I/O):

`python mlfq.py -n 3 -Q 10,20,30 -l 0,200,0:100,20,5 -c`

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  20
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  30
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime 200 - ioFreq   0
  Job  1: startTime 100 - runTime  20 - ioFreq   5


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 200) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 200) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 200) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 200) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 200) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 200) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 200) ]
[ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 200) ]
[ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 200) ]
[ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 200) ]
[ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 189 (of 200) ]
[ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 188 (of 200) ]
[ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 187 (of 200) ]
[ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 186 (of 200) ]
[ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 185 (of 200) ]
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 184 (of 200) ]
[ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 183 (of 200) ]
[ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 182 (of 200) ]
[ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 181 (of 200) ]
[ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 180 (of 200) ]
[ time 20 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 179 (of 200) ]
[ time 21 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 178 (of 200) ]
[ time 22 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 177 (of 200) ]
[ time 23 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 176 (of 200) ]
[ time 24 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 175 (of 200) ]
[ time 25 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 174 (of 200) ]
[ time 26 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 173 (of 200) ]
[ time 27 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 172 (of 200) ]
[ time 28 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 171 (of 200) ]
[ time 29 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 170 (of 200) ]
[ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 169 (of 200) ]
[ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 168 (of 200) ]
[ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 167 (of 200) ]
[ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 166 (of 200) ]
[ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 165 (of 200) ]
[ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 164 (of 200) ]
[ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 163 (of 200) ]
[ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 162 (of 200) ]
[ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 161 (of 200) ]
[ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 160 (of 200) ]
[ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 159 (of 200) ]
[ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 158 (of 200) ]
[ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 157 (of 200) ]
[ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 156 (of 200) ]
[ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 155 (of 200) ]
[ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 154 (of 200) ]
[ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 153 (of 200) ]
[ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 152 (of 200) ]
[ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 151 (of 200) ]
[ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 150 (of 200) ]
[ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 149 (of 200) ]
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 148 (of 200) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 147 (of 200) ]
[ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 146 (of 200) ]
[ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 145 (of 200) ]
[ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 144 (of 200) ]
[ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 143 (of 200) ]
[ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 142 (of 200) ]
[ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 141 (of 200) ]
[ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 140 (of 200) ]
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 139 (of 200) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 138 (of 200) ]
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 137 (of 200) ]
[ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 136 (of 200) ]
[ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 135 (of 200) ]
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 134 (of 200) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 133 (of 200) ]
[ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 132 (of 200) ]
[ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 131 (of 200) ]
[ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 130 (of 200) ]
[ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 129 (of 200) ]
[ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 128 (of 200) ]
[ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 127 (of 200) ]
[ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 126 (of 200) ]
[ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 125 (of 200) ]
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 124 (of 200) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 123 (of 200) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 122 (of 200) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 121 (of 200) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 120 (of 200) ]
[ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 119 (of 200) ]
[ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 118 (of 200) ]
[ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 117 (of 200) ]
[ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 116 (of 200) ]
[ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 115 (of 200) ]
[ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 114 (of 200) ]
[ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 113 (of 200) ]
[ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 112 (of 200) ]
[ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 111 (of 200) ]
[ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 110 (of 200) ]
[ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 109 (of 200) ]
[ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 108 (of 200) ]
[ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 107 (of 200) ]
[ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 106 (of 200) ]
[ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 105 (of 200) ]
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 104 (of 200) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 103 (of 200) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 102 (of 200) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 101 (of 200) ]
[ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 100 (of 200) ]
[ time 100 ] JOB BEGINS by JOB 1
[ time 100 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 19 (of 20) ]
[ time 101 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 18 (of 20) ]
[ time 102 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 17 (of 20) ]
[ time 103 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 16 (of 20) ]
[ time 104 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 15 (of 20) ]
[ time 105 ] IO_START by JOB 1
IO DONE
[ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 99 (of 200) ]
[ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 98 (of 200) ]
[ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 97 (of 200) ]
[ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 96 (of 200) ]
[ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 95 (of 200) ]
[ time 110 ] IO_DONE by JOB 1
[ time 110 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 14 (of 20) ]
[ time 111 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 13 (of 20) ]
[ time 112 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 12 (of 20) ]
[ time 113 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 11 (of 20) ]
[ time 114 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 10 (of 20) ]
[ time 115 ] IO_START by JOB 1
IO DONE
[ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 94 (of 200) ]
[ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 93 (of 200) ]
[ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 92 (of 200) ]
[ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 91 (of 200) ]
[ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 90 (of 200) ]
[ time 120 ] IO_DONE by JOB 1
[ time 120 ] Run JOB 1 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 9 (of 20) ]
[ time 121 ] Run JOB 1 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 8 (of 20) ]
[ time 122 ] Run JOB 1 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 7 (of 20) ]
[ time 123 ] Run JOB 1 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 6 (of 20) ]
[ time 124 ] Run JOB 1 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 5 (of 20) ]
[ time 125 ] IO_START by JOB 1
IO DONE
[ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 89 (of 200) ]
[ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 88 (of 200) ]
[ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 87 (of 200) ]
[ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 86 (of 200) ]
[ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 85 (of 200) ]
[ time 130 ] IO_DONE by JOB 1
[ time 130 ] Run JOB 1 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 4 (of 20) ]
[ time 131 ] Run JOB 1 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 3 (of 20) ]
[ time 132 ] Run JOB 1 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 2 (of 20) ]
[ time 133 ] Run JOB 1 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 1 (of 20) ]
[ time 134 ] Run JOB 1 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 0 (of 20) ]
[ time 135 ] FINISHED JOB 1
[ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 84 (of 200) ]
[ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 83 (of 200) ]
[ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 82 (of 200) ]
[ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 81 (of 200) ]
[ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 80 (of 200) ]
[ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 79 (of 200) ]
[ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 78 (of 200) ]
[ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 77 (of 200) ]
[ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 76 (of 200) ]
[ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 75 (of 200) ]
[ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 74 (of 200) ]
[ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 73 (of 200) ]
[ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 72 (of 200) ]
[ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 71 (of 200) ]
[ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 70 (of 200) ]
[ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 69 (of 200) ]
[ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 68 (of 200) ]
[ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 67 (of 200) ]
[ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 66 (of 200) ]
[ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 65 (of 200) ]
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 64 (of 200) ]
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 63 (of 200) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 62 (of 200) ]
[ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 61 (of 200) ]
[ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 60 (of 200) ]
[ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 200) ]
[ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 200) ]
[ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 200) ]
[ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 200) ]
[ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 200) ]
[ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 200) ]
[ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 200) ]
[ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 200) ]
[ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 200) ]
[ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 200) ]
[ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 49 (of 200) ]
[ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 48 (of 200) ]
[ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 47 (of 200) ]
[ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 46 (of 200) ]
[ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 45 (of 200) ]
[ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 44 (of 200) ]
[ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 43 (of 200) ]
[ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 42 (of 200) ]
[ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 41 (of 200) ]
[ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 40 (of 200) ]
[ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 39 (of 200) ]
[ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 38 (of 200) ]
[ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 37 (of 200) ]
[ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 36 (of 200) ]
[ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 35 (of 200) ]
[ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 34 (of 200) ]
[ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 33 (of 200) ]
[ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 32 (of 200) ]
[ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 31 (of 200) ]
[ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 30 (of 200) ]
[ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 200) ]
[ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 200) ]
[ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 200) ]
[ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 200) ]
[ time 194 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 200) ]
[ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 200) ]
[ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 200) ]
[ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 200) ]
[ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 200) ]
[ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 200) ]
[ time 200 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 19 (of 200) ]
[ time 201 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 18 (of 200) ]
[ time 202 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 17 (of 200) ]
[ time 203 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 16 (of 200) ]
[ time 204 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 15 (of 200) ]
[ time 205 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 14 (of 200) ]
[ time 206 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 13 (of 200) ]
[ time 207 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 12 (of 200) ]
[ time 208 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 11 (of 200) ]
[ time 209 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 10 (of 200) ]
[ time 210 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 200) ]
[ time 211 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 200) ]
[ time 212 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 200) ]
[ time 213 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 200) ]
[ time 214 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 200) ]
[ time 215 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 200) ]
[ time 216 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 200) ]
[ time 217 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 200) ]
[ time 218 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 200) ]
[ time 219 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 0 (of 200) ]
[ time 220 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 220
  Job  1: startTime 100 - response   0 - turnaround  35

  Avg  1: startTime n/a - response 0.00 - turnaround 127.50
```

3. How would you configure the scheduler parameters to behave just like a round-robin scheduler?

`python mlfq.py -n 1 -q 10 -c`

```
Here is the list of inputs:
OPTIONS jobs 3
OPTIONS queues 1
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime  84 - ioFreq   7
  Job  1: startTime   0 - runTime  42 - ioFreq   3
  Job  2: startTime   0 - runTime  51 - ioFreq   4


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] JOB BEGINS by JOB 2
[ time 0 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 83 (of 84) ]
[ time 1 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 82 (of 84) ]
[ time 2 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 81 (of 84) ]
[ time 3 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 80 (of 84) ]
[ time 4 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 79 (of 84) ]
[ time 5 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 78 (of 84) ]
[ time 6 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 77 (of 84) ]
[ time 7 ] IO_START by JOB 0
IO DONE
[ time 7 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 41 (of 42) ]
[ time 8 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 40 (of 42) ]
[ time 9 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 39 (of 42) ]
[ time 10 ] IO_START by JOB 1
IO DONE
[ time 10 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 50 (of 51) ]
[ time 11 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 49 (of 51) ]
[ time 12 ] IO_DONE by JOB 0
[ time 12 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 48 (of 51) ]
[ time 13 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 47 (of 51) ]
[ time 14 ] IO_START by JOB 2
IO DONE
[ time 14 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 76 (of 84) ]
[ time 15 ] IO_DONE by JOB 1
[ time 15 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 75 (of 84) ]
[ time 16 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 74 (of 84) ]
[ time 17 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 38 (of 42) ]
[ time 18 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 37 (of 42) ]
[ time 19 ] IO_DONE by JOB 2
[ time 19 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 36 (of 42) ]
[ time 20 ] IO_START by JOB 1
IO DONE
[ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 73 (of 84) ]
[ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 72 (of 84) ]
[ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 71 (of 84) ]
[ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 70 (of 84) ]
[ time 24 ] IO_START by JOB 0
IO DONE
[ time 24 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 46 (of 51) ]
[ time 25 ] IO_DONE by JOB 1
[ time 25 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 45 (of 51) ]
[ time 26 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 44 (of 51) ]
[ time 27 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 43 (of 51) ]
[ time 28 ] IO_START by JOB 2
IO DONE
[ time 28 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 35 (of 42) ]
[ time 29 ] IO_DONE by JOB 0
[ time 29 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 34 (of 42) ]
[ time 30 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 33 (of 42) ]
[ time 31 ] IO_START by JOB 1
IO DONE
[ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 69 (of 84) ]
[ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 68 (of 84) ]
[ time 33 ] IO_DONE by JOB 2
[ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 67 (of 84) ]
[ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 66 (of 84) ]
[ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 65 (of 84) ]
[ time 36 ] IO_DONE by JOB 1
[ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 64 (of 84) ]
[ time 37 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 42 (of 51) ]
[ time 38 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 41 (of 51) ]
[ time 39 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 32 (of 42) ]
[ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 63 (of 84) ]
[ time 41 ] IO_START by JOB 0
IO DONE
[ time 41 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 40 (of 51) ]
[ time 42 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 39 (of 51) ]
[ time 43 ] IO_START by JOB 2
IO DONE
[ time 43 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 31 (of 42) ]
[ time 44 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 30 (of 42) ]
[ time 45 ] IO_START by JOB 1
IO DONE
[ time 45 ] IDLE
[ time 46 ] IO_DONE by JOB 0
[ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 62 (of 84) ]
[ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 61 (of 84) ]
[ time 48 ] IO_DONE by JOB 2
[ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 60 (of 84) ]
[ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 59 (of 84) ]
[ time 50 ] IO_DONE by JOB 1
[ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 58 (of 84) ]
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 57 (of 84) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 56 (of 84) ]
[ time 53 ] IO_START by JOB 0
IO DONE
[ time 53 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 38 (of 51) ]
[ time 54 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 37 (of 51) ]
[ time 55 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 36 (of 51) ]
[ time 56 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 35 (of 51) ]
[ time 57 ] IO_START by JOB 2
IO DONE
[ time 57 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 29 (of 42) ]
[ time 58 ] IO_DONE by JOB 0
[ time 58 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 28 (of 42) ]
[ time 59 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 27 (of 42) ]
[ time 60 ] IO_START by JOB 1
IO DONE
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 55 (of 84) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 54 (of 84) ]
[ time 62 ] IO_DONE by JOB 2
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 53 (of 84) ]
[ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 52 (of 84) ]
[ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 51 (of 84) ]
[ time 65 ] IO_DONE by JOB 1
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 50 (of 84) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 49 (of 84) ]
[ time 67 ] IO_START by JOB 0
IO DONE
[ time 67 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 34 (of 51) ]
[ time 68 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 33 (of 51) ]
[ time 69 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 32 (of 51) ]
[ time 70 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 31 (of 51) ]
[ time 71 ] IO_START by JOB 2
IO DONE
[ time 71 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 26 (of 42) ]
[ time 72 ] IO_DONE by JOB 0
[ time 72 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 25 (of 42) ]
[ time 73 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 24 (of 42) ]
[ time 74 ] IO_START by JOB 1
IO DONE
[ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 48 (of 84) ]
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 47 (of 84) ]
[ time 76 ] IO_DONE by JOB 2
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 46 (of 84) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 45 (of 84) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 44 (of 84) ]
[ time 79 ] IO_DONE by JOB 1
[ time 79 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 30 (of 51) ]
[ time 80 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 29 (of 51) ]
[ time 81 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 28 (of 51) ]
[ time 82 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 27 (of 51) ]
[ time 83 ] IO_START by JOB 2
IO DONE
[ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 43 (of 84) ]
[ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 42 (of 84) ]
[ time 85 ] IO_START by JOB 0
IO DONE
[ time 85 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 23 (of 42) ]
[ time 86 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 22 (of 42) ]
[ time 87 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 21 (of 42) ]
[ time 88 ] IO_START by JOB 1
IO DONE
[ time 88 ] IO_DONE by JOB 2
[ time 88 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 26 (of 51) ]
[ time 89 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 25 (of 51) ]
[ time 90 ] IO_DONE by JOB 0
[ time 90 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 24 (of 51) ]
[ time 91 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 23 (of 51) ]
[ time 92 ] IO_START by JOB 2
IO DONE
[ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 41 (of 84) ]
[ time 93 ] IO_DONE by JOB 1
[ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 40 (of 84) ]
[ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 39 (of 84) ]
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 38 (of 84) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 37 (of 84) ]
[ time 97 ] IO_DONE by JOB 2
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 36 (of 84) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 35 (of 84) ]
[ time 99 ] IO_START by JOB 0
IO DONE
[ time 99 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 20 (of 42) ]
[ time 100 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 19 (of 42) ]
[ time 101 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 18 (of 42) ]
[ time 102 ] IO_START by JOB 1
IO DONE
[ time 102 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 22 (of 51) ]
[ time 103 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 21 (of 51) ]
[ time 104 ] IO_DONE by JOB 0
[ time 104 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 20 (of 51) ]
[ time 105 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 19 (of 51) ]
[ time 106 ] IO_START by JOB 2
IO DONE
[ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 34 (of 84) ]
[ time 107 ] IO_DONE by JOB 1
[ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 33 (of 84) ]
[ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 32 (of 84) ]
[ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 31 (of 84) ]
[ time 110 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 30 (of 84) ]
[ time 111 ] IO_DONE by JOB 2
[ time 111 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 29 (of 84) ]
[ time 112 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 28 (of 84) ]
[ time 113 ] IO_START by JOB 0
IO DONE
[ time 113 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 17 (of 42) ]
[ time 114 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 16 (of 42) ]
[ time 115 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 15 (of 42) ]
[ time 116 ] IO_START by JOB 1
IO DONE
[ time 116 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 18 (of 51) ]
[ time 117 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 17 (of 51) ]
[ time 118 ] IO_DONE by JOB 0
[ time 118 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 16 (of 51) ]
[ time 119 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 15 (of 51) ]
[ time 120 ] IO_START by JOB 2
IO DONE
[ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 27 (of 84) ]
[ time 121 ] IO_DONE by JOB 1
[ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 26 (of 84) ]
[ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 25 (of 84) ]
[ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 24 (of 84) ]
[ time 124 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 14 (of 42) ]
[ time 125 ] IO_DONE by JOB 2
[ time 125 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 13 (of 42) ]
[ time 126 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 12 (of 42) ]
[ time 127 ] IO_START by JOB 1
IO DONE
[ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 23 (of 84) ]
[ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 22 (of 84) ]
[ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 21 (of 84) ]
[ time 130 ] IO_START by JOB 0
IO DONE
[ time 130 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 14 (of 51) ]
[ time 131 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 13 (of 51) ]
[ time 132 ] IO_DONE by JOB 1
[ time 132 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 12 (of 51) ]
[ time 133 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 11 (of 51) ]
[ time 134 ] IO_START by JOB 2
IO DONE
[ time 134 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 11 (of 42) ]
[ time 135 ] IO_DONE by JOB 0
[ time 135 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 10 (of 42) ]
[ time 136 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 9 (of 42) ]
[ time 137 ] IO_START by JOB 1
IO DONE
[ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 20 (of 84) ]
[ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 19 (of 84) ]
[ time 139 ] IO_DONE by JOB 2
[ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 18 (of 84) ]
[ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 17 (of 84) ]
[ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 16 (of 84) ]
[ time 142 ] IO_DONE by JOB 1
[ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 15 (of 84) ]
[ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 14 (of 84) ]
[ time 144 ] IO_START by JOB 0
IO DONE
[ time 144 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 10 (of 51) ]
[ time 145 ] Run JOB 2 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 9 (of 51) ]
[ time 146 ] Run JOB 2 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 8 (of 51) ]
[ time 147 ] Run JOB 2 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 7 (of 51) ]
[ time 148 ] IO_START by JOB 2
IO DONE
[ time 148 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 8 (of 42) ]
[ time 149 ] IO_DONE by JOB 0
[ time 149 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 7 (of 42) ]
[ time 150 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 6 (of 42) ]
[ time 151 ] IO_START by JOB 1
IO DONE
[ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 13 (of 84) ]
[ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 12 (of 84) ]
[ time 153 ] IO_DONE by JOB 2
[ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 11 (of 84) ]
[ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 10 (of 84) ]
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 9 (of 84) ]
[ time 156 ] IO_DONE by JOB 1
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 8 (of 84) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 7 (of 84) ]
[ time 158 ] IO_START by JOB 0
IO DONE
[ time 158 ] Run JOB 2 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 6 (of 51) ]
[ time 159 ] Run JOB 2 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 5 (of 51) ]
[ time 160 ] Run JOB 2 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 4 (of 51) ]
[ time 161 ] Run JOB 2 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 3 (of 51) ]
[ time 162 ] IO_START by JOB 2
IO DONE
[ time 162 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 5 (of 42) ]
[ time 163 ] IO_DONE by JOB 0
[ time 163 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 4 (of 42) ]
[ time 164 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 3 (of 42) ]
[ time 165 ] IO_START by JOB 1
IO DONE
[ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 6 (of 84) ]
[ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 5 (of 84) ]
[ time 167 ] IO_DONE by JOB 2
[ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 4 (of 84) ]
[ time 168 ] Run JOB 2 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 2 (of 51) ]
[ time 169 ] Run JOB 2 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 1 (of 51) ]
[ time 170 ] IO_DONE by JOB 1
[ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 3 (of 84) ]
[ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 2 (of 84) ]
[ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 1 (of 84) ]
[ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 0 (of 84) ]
[ time 174 ] FINISHED JOB 0
[ time 174 ] Run JOB 2 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 0 (of 51) ]
[ time 175 ] FINISHED JOB 2
[ time 175 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 2 (of 42) ]
[ time 176 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 1 (of 42) ]
[ time 177 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 0 (of 42) ]
[ time 178 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 174
  Job  1: startTime   0 - response   7 - turnaround 178
  Job  2: startTime   0 - response  10 - turnaround 175

  Avg  2: startTime n/a - response 5.67 - turnaround 175.67
```

This sets up a single queue (just like round-robin) with a time slice of 10 ms.

4. Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the `-S` flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.

`python mlfq.py -n 2 -Q 10,20 -l 0,100,0:0,100,99 -S -c`

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  20
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO True
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime 100 - ioFreq   0
  Job  1: startTime   0 - runTime 100 - ioFreq  99


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
[ time 3 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
[ time 4 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
[ time 5 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 94 (of 100) ]
[ time 6 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 93 (of 100) ]
[ time 7 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 92 (of 100) ]
[ time 8 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 91 (of 100) ]
[ time 9 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 90 (of 100) ]
[ time 10 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
[ time 11 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
[ time 12 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
[ time 13 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
[ time 14 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
[ time 15 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 94 (of 100) ]
[ time 16 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 93 (of 100) ]
[ time 17 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 92 (of 100) ]
[ time 18 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 91 (of 100) ]
[ time 19 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 90 (of 100) ]
[ time 20 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 89 (of 100) ]
[ time 21 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 88 (of 100) ]
[ time 22 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 87 (of 100) ]
[ time 23 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 86 (of 100) ]
[ time 24 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 85 (of 100) ]
[ time 25 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 84 (of 100) ]
[ time 26 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 83 (of 100) ]
[ time 27 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 82 (of 100) ]
[ time 28 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 81 (of 100) ]
[ time 29 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 80 (of 100) ]
[ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 79 (of 100) ]
[ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 78 (of 100) ]
[ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 77 (of 100) ]
[ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 76 (of 100) ]
[ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 75 (of 100) ]
[ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 74 (of 100) ]
[ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 73 (of 100) ]
[ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 72 (of 100) ]
[ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 71 (of 100) ]
[ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 70 (of 100) ]
[ time 40 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 89 (of 100) ]
[ time 41 ] Run JOB 1 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 88 (of 100) ]
[ time 42 ] Run JOB 1 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 87 (of 100) ]
[ time 43 ] Run JOB 1 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 86 (of 100) ]
[ time 44 ] Run JOB 1 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 85 (of 100) ]
[ time 45 ] Run JOB 1 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 84 (of 100) ]
[ time 46 ] Run JOB 1 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 83 (of 100) ]
[ time 47 ] Run JOB 1 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 82 (of 100) ]
[ time 48 ] Run JOB 1 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 81 (of 100) ]
[ time 49 ] Run JOB 1 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 80 (of 100) ]
[ time 50 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 79 (of 100) ]
[ time 51 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 78 (of 100) ]
[ time 52 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 77 (of 100) ]
[ time 53 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 76 (of 100) ]
[ time 54 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 75 (of 100) ]
[ time 55 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 74 (of 100) ]
[ time 56 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 73 (of 100) ]
[ time 57 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 72 (of 100) ]
[ time 58 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 71 (of 100) ]
[ time 59 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 70 (of 100) ]
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 69 (of 100) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 68 (of 100) ]
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 67 (of 100) ]
[ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 66 (of 100) ]
[ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 65 (of 100) ]
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 64 (of 100) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 63 (of 100) ]
[ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 62 (of 100) ]
[ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 61 (of 100) ]
[ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 60 (of 100) ]
[ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 100) ]
[ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 100) ]
[ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 100) ]
[ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 100) ]
[ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 100) ]
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 100) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 100) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 100) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 100) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 100) ]
[ time 80 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 69 (of 100) ]
[ time 81 ] Run JOB 1 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 68 (of 100) ]
[ time 82 ] Run JOB 1 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 67 (of 100) ]
[ time 83 ] Run JOB 1 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 66 (of 100) ]
[ time 84 ] Run JOB 1 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 65 (of 100) ]
[ time 85 ] Run JOB 1 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 64 (of 100) ]
[ time 86 ] Run JOB 1 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 63 (of 100) ]
[ time 87 ] Run JOB 1 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 62 (of 100) ]
[ time 88 ] Run JOB 1 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 61 (of 100) ]
[ time 89 ] Run JOB 1 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 60 (of 100) ]
[ time 90 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 100) ]
[ time 91 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 100) ]
[ time 92 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 100) ]
[ time 93 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 100) ]
[ time 94 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 100) ]
[ time 95 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 100) ]
[ time 96 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 100) ]
[ time 97 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 100) ]
[ time 98 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 100) ]
[ time 99 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 100) ]
[ time 100 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 49 (of 100) ]
[ time 101 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 48 (of 100) ]
[ time 102 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 47 (of 100) ]
[ time 103 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 46 (of 100) ]
[ time 104 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 45 (of 100) ]
[ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 44 (of 100) ]
[ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 43 (of 100) ]
[ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 42 (of 100) ]
[ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 41 (of 100) ]
[ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 40 (of 100) ]
[ time 110 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 39 (of 100) ]
[ time 111 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 38 (of 100) ]
[ time 112 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 37 (of 100) ]
[ time 113 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 36 (of 100) ]
[ time 114 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 35 (of 100) ]
[ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 34 (of 100) ]
[ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 33 (of 100) ]
[ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 32 (of 100) ]
[ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 31 (of 100) ]
[ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 30 (of 100) ]
[ time 120 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 49 (of 100) ]
[ time 121 ] Run JOB 1 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 48 (of 100) ]
[ time 122 ] Run JOB 1 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 47 (of 100) ]
[ time 123 ] Run JOB 1 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 46 (of 100) ]
[ time 124 ] Run JOB 1 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 45 (of 100) ]
[ time 125 ] Run JOB 1 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 44 (of 100) ]
[ time 126 ] Run JOB 1 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 43 (of 100) ]
[ time 127 ] Run JOB 1 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 42 (of 100) ]
[ time 128 ] Run JOB 1 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 41 (of 100) ]
[ time 129 ] Run JOB 1 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 40 (of 100) ]
[ time 130 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 39 (of 100) ]
[ time 131 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 38 (of 100) ]
[ time 132 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 37 (of 100) ]
[ time 133 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 36 (of 100) ]
[ time 134 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 35 (of 100) ]
[ time 135 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 34 (of 100) ]
[ time 136 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 33 (of 100) ]
[ time 137 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 32 (of 100) ]
[ time 138 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 31 (of 100) ]
[ time 139 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 30 (of 100) ]
[ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 29 (of 100) ]
[ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 28 (of 100) ]
[ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 27 (of 100) ]
[ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 26 (of 100) ]
[ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 25 (of 100) ]
[ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 24 (of 100) ]
[ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 23 (of 100) ]
[ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 22 (of 100) ]
[ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 21 (of 100) ]
[ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 20 (of 100) ]
[ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 100) ]
[ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 100) ]
[ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 100) ]
[ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 100) ]
[ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 100) ]
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 100) ]
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 100) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 100) ]
[ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 100) ]
[ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 100) ]
[ time 160 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 29 (of 100) ]
[ time 161 ] Run JOB 1 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 28 (of 100) ]
[ time 162 ] Run JOB 1 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 27 (of 100) ]
[ time 163 ] Run JOB 1 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 26 (of 100) ]
[ time 164 ] Run JOB 1 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 25 (of 100) ]
[ time 165 ] Run JOB 1 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 24 (of 100) ]
[ time 166 ] Run JOB 1 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 23 (of 100) ]
[ time 167 ] Run JOB 1 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 22 (of 100) ]
[ time 168 ] Run JOB 1 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 21 (of 100) ]
[ time 169 ] Run JOB 1 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 20 (of 100) ]
[ time 170 ] Run JOB 1 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 100) ]
[ time 171 ] Run JOB 1 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 100) ]
[ time 172 ] Run JOB 1 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 100) ]
[ time 173 ] Run JOB 1 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 100) ]
[ time 174 ] Run JOB 1 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 100) ]
[ time 175 ] Run JOB 1 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 100) ]
[ time 176 ] Run JOB 1 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 100) ]
[ time 177 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 100) ]
[ time 178 ] Run JOB 1 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 100) ]
[ time 179 ] Run JOB 1 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 100) ]
[ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 100) ]
[ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 100) ]
[ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 100) ]
[ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 100) ]
[ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 100) ]
[ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 100) ]
[ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 100) ]
[ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 100) ]
[ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 100) ]
[ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 0 (of 100) ]
[ time 190 ] FINISHED JOB 0
[ time 190 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 100) ]
[ time 191 ] Run JOB 1 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 100) ]
[ time 192 ] Run JOB 1 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 100) ]
[ time 193 ] Run JOB 1 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 100) ]
[ time 194 ] Run JOB 1 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 100) ]
[ time 195 ] Run JOB 1 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 100) ]
[ time 196 ] Run JOB 1 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 100) ]
[ time 197 ] Run JOB 1 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 100) ]
[ time 198 ] Run JOB 1 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 100) ]
[ time 199 ] IO_START by JOB 1
IO DONE
[ time 199 ] IDLE
[ time 200 ] IDLE
[ time 201 ] IDLE
[ time 202 ] IDLE
[ time 203 ] IDLE
[ time 204 ] IO_DONE by JOB 1
[ time 204 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 0 (of 100) ]
[ time 205 ] FINISHED JOB 1

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 190
  Job  1: startTime   0 - response  10 - turnaround 205

  Avg  1: startTime n/a - response 5.00 - turnaround 197.50
```

This uses the `-S` flag to turn on the older Rules 4a and 4b. The second job issues I/O 99% of the time (`l 0,100,99`), allowing it to game the system.

5. Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the `-B` flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU?

Assuming you want the boost to happen at intervals that ensure 5% CPU time for the long-running job:

`python mlfq.py -n 3 -Q 10,20,30 -l 0,1000,0 -B 200 -c`

```
Here is the list of inputs:
OPTIONS jobs 1
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  20
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  30
OPTIONS boost 200
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime 1000 - ioFreq   0


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 999 (of 1000) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 998 (of 1000) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 997 (of 1000) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 996 (of 1000) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 995 (of 1000) ]
[ time 5 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 994 (of 1000) ]
[ time 6 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 993 (of 1000) ]
[ time 7 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 992 (of 1000) ]
[ time 8 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 991 (of 1000) ]
[ time 9 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 990 (of 1000) ]
[ time 10 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 989 (of 1000) ]
[ time 11 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 988 (of 1000) ]
[ time 12 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 987 (of 1000) ]
[ time 13 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 986 (of 1000) ]
[ time 14 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 985 (of 1000) ]
[ time 15 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 984 (of 1000) ]
[ time 16 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 983 (of 1000) ]
[ time 17 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 982 (of 1000) ]
[ time 18 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 981 (of 1000) ]
[ time 19 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 980 (of 1000) ]
[ time 20 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 979 (of 1000) ]
[ time 21 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 978 (of 1000) ]
[ time 22 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 977 (of 1000) ]
[ time 23 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 976 (of 1000) ]
[ time 24 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 975 (of 1000) ]
[ time 25 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 974 (of 1000) ]
[ time 26 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 973 (of 1000) ]
[ time 27 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 972 (of 1000) ]
[ time 28 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 971 (of 1000) ]
[ time 29 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 970 (of 1000) ]
[ time 30 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 969 (of 1000) ]
[ time 31 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 968 (of 1000) ]
[ time 32 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 967 (of 1000) ]
[ time 33 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 966 (of 1000) ]
[ time 34 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 965 (of 1000) ]
[ time 35 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 964 (of 1000) ]
[ time 36 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 963 (of 1000) ]
[ time 37 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 962 (of 1000) ]
[ time 38 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 961 (of 1000) ]
[ time 39 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 960 (of 1000) ]
[ time 40 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 959 (of 1000) ]
[ time 41 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 958 (of 1000) ]
[ time 42 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 957 (of 1000) ]
[ time 43 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 956 (of 1000) ]
[ time 44 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 955 (of 1000) ]
[ time 45 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 954 (of 1000) ]
[ time 46 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 953 (of 1000) ]
[ time 47 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 952 (of 1000) ]
[ time 48 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 951 (of 1000) ]
[ time 49 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 950 (of 1000) ]
[ time 50 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 949 (of 1000) ]
[ time 51 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 948 (of 1000) ]
[ time 52 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 947 (of 1000) ]
[ time 53 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 946 (of 1000) ]
[ time 54 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 945 (of 1000) ]
[ time 55 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 944 (of 1000) ]
[ time 56 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 943 (of 1000) ]
[ time 57 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 942 (of 1000) ]
[ time 58 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 941 (of 1000) ]
[ time 59 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 940 (of 1000) ]
[ time 60 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 939 (of 1000) ]
[ time 61 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 938 (of 1000) ]
[ time 62 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 937 (of 1000) ]
[ time 63 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 936 (of 1000) ]
[ time 64 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 935 (of 1000) ]
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 934 (of 1000) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 933 (of 1000) ]
[ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 932 (of 1000) ]
[ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 931 (of 1000) ]
[ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 930 (of 1000) ]
[ time 70 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 929 (of 1000) ]
[ time 71 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 928 (of 1000) ]
[ time 72 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 927 (of 1000) ]
[ time 73 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 926 (of 1000) ]
[ time 74 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 925 (of 1000) ]
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 924 (of 1000) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 923 (of 1000) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 922 (of 1000) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 921 (of 1000) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 920 (of 1000) ]
[ time 80 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 919 (of 1000) ]
[ time 81 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 918 (of 1000) ]
[ time 82 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 917 (of 1000) ]
[ time 83 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 916 (of 1000) ]
[ time 84 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 915 (of 1000) ]
[ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 914 (of 1000) ]
[ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 913 (of 1000) ]
[ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 912 (of 1000) ]
[ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 911 (of 1000) ]
[ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 910 (of 1000) ]
[ time 90 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 909 (of 1000) ]
[ time 91 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 908 (of 1000) ]
[ time 92 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 907 (of 1000) ]
[ time 93 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 906 (of 1000) ]
[ time 94 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 905 (of 1000) ]
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 904 (of 1000) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 903 (of 1000) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 902 (of 1000) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 901 (of 1000) ]
[ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 900 (of 1000) ]
[ time 100 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 899 (of 1000) ]
[ time 101 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 898 (of 1000) ]
[ time 102 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 897 (of 1000) ]
[ time 103 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 896 (of 1000) ]
[ time 104 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 895 (of 1000) ]
[ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 894 (of 1000) ]
[ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 893 (of 1000) ]
[ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 892 (of 1000) ]
[ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 891 (of 1000) ]
[ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 890 (of 1000) ]
[ time 110 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 889 (of 1000) ]
[ time 111 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 888 (of 1000) ]
[ time 112 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 887 (of 1000) ]
[ time 113 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 886 (of 1000) ]
[ time 114 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 885 (of 1000) ]
[ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 884 (of 1000) ]
[ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 883 (of 1000) ]
[ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 882 (of 1000) ]
[ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 881 (of 1000) ]
[ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 880 (of 1000) ]
[ time 120 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 879 (of 1000) ]
[ time 121 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 878 (of 1000) ]
[ time 122 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 877 (of 1000) ]
[ time 123 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 876 (of 1000) ]
[ time 124 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 875 (of 1000) ]
[ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 874 (of 1000) ]
[ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 873 (of 1000) ]
[ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 872 (of 1000) ]
[ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 871 (of 1000) ]
[ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 870 (of 1000) ]
[ time 130 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 869 (of 1000) ]
[ time 131 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 868 (of 1000) ]
[ time 132 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 867 (of 1000) ]
[ time 133 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 866 (of 1000) ]
[ time 134 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 865 (of 1000) ]
[ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 864 (of 1000) ]
[ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 863 (of 1000) ]
[ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 862 (of 1000) ]
[ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 861 (of 1000) ]
[ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 860 (of 1000) ]
[ time 140 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 859 (of 1000) ]
[ time 141 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 858 (of 1000) ]
[ time 142 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 857 (of 1000) ]
[ time 143 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 856 (of 1000) ]
[ time 144 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 855 (of 1000) ]
[ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 854 (of 1000) ]
[ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 853 (of 1000) ]
[ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 852 (of 1000) ]
[ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 851 (of 1000) ]
[ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 850 (of 1000) ]
[ time 150 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 849 (of 1000) ]
[ time 151 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 848 (of 1000) ]
[ time 152 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 847 (of 1000) ]
[ time 153 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 846 (of 1000) ]
[ time 154 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 845 (of 1000) ]
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 844 (of 1000) ]
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 843 (of 1000) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 842 (of 1000) ]
[ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 841 (of 1000) ]
[ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 840 (of 1000) ]
[ time 160 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 839 (of 1000) ]
[ time 161 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 838 (of 1000) ]
[ time 162 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 837 (of 1000) ]
[ time 163 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 836 (of 1000) ]
[ time 164 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 835 (of 1000) ]
[ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 834 (of 1000) ]
[ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 833 (of 1000) ]
[ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 832 (of 1000) ]
[ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 831 (of 1000) ]
[ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 830 (of 1000) ]
[ time 170 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 829 (of 1000) ]
[ time 171 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 828 (of 1000) ]
[ time 172 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 827 (of 1000) ]
[ time 173 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 826 (of 1000) ]
[ time 174 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 825 (of 1000) ]
[ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 824 (of 1000) ]
[ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 823 (of 1000) ]
[ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 822 (of 1000) ]
[ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 821 (of 1000) ]
[ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 820 (of 1000) ]
[ time 180 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 819 (of 1000) ]
[ time 181 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 818 (of 1000) ]
[ time 182 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 817 (of 1000) ]
[ time 183 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 816 (of 1000) ]
[ time 184 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 815 (of 1000) ]
[ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 814 (of 1000) ]
[ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 813 (of 1000) ]
[ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 812 (of 1000) ]
[ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 811 (of 1000) ]
[ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 810 (of 1000) ]
[ time 190 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 809 (of 1000) ]
[ time 191 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 808 (of 1000) ]
[ time 192 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 807 (of 1000) ]
[ time 193 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 806 (of 1000) ]
[ time 194 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 805 (of 1000) ]
[ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 804 (of 1000) ]
[ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 803 (of 1000) ]
[ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 802 (of 1000) ]
[ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 801 (of 1000) ]
[ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 800 (of 1000) ]
[ time 200 ] BOOST ( every 200 )
[ time 200 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 799 (of 1000) ]
[ time 201 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 798 (of 1000) ]
[ time 202 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 797 (of 1000) ]
[ time 203 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 796 (of 1000) ]
[ time 204 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 795 (of 1000) ]
[ time 205 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 794 (of 1000) ]
[ time 206 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 793 (of 1000) ]
[ time 207 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 792 (of 1000) ]
[ time 208 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 791 (of 1000) ]
[ time 209 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 790 (of 1000) ]
[ time 210 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 789 (of 1000) ]
[ time 211 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 788 (of 1000) ]
[ time 212 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 787 (of 1000) ]
[ time 213 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 786 (of 1000) ]
[ time 214 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 785 (of 1000) ]
[ time 215 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 784 (of 1000) ]
[ time 216 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 783 (of 1000) ]
[ time 217 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 782 (of 1000) ]
[ time 218 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 781 (of 1000) ]
[ time 219 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 780 (of 1000) ]
[ time 220 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 779 (of 1000) ]
[ time 221 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 778 (of 1000) ]
[ time 222 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 777 (of 1000) ]
[ time 223 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 776 (of 1000) ]
[ time 224 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 775 (of 1000) ]
[ time 225 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 774 (of 1000) ]
[ time 226 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 773 (of 1000) ]
[ time 227 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 772 (of 1000) ]
[ time 228 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 771 (of 1000) ]
[ time 229 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 770 (of 1000) ]
[ time 230 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 769 (of 1000) ]
[ time 231 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 768 (of 1000) ]
[ time 232 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 767 (of 1000) ]
[ time 233 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 766 (of 1000) ]
[ time 234 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 765 (of 1000) ]
[ time 235 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 764 (of 1000) ]
[ time 236 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 763 (of 1000) ]
[ time 237 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 762 (of 1000) ]
[ time 238 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 761 (of 1000) ]
[ time 239 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 760 (of 1000) ]
[ time 240 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 759 (of 1000) ]
[ time 241 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 758 (of 1000) ]
[ time 242 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 757 (of 1000) ]
[ time 243 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 756 (of 1000) ]
[ time 244 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 755 (of 1000) ]
[ time 245 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 754 (of 1000) ]
[ time 246 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 753 (of 1000) ]
[ time 247 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 752 (of 1000) ]
[ time 248 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 751 (of 1000) ]
[ time 249 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 750 (of 1000) ]
[ time 250 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 749 (of 1000) ]
[ time 251 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 748 (of 1000) ]
[ time 252 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 747 (of 1000) ]
[ time 253 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 746 (of 1000) ]
[ time 254 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 745 (of 1000) ]
[ time 255 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 744 (of 1000) ]
[ time 256 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 743 (of 1000) ]
[ time 257 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 742 (of 1000) ]
[ time 258 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 741 (of 1000) ]
[ time 259 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 740 (of 1000) ]
[ time 260 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 739 (of 1000) ]
[ time 261 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 738 (of 1000) ]
[ time 262 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 737 (of 1000) ]
[ time 263 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 736 (of 1000) ]
[ time 264 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 735 (of 1000) ]
[ time 265 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 734 (of 1000) ]
[ time 266 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 733 (of 1000) ]
[ time 267 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 732 (of 1000) ]
[ time 268 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 731 (of 1000) ]
[ time 269 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 730 (of 1000) ]
[ time 270 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 729 (of 1000) ]
[ time 271 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 728 (of 1000) ]
[ time 272 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 727 (of 1000) ]
[ time 273 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 726 (of 1000) ]
[ time 274 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 725 (of 1000) ]
[ time 275 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 724 (of 1000) ]
[ time 276 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 723 (of 1000) ]
[ time 277 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 722 (of 1000) ]
[ time 278 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 721 (of 1000) ]
[ time 279 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 720 (of 1000) ]
[ time 280 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 719 (of 1000) ]
[ time 281 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 718 (of 1000) ]
[ time 282 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 717 (of 1000) ]
[ time 283 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 716 (of 1000) ]
[ time 284 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 715 (of 1000) ]
[ time 285 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 714 (of 1000) ]
[ time 286 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 713 (of 1000) ]
[ time 287 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 712 (of 1000) ]
[ time 288 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 711 (of 1000) ]
[ time 289 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 710 (of 1000) ]
[ time 290 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 709 (of 1000) ]
[ time 291 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 708 (of 1000) ]
[ time 292 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 707 (of 1000) ]
[ time 293 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 706 (of 1000) ]
[ time 294 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 705 (of 1000) ]
[ time 295 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 704 (of 1000) ]
[ time 296 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 703 (of 1000) ]
[ time 297 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 702 (of 1000) ]
[ time 298 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 701 (of 1000) ]
[ time 299 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 700 (of 1000) ]
[ time 300 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 699 (of 1000) ]
[ time 301 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 698 (of 1000) ]
[ time 302 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 697 (of 1000) ]
[ time 303 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 696 (of 1000) ]
[ time 304 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 695 (of 1000) ]
[ time 305 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 694 (of 1000) ]
[ time 306 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 693 (of 1000) ]
[ time 307 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 692 (of 1000) ]
[ time 308 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 691 (of 1000) ]
[ time 309 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 690 (of 1000) ]
[ time 310 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 689 (of 1000) ]
[ time 311 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 688 (of 1000) ]
[ time 312 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 687 (of 1000) ]
[ time 313 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 686 (of 1000) ]
[ time 314 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 685 (of 1000) ]
[ time 315 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 684 (of 1000) ]
[ time 316 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 683 (of 1000) ]
[ time 317 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 682 (of 1000) ]
[ time 318 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 681 (of 1000) ]
[ time 319 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 680 (of 1000) ]
[ time 320 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 679 (of 1000) ]
[ time 321 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 678 (of 1000) ]
[ time 322 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 677 (of 1000) ]
[ time 323 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 676 (of 1000) ]
[ time 324 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 675 (of 1000) ]
[ time 325 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 674 (of 1000) ]
[ time 326 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 673 (of 1000) ]
[ time 327 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 672 (of 1000) ]
[ time 328 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 671 (of 1000) ]
[ time 329 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 670 (of 1000) ]
[ time 330 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 669 (of 1000) ]
[ time 331 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 668 (of 1000) ]
[ time 332 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 667 (of 1000) ]
[ time 333 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 666 (of 1000) ]
[ time 334 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 665 (of 1000) ]
[ time 335 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 664 (of 1000) ]
[ time 336 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 663 (of 1000) ]
[ time 337 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 662 (of 1000) ]
[ time 338 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 661 (of 1000) ]
[ time 339 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 660 (of 1000) ]
[ time 340 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 659 (of 1000) ]
[ time 341 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 658 (of 1000) ]
[ time 342 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 657 (of 1000) ]
[ time 343 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 656 (of 1000) ]
[ time 344 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 655 (of 1000) ]
[ time 345 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 654 (of 1000) ]
[ time 346 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 653 (of 1000) ]
[ time 347 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 652 (of 1000) ]
[ time 348 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 651 (of 1000) ]
[ time 349 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 650 (of 1000) ]
[ time 350 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 649 (of 1000) ]
[ time 351 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 648 (of 1000) ]
[ time 352 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 647 (of 1000) ]
[ time 353 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 646 (of 1000) ]
[ time 354 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 645 (of 1000) ]
[ time 355 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 644 (of 1000) ]
[ time 356 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 643 (of 1000) ]
[ time 357 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 642 (of 1000) ]
[ time 358 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 641 (of 1000) ]
[ time 359 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 640 (of 1000) ]
[ time 360 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 639 (of 1000) ]
[ time 361 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 638 (of 1000) ]
[ time 362 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 637 (of 1000) ]
[ time 363 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 636 (of 1000) ]
[ time 364 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 635 (of 1000) ]
[ time 365 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 634 (of 1000) ]
[ time 366 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 633 (of 1000) ]
[ time 367 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 632 (of 1000) ]
[ time 368 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 631 (of 1000) ]
[ time 369 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 630 (of 1000) ]
[ time 370 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 629 (of 1000) ]
[ time 371 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 628 (of 1000) ]
[ time 372 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 627 (of 1000) ]
[ time 373 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 626 (of 1000) ]
[ time 374 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 625 (of 1000) ]
[ time 375 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 624 (of 1000) ]
[ time 376 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 623 (of 1000) ]
[ time 377 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 622 (of 1000) ]
[ time 378 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 621 (of 1000) ]
[ time 379 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 620 (of 1000) ]
[ time 380 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 619 (of 1000) ]
[ time 381 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 618 (of 1000) ]
[ time 382 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 617 (of 1000) ]
[ time 383 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 616 (of 1000) ]
[ time 384 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 615 (of 1000) ]
[ time 385 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 614 (of 1000) ]
[ time 386 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 613 (of 1000) ]
[ time 387 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 612 (of 1000) ]
[ time 388 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 611 (of 1000) ]
[ time 389 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 610 (of 1000) ]
[ time 390 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 609 (of 1000) ]
[ time 391 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 608 (of 1000) ]
[ time 392 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 607 (of 1000) ]
[ time 393 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 606 (of 1000) ]
[ time 394 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 605 (of 1000) ]
[ time 395 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 604 (of 1000) ]
[ time 396 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 603 (of 1000) ]
[ time 397 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 602 (of 1000) ]
[ time 398 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 601 (of 1000) ]
[ time 399 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 600 (of 1000) ]
[ time 400 ] BOOST ( every 200 )
[ time 400 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 599 (of 1000) ]
[ time 401 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 598 (of 1000) ]
[ time 402 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 597 (of 1000) ]
[ time 403 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 596 (of 1000) ]
[ time 404 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 595 (of 1000) ]
[ time 405 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 594 (of 1000) ]
[ time 406 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 593 (of 1000) ]
[ time 407 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 592 (of 1000) ]
[ time 408 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 591 (of 1000) ]
[ time 409 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 590 (of 1000) ]
[ time 410 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 589 (of 1000) ]
[ time 411 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 588 (of 1000) ]
[ time 412 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 587 (of 1000) ]
[ time 413 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 586 (of 1000) ]
[ time 414 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 585 (of 1000) ]
[ time 415 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 584 (of 1000) ]
[ time 416 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 583 (of 1000) ]
[ time 417 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 582 (of 1000) ]
[ time 418 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 581 (of 1000) ]
[ time 419 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 580 (of 1000) ]
[ time 420 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 579 (of 1000) ]
[ time 421 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 578 (of 1000) ]
[ time 422 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 577 (of 1000) ]
[ time 423 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 576 (of 1000) ]
[ time 424 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 575 (of 1000) ]
[ time 425 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 574 (of 1000) ]
[ time 426 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 573 (of 1000) ]
[ time 427 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 572 (of 1000) ]
[ time 428 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 571 (of 1000) ]
[ time 429 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 570 (of 1000) ]
[ time 430 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 569 (of 1000) ]
[ time 431 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 568 (of 1000) ]
[ time 432 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 567 (of 1000) ]
[ time 433 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 566 (of 1000) ]
[ time 434 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 565 (of 1000) ]
[ time 435 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 564 (of 1000) ]
[ time 436 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 563 (of 1000) ]
[ time 437 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 562 (of 1000) ]
[ time 438 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 561 (of 1000) ]
[ time 439 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 560 (of 1000) ]
[ time 440 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 559 (of 1000) ]
[ time 441 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 558 (of 1000) ]
[ time 442 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 557 (of 1000) ]
[ time 443 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 556 (of 1000) ]
[ time 444 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 555 (of 1000) ]
[ time 445 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 554 (of 1000) ]
[ time 446 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 553 (of 1000) ]
[ time 447 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 552 (of 1000) ]
[ time 448 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 551 (of 1000) ]
[ time 449 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 550 (of 1000) ]
[ time 450 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 549 (of 1000) ]
[ time 451 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 548 (of 1000) ]
[ time 452 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 547 (of 1000) ]
[ time 453 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 546 (of 1000) ]
[ time 454 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 545 (of 1000) ]
[ time 455 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 544 (of 1000) ]
[ time 456 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 543 (of 1000) ]
[ time 457 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 542 (of 1000) ]
[ time 458 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 541 (of 1000) ]
[ time 459 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 540 (of 1000) ]
[ time 460 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 539 (of 1000) ]
[ time 461 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 538 (of 1000) ]
[ time 462 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 537 (of 1000) ]
[ time 463 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 536 (of 1000) ]
[ time 464 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 535 (of 1000) ]
[ time 465 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 534 (of 1000) ]
[ time 466 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 533 (of 1000) ]
[ time 467 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 532 (of 1000) ]
[ time 468 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 531 (of 1000) ]
[ time 469 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 530 (of 1000) ]
[ time 470 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 529 (of 1000) ]
[ time 471 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 528 (of 1000) ]
[ time 472 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 527 (of 1000) ]
[ time 473 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 526 (of 1000) ]
[ time 474 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 525 (of 1000) ]
[ time 475 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 524 (of 1000) ]
[ time 476 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 523 (of 1000) ]
[ time 477 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 522 (of 1000) ]
[ time 478 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 521 (of 1000) ]
[ time 479 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 520 (of 1000) ]
[ time 480 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 519 (of 1000) ]
[ time 481 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 518 (of 1000) ]
[ time 482 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 517 (of 1000) ]
[ time 483 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 516 (of 1000) ]
[ time 484 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 515 (of 1000) ]
[ time 485 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 514 (of 1000) ]
[ time 486 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 513 (of 1000) ]
[ time 487 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 512 (of 1000) ]
[ time 488 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 511 (of 1000) ]
[ time 489 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 510 (of 1000) ]
[ time 490 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 509 (of 1000) ]
[ time 491 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 508 (of 1000) ]
[ time 492 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 507 (of 1000) ]
[ time 493 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 506 (of 1000) ]
[ time 494 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 505 (of 1000) ]
[ time 495 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 504 (of 1000) ]
[ time 496 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 503 (of 1000) ]
[ time 497 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 502 (of 1000) ]
[ time 498 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 501 (of 1000) ]
[ time 499 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 500 (of 1000) ]
[ time 500 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 499 (of 1000) ]
[ time 501 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 498 (of 1000) ]
[ time 502 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 497 (of 1000) ]
[ time 503 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 496 (of 1000) ]
[ time 504 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 495 (of 1000) ]
[ time 505 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 494 (of 1000) ]
[ time 506 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 493 (of 1000) ]
[ time 507 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 492 (of 1000) ]
[ time 508 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 491 (of 1000) ]
[ time 509 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 490 (of 1000) ]
[ time 510 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 489 (of 1000) ]
[ time 511 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 488 (of 1000) ]
[ time 512 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 487 (of 1000) ]
[ time 513 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 486 (of 1000) ]
[ time 514 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 485 (of 1000) ]
[ time 515 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 484 (of 1000) ]
[ time 516 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 483 (of 1000) ]
[ time 517 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 482 (of 1000) ]
[ time 518 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 481 (of 1000) ]
[ time 519 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 480 (of 1000) ]
[ time 520 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 479 (of 1000) ]
[ time 521 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 478 (of 1000) ]
[ time 522 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 477 (of 1000) ]
[ time 523 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 476 (of 1000) ]
[ time 524 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 475 (of 1000) ]
[ time 525 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 474 (of 1000) ]
[ time 526 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 473 (of 1000) ]
[ time 527 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 472 (of 1000) ]
[ time 528 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 471 (of 1000) ]
[ time 529 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 470 (of 1000) ]
[ time 530 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 469 (of 1000) ]
[ time 531 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 468 (of 1000) ]
[ time 532 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 467 (of 1000) ]
[ time 533 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 466 (of 1000) ]
[ time 534 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 465 (of 1000) ]
[ time 535 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 464 (of 1000) ]
[ time 536 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 463 (of 1000) ]
[ time 537 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 462 (of 1000) ]
[ time 538 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 461 (of 1000) ]
[ time 539 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 460 (of 1000) ]
[ time 540 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 459 (of 1000) ]
[ time 541 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 458 (of 1000) ]
[ time 542 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 457 (of 1000) ]
[ time 543 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 456 (of 1000) ]
[ time 544 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 455 (of 1000) ]
[ time 545 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 454 (of 1000) ]
[ time 546 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 453 (of 1000) ]
[ time 547 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 452 (of 1000) ]
[ time 548 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 451 (of 1000) ]
[ time 549 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 450 (of 1000) ]
[ time 550 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 449 (of 1000) ]
[ time 551 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 448 (of 1000) ]
[ time 552 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 447 (of 1000) ]
[ time 553 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 446 (of 1000) ]
[ time 554 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 445 (of 1000) ]
[ time 555 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 444 (of 1000) ]
[ time 556 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 443 (of 1000) ]
[ time 557 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 442 (of 1000) ]
[ time 558 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 441 (of 1000) ]
[ time 559 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 440 (of 1000) ]
[ time 560 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 439 (of 1000) ]
[ time 561 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 438 (of 1000) ]
[ time 562 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 437 (of 1000) ]
[ time 563 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 436 (of 1000) ]
[ time 564 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 435 (of 1000) ]
[ time 565 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 434 (of 1000) ]
[ time 566 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 433 (of 1000) ]
[ time 567 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 432 (of 1000) ]
[ time 568 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 431 (of 1000) ]
[ time 569 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 430 (of 1000) ]
[ time 570 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 429 (of 1000) ]
[ time 571 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 428 (of 1000) ]
[ time 572 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 427 (of 1000) ]
[ time 573 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 426 (of 1000) ]
[ time 574 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 425 (of 1000) ]
[ time 575 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 424 (of 1000) ]
[ time 576 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 423 (of 1000) ]
[ time 577 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 422 (of 1000) ]
[ time 578 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 421 (of 1000) ]
[ time 579 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 420 (of 1000) ]
[ time 580 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 419 (of 1000) ]
[ time 581 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 418 (of 1000) ]
[ time 582 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 417 (of 1000) ]
[ time 583 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 416 (of 1000) ]
[ time 584 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 415 (of 1000) ]
[ time 585 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 414 (of 1000) ]
[ time 586 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 413 (of 1000) ]
[ time 587 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 412 (of 1000) ]
[ time 588 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 411 (of 1000) ]
[ time 589 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 410 (of 1000) ]
[ time 590 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 409 (of 1000) ]
[ time 591 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 408 (of 1000) ]
[ time 592 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 407 (of 1000) ]
[ time 593 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 406 (of 1000) ]
[ time 594 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 405 (of 1000) ]
[ time 595 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 404 (of 1000) ]
[ time 596 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 403 (of 1000) ]
[ time 597 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 402 (of 1000) ]
[ time 598 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 401 (of 1000) ]
[ time 599 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 400 (of 1000) ]
[ time 600 ] BOOST ( every 200 )
[ time 600 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 399 (of 1000) ]
[ time 601 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 398 (of 1000) ]
[ time 602 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 397 (of 1000) ]
[ time 603 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 396 (of 1000) ]
[ time 604 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 395 (of 1000) ]
[ time 605 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 394 (of 1000) ]
[ time 606 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 393 (of 1000) ]
[ time 607 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 392 (of 1000) ]
[ time 608 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 391 (of 1000) ]
[ time 609 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 390 (of 1000) ]
[ time 610 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 389 (of 1000) ]
[ time 611 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 388 (of 1000) ]
[ time 612 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 387 (of 1000) ]
[ time 613 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 386 (of 1000) ]
[ time 614 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 385 (of 1000) ]
[ time 615 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 384 (of 1000) ]
[ time 616 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 383 (of 1000) ]
[ time 617 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 382 (of 1000) ]
[ time 618 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 381 (of 1000) ]
[ time 619 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 380 (of 1000) ]
[ time 620 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 379 (of 1000) ]
[ time 621 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 378 (of 1000) ]
[ time 622 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 377 (of 1000) ]
[ time 623 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 376 (of 1000) ]
[ time 624 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 375 (of 1000) ]
[ time 625 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 374 (of 1000) ]
[ time 626 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 373 (of 1000) ]
[ time 627 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 372 (of 1000) ]
[ time 628 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 371 (of 1000) ]
[ time 629 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 370 (of 1000) ]
[ time 630 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 369 (of 1000) ]
[ time 631 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 368 (of 1000) ]
[ time 632 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 367 (of 1000) ]
[ time 633 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 366 (of 1000) ]
[ time 634 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 365 (of 1000) ]
[ time 635 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 364 (of 1000) ]
[ time 636 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 363 (of 1000) ]
[ time 637 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 362 (of 1000) ]
[ time 638 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 361 (of 1000) ]
[ time 639 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 360 (of 1000) ]
[ time 640 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 359 (of 1000) ]
[ time 641 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 358 (of 1000) ]
[ time 642 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 357 (of 1000) ]
[ time 643 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 356 (of 1000) ]
[ time 644 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 355 (of 1000) ]
[ time 645 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 354 (of 1000) ]
[ time 646 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 353 (of 1000) ]
[ time 647 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 352 (of 1000) ]
[ time 648 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 351 (of 1000) ]
[ time 649 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 350 (of 1000) ]
[ time 650 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 349 (of 1000) ]
[ time 651 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 348 (of 1000) ]
[ time 652 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 347 (of 1000) ]
[ time 653 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 346 (of 1000) ]
[ time 654 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 345 (of 1000) ]
[ time 655 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 344 (of 1000) ]
[ time 656 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 343 (of 1000) ]
[ time 657 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 342 (of 1000) ]
[ time 658 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 341 (of 1000) ]
[ time 659 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 340 (of 1000) ]
[ time 660 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 339 (of 1000) ]
[ time 661 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 338 (of 1000) ]
[ time 662 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 337 (of 1000) ]
[ time 663 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 336 (of 1000) ]
[ time 664 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 335 (of 1000) ]
[ time 665 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 334 (of 1000) ]
[ time 666 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 333 (of 1000) ]
[ time 667 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 332 (of 1000) ]
[ time 668 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 331 (of 1000) ]
[ time 669 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 330 (of 1000) ]
[ time 670 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 329 (of 1000) ]
[ time 671 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 328 (of 1000) ]
[ time 672 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 327 (of 1000) ]
[ time 673 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 326 (of 1000) ]
[ time 674 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 325 (of 1000) ]
[ time 675 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 324 (of 1000) ]
[ time 676 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 323 (of 1000) ]
[ time 677 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 322 (of 1000) ]
[ time 678 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 321 (of 1000) ]
[ time 679 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 320 (of 1000) ]
[ time 680 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 319 (of 1000) ]
[ time 681 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 318 (of 1000) ]
[ time 682 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 317 (of 1000) ]
[ time 683 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 316 (of 1000) ]
[ time 684 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 315 (of 1000) ]
[ time 685 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 314 (of 1000) ]
[ time 686 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 313 (of 1000) ]
[ time 687 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 312 (of 1000) ]
[ time 688 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 311 (of 1000) ]
[ time 689 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 310 (of 1000) ]
[ time 690 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 309 (of 1000) ]
[ time 691 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 308 (of 1000) ]
[ time 692 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 307 (of 1000) ]
[ time 693 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 306 (of 1000) ]
[ time 694 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 305 (of 1000) ]
[ time 695 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 304 (of 1000) ]
[ time 696 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 303 (of 1000) ]
[ time 697 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 302 (of 1000) ]
[ time 698 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 301 (of 1000) ]
[ time 699 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 300 (of 1000) ]
[ time 700 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 299 (of 1000) ]
[ time 701 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 298 (of 1000) ]
[ time 702 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 297 (of 1000) ]
[ time 703 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 296 (of 1000) ]
[ time 704 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 295 (of 1000) ]
[ time 705 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 294 (of 1000) ]
[ time 706 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 293 (of 1000) ]
[ time 707 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 292 (of 1000) ]
[ time 708 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 291 (of 1000) ]
[ time 709 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 290 (of 1000) ]
[ time 710 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 289 (of 1000) ]
[ time 711 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 288 (of 1000) ]
[ time 712 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 287 (of 1000) ]
[ time 713 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 286 (of 1000) ]
[ time 714 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 285 (of 1000) ]
[ time 715 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 284 (of 1000) ]
[ time 716 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 283 (of 1000) ]
[ time 717 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 282 (of 1000) ]
[ time 718 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 281 (of 1000) ]
[ time 719 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 280 (of 1000) ]
[ time 720 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 279 (of 1000) ]
[ time 721 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 278 (of 1000) ]
[ time 722 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 277 (of 1000) ]
[ time 723 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 276 (of 1000) ]
[ time 724 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 275 (of 1000) ]
[ time 725 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 274 (of 1000) ]
[ time 726 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 273 (of 1000) ]
[ time 727 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 272 (of 1000) ]
[ time 728 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 271 (of 1000) ]
[ time 729 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 270 (of 1000) ]
[ time 730 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 269 (of 1000) ]
[ time 731 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 268 (of 1000) ]
[ time 732 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 267 (of 1000) ]
[ time 733 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 266 (of 1000) ]
[ time 734 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 265 (of 1000) ]
[ time 735 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 264 (of 1000) ]
[ time 736 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 263 (of 1000) ]
[ time 737 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 262 (of 1000) ]
[ time 738 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 261 (of 1000) ]
[ time 739 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 260 (of 1000) ]
[ time 740 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 259 (of 1000) ]
[ time 741 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 258 (of 1000) ]
[ time 742 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 257 (of 1000) ]
[ time 743 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 256 (of 1000) ]
[ time 744 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 255 (of 1000) ]
[ time 745 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 254 (of 1000) ]
[ time 746 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 253 (of 1000) ]
[ time 747 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 252 (of 1000) ]
[ time 748 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 251 (of 1000) ]
[ time 749 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 250 (of 1000) ]
[ time 750 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 249 (of 1000) ]
[ time 751 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 248 (of 1000) ]
[ time 752 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 247 (of 1000) ]
[ time 753 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 246 (of 1000) ]
[ time 754 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 245 (of 1000) ]
[ time 755 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 244 (of 1000) ]
[ time 756 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 243 (of 1000) ]
[ time 757 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 242 (of 1000) ]
[ time 758 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 241 (of 1000) ]
[ time 759 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 240 (of 1000) ]
[ time 760 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 239 (of 1000) ]
[ time 761 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 238 (of 1000) ]
[ time 762 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 237 (of 1000) ]
[ time 763 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 236 (of 1000) ]
[ time 764 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 235 (of 1000) ]
[ time 765 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 234 (of 1000) ]
[ time 766 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 233 (of 1000) ]
[ time 767 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 232 (of 1000) ]
[ time 768 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 231 (of 1000) ]
[ time 769 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 230 (of 1000) ]
[ time 770 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 229 (of 1000) ]
[ time 771 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 228 (of 1000) ]
[ time 772 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 227 (of 1000) ]
[ time 773 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 226 (of 1000) ]
[ time 774 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 225 (of 1000) ]
[ time 775 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 224 (of 1000) ]
[ time 776 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 223 (of 1000) ]
[ time 777 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 222 (of 1000) ]
[ time 778 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 221 (of 1000) ]
[ time 779 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 220 (of 1000) ]
[ time 780 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 219 (of 1000) ]
[ time 781 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 218 (of 1000) ]
[ time 782 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 217 (of 1000) ]
[ time 783 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 216 (of 1000) ]
[ time 784 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 215 (of 1000) ]
[ time 785 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 214 (of 1000) ]
[ time 786 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 213 (of 1000) ]
[ time 787 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 212 (of 1000) ]
[ time 788 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 211 (of 1000) ]
[ time 789 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 210 (of 1000) ]
[ time 790 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 209 (of 1000) ]
[ time 791 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 208 (of 1000) ]
[ time 792 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 207 (of 1000) ]
[ time 793 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 206 (of 1000) ]
[ time 794 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 205 (of 1000) ]
[ time 795 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 204 (of 1000) ]
[ time 796 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 203 (of 1000) ]
[ time 797 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 202 (of 1000) ]
[ time 798 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 201 (of 1000) ]
[ time 799 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 200 (of 1000) ]
[ time 800 ] BOOST ( every 200 )
[ time 800 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 199 (of 1000) ]
[ time 801 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 198 (of 1000) ]
[ time 802 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 197 (of 1000) ]
[ time 803 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 196 (of 1000) ]
[ time 804 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 195 (of 1000) ]
[ time 805 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 194 (of 1000) ]
[ time 806 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 193 (of 1000) ]
[ time 807 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 192 (of 1000) ]
[ time 808 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 191 (of 1000) ]
[ time 809 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 190 (of 1000) ]
[ time 810 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 189 (of 1000) ]
[ time 811 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 188 (of 1000) ]
[ time 812 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 187 (of 1000) ]
[ time 813 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 186 (of 1000) ]
[ time 814 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 185 (of 1000) ]
[ time 815 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 184 (of 1000) ]
[ time 816 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 183 (of 1000) ]
[ time 817 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 182 (of 1000) ]
[ time 818 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 181 (of 1000) ]
[ time 819 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 180 (of 1000) ]
[ time 820 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 179 (of 1000) ]
[ time 821 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 178 (of 1000) ]
[ time 822 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 177 (of 1000) ]
[ time 823 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 176 (of 1000) ]
[ time 824 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 175 (of 1000) ]
[ time 825 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 174 (of 1000) ]
[ time 826 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 173 (of 1000) ]
[ time 827 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 172 (of 1000) ]
[ time 828 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 171 (of 1000) ]
[ time 829 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 170 (of 1000) ]
[ time 830 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 169 (of 1000) ]
[ time 831 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 168 (of 1000) ]
[ time 832 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 167 (of 1000) ]
[ time 833 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 166 (of 1000) ]
[ time 834 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 165 (of 1000) ]
[ time 835 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 164 (of 1000) ]
[ time 836 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 163 (of 1000) ]
[ time 837 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 162 (of 1000) ]
[ time 838 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 161 (of 1000) ]
[ time 839 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 160 (of 1000) ]
[ time 840 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 159 (of 1000) ]
[ time 841 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 158 (of 1000) ]
[ time 842 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 157 (of 1000) ]
[ time 843 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 156 (of 1000) ]
[ time 844 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 155 (of 1000) ]
[ time 845 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 154 (of 1000) ]
[ time 846 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 153 (of 1000) ]
[ time 847 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 152 (of 1000) ]
[ time 848 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 151 (of 1000) ]
[ time 849 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 150 (of 1000) ]
[ time 850 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 149 (of 1000) ]
[ time 851 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 148 (of 1000) ]
[ time 852 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 147 (of 1000) ]
[ time 853 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 146 (of 1000) ]
[ time 854 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 145 (of 1000) ]
[ time 855 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 144 (of 1000) ]
[ time 856 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 143 (of 1000) ]
[ time 857 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 142 (of 1000) ]
[ time 858 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 141 (of 1000) ]
[ time 859 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 140 (of 1000) ]
[ time 860 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 139 (of 1000) ]
[ time 861 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 138 (of 1000) ]
[ time 862 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 137 (of 1000) ]
[ time 863 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 136 (of 1000) ]
[ time 864 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 135 (of 1000) ]
[ time 865 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 134 (of 1000) ]
[ time 866 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 133 (of 1000) ]
[ time 867 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 132 (of 1000) ]
[ time 868 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 131 (of 1000) ]
[ time 869 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 130 (of 1000) ]
[ time 870 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 129 (of 1000) ]
[ time 871 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 128 (of 1000) ]
[ time 872 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 127 (of 1000) ]
[ time 873 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 126 (of 1000) ]
[ time 874 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 125 (of 1000) ]
[ time 875 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 124 (of 1000) ]
[ time 876 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 123 (of 1000) ]
[ time 877 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 122 (of 1000) ]
[ time 878 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 121 (of 1000) ]
[ time 879 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 120 (of 1000) ]
[ time 880 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 119 (of 1000) ]
[ time 881 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 118 (of 1000) ]
[ time 882 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 117 (of 1000) ]
[ time 883 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 116 (of 1000) ]
[ time 884 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 115 (of 1000) ]
[ time 885 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 114 (of 1000) ]
[ time 886 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 113 (of 1000) ]
[ time 887 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 112 (of 1000) ]
[ time 888 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 111 (of 1000) ]
[ time 889 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 110 (of 1000) ]
[ time 890 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 109 (of 1000) ]
[ time 891 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 108 (of 1000) ]
[ time 892 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 107 (of 1000) ]
[ time 893 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 106 (of 1000) ]
[ time 894 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 105 (of 1000) ]
[ time 895 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 104 (of 1000) ]
[ time 896 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 103 (of 1000) ]
[ time 897 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 102 (of 1000) ]
[ time 898 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 101 (of 1000) ]
[ time 899 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 100 (of 1000) ]
[ time 900 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 99 (of 1000) ]
[ time 901 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 98 (of 1000) ]
[ time 902 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 97 (of 1000) ]
[ time 903 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 96 (of 1000) ]
[ time 904 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 95 (of 1000) ]
[ time 905 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 94 (of 1000) ]
[ time 906 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 93 (of 1000) ]
[ time 907 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 92 (of 1000) ]
[ time 908 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 91 (of 1000) ]
[ time 909 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 90 (of 1000) ]
[ time 910 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 89 (of 1000) ]
[ time 911 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 88 (of 1000) ]
[ time 912 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 87 (of 1000) ]
[ time 913 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 86 (of 1000) ]
[ time 914 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 85 (of 1000) ]
[ time 915 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 84 (of 1000) ]
[ time 916 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 83 (of 1000) ]
[ time 917 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 82 (of 1000) ]
[ time 918 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 81 (of 1000) ]
[ time 919 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 80 (of 1000) ]
[ time 920 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 79 (of 1000) ]
[ time 921 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 78 (of 1000) ]
[ time 922 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 77 (of 1000) ]
[ time 923 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 76 (of 1000) ]
[ time 924 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 75 (of 1000) ]
[ time 925 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 74 (of 1000) ]
[ time 926 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 73 (of 1000) ]
[ time 927 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 72 (of 1000) ]
[ time 928 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 71 (of 1000) ]
[ time 929 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 70 (of 1000) ]
[ time 930 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 69 (of 1000) ]
[ time 931 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 68 (of 1000) ]
[ time 932 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 67 (of 1000) ]
[ time 933 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 66 (of 1000) ]
[ time 934 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 65 (of 1000) ]
[ time 935 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 64 (of 1000) ]
[ time 936 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 63 (of 1000) ]
[ time 937 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 62 (of 1000) ]
[ time 938 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 61 (of 1000) ]
[ time 939 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 60 (of 1000) ]
[ time 940 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 59 (of 1000) ]
[ time 941 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 58 (of 1000) ]
[ time 942 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 57 (of 1000) ]
[ time 943 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 56 (of 1000) ]
[ time 944 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 55 (of 1000) ]
[ time 945 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 54 (of 1000) ]
[ time 946 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 53 (of 1000) ]
[ time 947 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 52 (of 1000) ]
[ time 948 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 51 (of 1000) ]
[ time 949 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 50 (of 1000) ]
[ time 950 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 49 (of 1000) ]
[ time 951 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 48 (of 1000) ]
[ time 952 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 47 (of 1000) ]
[ time 953 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 46 (of 1000) ]
[ time 954 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 45 (of 1000) ]
[ time 955 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 44 (of 1000) ]
[ time 956 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 43 (of 1000) ]
[ time 957 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 42 (of 1000) ]
[ time 958 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 41 (of 1000) ]
[ time 959 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 40 (of 1000) ]
[ time 960 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 39 (of 1000) ]
[ time 961 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 38 (of 1000) ]
[ time 962 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 37 (of 1000) ]
[ time 963 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 36 (of 1000) ]
[ time 964 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 35 (of 1000) ]
[ time 965 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 34 (of 1000) ]
[ time 966 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 33 (of 1000) ]
[ time 967 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 32 (of 1000) ]
[ time 968 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 31 (of 1000) ]
[ time 969 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 30 (of 1000) ]
[ time 970 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 29 (of 1000) ]
[ time 971 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 28 (of 1000) ]
[ time 972 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 27 (of 1000) ]
[ time 973 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 26 (of 1000) ]
[ time 974 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 25 (of 1000) ]
[ time 975 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 24 (of 1000) ]
[ time 976 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 23 (of 1000) ]
[ time 977 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 22 (of 1000) ]
[ time 978 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 21 (of 1000) ]
[ time 979 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 20 (of 1000) ]
[ time 980 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 19 (of 1000) ]
[ time 981 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 18 (of 1000) ]
[ time 982 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 17 (of 1000) ]
[ time 983 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 16 (of 1000) ]
[ time 984 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 15 (of 1000) ]
[ time 985 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 14 (of 1000) ]
[ time 986 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 13 (of 1000) ]
[ time 987 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 12 (of 1000) ]
[ time 988 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 11 (of 1000) ]
[ time 989 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 10 (of 1000) ]
[ time 990 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 1000) ]
[ time 991 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 1000) ]
[ time 992 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 1000) ]
[ time 993 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 1000) ]
[ time 994 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 1000) ]
[ time 995 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 1000) ]
[ time 996 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 1000) ]
[ time 997 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 1000) ]
[ time 998 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 1000) ]
[ time 999 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 0 (of 1000) ]
[ time 1000 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 1000

  Avg  0: startTime n/a - response 0.00 - turnaround 1000.00
```

This boosts the priority every 200 ms (`-B 200`), ensuring the long-running job gets CPU time.

6. One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the `-I` flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.

`python mlfq.py -n 3 -Q 10,20,30 -l 0,100,5:10,50,0 -I -c`

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 3
OPTIONS allotments for queue  2 is   1
OPTIONS quantum length for queue  2 is  10
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  20
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  30
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump True


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime 100 - ioFreq   5
  Job  1: startTime  10 - runTime  50 - ioFreq   0


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] Run JOB 0 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 99 (of 100) ]
[ time 1 ] Run JOB 0 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 98 (of 100) ]
[ time 2 ] Run JOB 0 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 97 (of 100) ]
[ time 3 ] Run JOB 0 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 96 (of 100) ]
[ time 4 ] Run JOB 0 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 95 (of 100) ]
[ time 5 ] IO_START by JOB 0
IO DONE
[ time 5 ] IDLE
[ time 6 ] IDLE
[ time 7 ] IDLE
[ time 8 ] IDLE
[ time 9 ] IDLE
[ time 10 ] JOB BEGINS by JOB 1
[ time 10 ] IO_DONE by JOB 0
[ time 10 ] Run JOB 0 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 94 (of 100) ]
[ time 11 ] Run JOB 0 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 93 (of 100) ]
[ time 12 ] Run JOB 0 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 92 (of 100) ]
[ time 13 ] Run JOB 0 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 91 (of 100) ]
[ time 14 ] Run JOB 0 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 90 (of 100) ]
[ time 15 ] IO_START by JOB 0
IO DONE
[ time 15 ] Run JOB 1 at PRIORITY 2 [ TICKS 9 ALLOT 1 TIME 49 (of 50) ]
[ time 16 ] Run JOB 1 at PRIORITY 2 [ TICKS 8 ALLOT 1 TIME 48 (of 50) ]
[ time 17 ] Run JOB 1 at PRIORITY 2 [ TICKS 7 ALLOT 1 TIME 47 (of 50) ]
[ time 18 ] Run JOB 1 at PRIORITY 2 [ TICKS 6 ALLOT 1 TIME 46 (of 50) ]
[ time 19 ] Run JOB 1 at PRIORITY 2 [ TICKS 5 ALLOT 1 TIME 45 (of 50) ]
[ time 20 ] IO_DONE by JOB 0
[ time 20 ] Run JOB 1 at PRIORITY 2 [ TICKS 4 ALLOT 1 TIME 44 (of 50) ]
[ time 21 ] Run JOB 1 at PRIORITY 2 [ TICKS 3 ALLOT 1 TIME 43 (of 50) ]
[ time 22 ] Run JOB 1 at PRIORITY 2 [ TICKS 2 ALLOT 1 TIME 42 (of 50) ]
[ time 23 ] Run JOB 1 at PRIORITY 2 [ TICKS 1 ALLOT 1 TIME 41 (of 50) ]
[ time 24 ] Run JOB 1 at PRIORITY 2 [ TICKS 0 ALLOT 1 TIME 40 (of 50) ]
[ time 25 ] Run JOB 0 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 89 (of 100) ]
[ time 26 ] Run JOB 0 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 88 (of 100) ]
[ time 27 ] Run JOB 0 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 87 (of 100) ]
[ time 28 ] Run JOB 0 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 86 (of 100) ]
[ time 29 ] Run JOB 0 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 85 (of 100) ]
[ time 30 ] IO_START by JOB 0
IO DONE
[ time 30 ] Run JOB 1 at PRIORITY 1 [ TICKS 19 ALLOT 1 TIME 39 (of 50) ]
[ time 31 ] Run JOB 1 at PRIORITY 1 [ TICKS 18 ALLOT 1 TIME 38 (of 50) ]
[ time 32 ] Run JOB 1 at PRIORITY 1 [ TICKS 17 ALLOT 1 TIME 37 (of 50) ]
[ time 33 ] Run JOB 1 at PRIORITY 1 [ TICKS 16 ALLOT 1 TIME 36 (of 50) ]
[ time 34 ] Run JOB 1 at PRIORITY 1 [ TICKS 15 ALLOT 1 TIME 35 (of 50) ]
[ time 35 ] IO_DONE by JOB 0
[ time 35 ] Run JOB 0 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 84 (of 100) ]
[ time 36 ] Run JOB 0 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 83 (of 100) ]
[ time 37 ] Run JOB 0 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 82 (of 100) ]
[ time 38 ] Run JOB 0 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 81 (of 100) ]
[ time 39 ] Run JOB 0 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 80 (of 100) ]
[ time 40 ] IO_START by JOB 0
IO DONE
[ time 40 ] Run JOB 1 at PRIORITY 1 [ TICKS 14 ALLOT 1 TIME 34 (of 50) ]
[ time 41 ] Run JOB 1 at PRIORITY 1 [ TICKS 13 ALLOT 1 TIME 33 (of 50) ]
[ time 42 ] Run JOB 1 at PRIORITY 1 [ TICKS 12 ALLOT 1 TIME 32 (of 50) ]
[ time 43 ] Run JOB 1 at PRIORITY 1 [ TICKS 11 ALLOT 1 TIME 31 (of 50) ]
[ time 44 ] Run JOB 1 at PRIORITY 1 [ TICKS 10 ALLOT 1 TIME 30 (of 50) ]
[ time 45 ] IO_DONE by JOB 0
[ time 45 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 79 (of 100) ]
[ time 46 ] Run JOB 0 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 78 (of 100) ]
[ time 47 ] Run JOB 0 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 77 (of 100) ]
[ time 48 ] Run JOB 0 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 76 (of 100) ]
[ time 49 ] Run JOB 0 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 75 (of 100) ]
[ time 50 ] IO_START by JOB 0
IO DONE
[ time 50 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 29 (of 50) ]
[ time 51 ] Run JOB 1 at PRIORITY 1 [ TICKS 8 ALLOT 1 TIME 28 (of 50) ]
[ time 52 ] Run JOB 1 at PRIORITY 1 [ TICKS 7 ALLOT 1 TIME 27 (of 50) ]
[ time 53 ] Run JOB 1 at PRIORITY 1 [ TICKS 6 ALLOT 1 TIME 26 (of 50) ]
[ time 54 ] Run JOB 1 at PRIORITY 1 [ TICKS 5 ALLOT 1 TIME 25 (of 50) ]
[ time 55 ] IO_DONE by JOB 0
[ time 55 ] Run JOB 0 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 74 (of 100) ]
[ time 56 ] Run JOB 0 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 73 (of 100) ]
[ time 57 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 72 (of 100) ]
[ time 58 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 71 (of 100) ]
[ time 59 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 70 (of 100) ]
[ time 60 ] IO_START by JOB 0
IO DONE
[ time 60 ] Run JOB 1 at PRIORITY 1 [ TICKS 4 ALLOT 1 TIME 24 (of 50) ]
[ time 61 ] Run JOB 1 at PRIORITY 1 [ TICKS 3 ALLOT 1 TIME 23 (of 50) ]
[ time 62 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 22 (of 50) ]
[ time 63 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 21 (of 50) ]
[ time 64 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 20 (of 50) ]
[ time 65 ] IO_DONE by JOB 0
[ time 65 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 69 (of 100) ]
[ time 66 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 68 (of 100) ]
[ time 67 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 67 (of 100) ]
[ time 68 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 66 (of 100) ]
[ time 69 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 65 (of 100) ]
[ time 70 ] IO_START by JOB 0
IO DONE
[ time 70 ] Run JOB 1 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 19 (of 50) ]
[ time 71 ] Run JOB 1 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 18 (of 50) ]
[ time 72 ] Run JOB 1 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 17 (of 50) ]
[ time 73 ] Run JOB 1 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 16 (of 50) ]
[ time 74 ] Run JOB 1 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 15 (of 50) ]
[ time 75 ] IO_DONE by JOB 0
[ time 75 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 64 (of 100) ]
[ time 76 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 63 (of 100) ]
[ time 77 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 62 (of 100) ]
[ time 78 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 61 (of 100) ]
[ time 79 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 60 (of 100) ]
[ time 80 ] IO_START by JOB 0
IO DONE
[ time 80 ] Run JOB 1 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 14 (of 50) ]
[ time 81 ] Run JOB 1 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 13 (of 50) ]
[ time 82 ] Run JOB 1 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 12 (of 50) ]
[ time 83 ] Run JOB 1 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 11 (of 50) ]
[ time 84 ] Run JOB 1 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 10 (of 50) ]
[ time 85 ] IO_DONE by JOB 0
[ time 85 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 59 (of 100) ]
[ time 86 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 58 (of 100) ]
[ time 87 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 57 (of 100) ]
[ time 88 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 56 (of 100) ]
[ time 89 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 55 (of 100) ]
[ time 90 ] IO_START by JOB 0
IO DONE
[ time 90 ] Run JOB 1 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 9 (of 50) ]
[ time 91 ] Run JOB 1 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 8 (of 50) ]
[ time 92 ] Run JOB 1 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 7 (of 50) ]
[ time 93 ] Run JOB 1 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 6 (of 50) ]
[ time 94 ] Run JOB 1 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 5 (of 50) ]
[ time 95 ] IO_DONE by JOB 0
[ time 95 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 54 (of 100) ]
[ time 96 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 53 (of 100) ]
[ time 97 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 52 (of 100) ]
[ time 98 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 51 (of 100) ]
[ time 99 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 50 (of 100) ]
[ time 100 ] IO_START by JOB 0
IO DONE
[ time 100 ] Run JOB 1 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 4 (of 50) ]
[ time 101 ] Run JOB 1 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 3 (of 50) ]
[ time 102 ] Run JOB 1 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 2 (of 50) ]
[ time 103 ] Run JOB 1 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 1 (of 50) ]
[ time 104 ] Run JOB 1 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 0 (of 50) ]
[ time 105 ] FINISHED JOB 1
[ time 105 ] IO_DONE by JOB 0
[ time 105 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 49 (of 100) ]
[ time 106 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 48 (of 100) ]
[ time 107 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 47 (of 100) ]
[ time 108 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 46 (of 100) ]
[ time 109 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 45 (of 100) ]
[ time 110 ] IO_START by JOB 0
IO DONE
[ time 110 ] IDLE
[ time 111 ] IDLE
[ time 112 ] IDLE
[ time 113 ] IDLE
[ time 114 ] IDLE
[ time 115 ] IO_DONE by JOB 0
[ time 115 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 44 (of 100) ]
[ time 116 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 43 (of 100) ]
[ time 117 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 42 (of 100) ]
[ time 118 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 41 (of 100) ]
[ time 119 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 40 (of 100) ]
[ time 120 ] IO_START by JOB 0
IO DONE
[ time 120 ] IDLE
[ time 121 ] IDLE
[ time 122 ] IDLE
[ time 123 ] IDLE
[ time 124 ] IDLE
[ time 125 ] IO_DONE by JOB 0
[ time 125 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 39 (of 100) ]
[ time 126 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 38 (of 100) ]
[ time 127 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 37 (of 100) ]
[ time 128 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 36 (of 100) ]
[ time 129 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 35 (of 100) ]
[ time 130 ] IO_START by JOB 0
IO DONE
[ time 130 ] IDLE
[ time 131 ] IDLE
[ time 132 ] IDLE
[ time 133 ] IDLE
[ time 134 ] IDLE
[ time 135 ] IO_DONE by JOB 0
[ time 135 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 34 (of 100) ]
[ time 136 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 33 (of 100) ]
[ time 137 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 32 (of 100) ]
[ time 138 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 31 (of 100) ]
[ time 139 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 30 (of 100) ]
[ time 140 ] IO_START by JOB 0
IO DONE
[ time 140 ] IDLE
[ time 141 ] IDLE
[ time 142 ] IDLE
[ time 143 ] IDLE
[ time 144 ] IDLE
[ time 145 ] IO_DONE by JOB 0
[ time 145 ] Run JOB 0 at PRIORITY 0 [ TICKS 19 ALLOT 1 TIME 29 (of 100) ]
[ time 146 ] Run JOB 0 at PRIORITY 0 [ TICKS 18 ALLOT 1 TIME 28 (of 100) ]
[ time 147 ] Run JOB 0 at PRIORITY 0 [ TICKS 17 ALLOT 1 TIME 27 (of 100) ]
[ time 148 ] Run JOB 0 at PRIORITY 0 [ TICKS 16 ALLOT 1 TIME 26 (of 100) ]
[ time 149 ] Run JOB 0 at PRIORITY 0 [ TICKS 15 ALLOT 1 TIME 25 (of 100) ]
[ time 150 ] IO_START by JOB 0
IO DONE
[ time 150 ] IDLE
[ time 151 ] IDLE
[ time 152 ] IDLE
[ time 153 ] IDLE
[ time 154 ] IDLE
[ time 155 ] IO_DONE by JOB 0
[ time 155 ] Run JOB 0 at PRIORITY 0 [ TICKS 14 ALLOT 1 TIME 24 (of 100) ]
[ time 156 ] Run JOB 0 at PRIORITY 0 [ TICKS 13 ALLOT 1 TIME 23 (of 100) ]
[ time 157 ] Run JOB 0 at PRIORITY 0 [ TICKS 12 ALLOT 1 TIME 22 (of 100) ]
[ time 158 ] Run JOB 0 at PRIORITY 0 [ TICKS 11 ALLOT 1 TIME 21 (of 100) ]
[ time 159 ] Run JOB 0 at PRIORITY 0 [ TICKS 10 ALLOT 1 TIME 20 (of 100) ]
[ time 160 ] IO_START by JOB 0
IO DONE
[ time 160 ] IDLE
[ time 161 ] IDLE
[ time 162 ] IDLE
[ time 163 ] IDLE
[ time 164 ] IDLE
[ time 165 ] IO_DONE by JOB 0
[ time 165 ] Run JOB 0 at PRIORITY 0 [ TICKS 9 ALLOT 1 TIME 19 (of 100) ]
[ time 166 ] Run JOB 0 at PRIORITY 0 [ TICKS 8 ALLOT 1 TIME 18 (of 100) ]
[ time 167 ] Run JOB 0 at PRIORITY 0 [ TICKS 7 ALLOT 1 TIME 17 (of 100) ]
[ time 168 ] Run JOB 0 at PRIORITY 0 [ TICKS 6 ALLOT 1 TIME 16 (of 100) ]
[ time 169 ] Run JOB 0 at PRIORITY 0 [ TICKS 5 ALLOT 1 TIME 15 (of 100) ]
[ time 170 ] IO_START by JOB 0
IO DONE
[ time 170 ] IDLE
[ time 171 ] IDLE
[ time 172 ] IDLE
[ time 173 ] IDLE
[ time 174 ] IDLE
[ time 175 ] IO_DONE by JOB 0
[ time 175 ] Run JOB 0 at PRIORITY 0 [ TICKS 4 ALLOT 1 TIME 14 (of 100) ]
[ time 176 ] Run JOB 0 at PRIORITY 0 [ TICKS 3 ALLOT 1 TIME 13 (of 100) ]
[ time 177 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 12 (of 100) ]
[ time 178 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 11 (of 100) ]
[ time 179 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 10 (of 100) ]
[ time 180 ] IO_START by JOB 0
IO DONE
[ time 180 ] IDLE
[ time 181 ] IDLE
[ time 182 ] IDLE
[ time 183 ] IDLE
[ time 184 ] IDLE
[ time 185 ] IO_DONE by JOB 0
[ time 185 ] Run JOB 0 at PRIORITY 0 [ TICKS 29 ALLOT 1 TIME 9 (of 100) ]
[ time 186 ] Run JOB 0 at PRIORITY 0 [ TICKS 28 ALLOT 1 TIME 8 (of 100) ]
[ time 187 ] Run JOB 0 at PRIORITY 0 [ TICKS 27 ALLOT 1 TIME 7 (of 100) ]
[ time 188 ] Run JOB 0 at PRIORITY 0 [ TICKS 26 ALLOT 1 TIME 6 (of 100) ]
[ time 189 ] Run JOB 0 at PRIORITY 0 [ TICKS 25 ALLOT 1 TIME 5 (of 100) ]
[ time 190 ] IO_START by JOB 0
IO DONE
[ time 190 ] IDLE
[ time 191 ] IDLE
[ time 192 ] IDLE
[ time 193 ] IDLE
[ time 194 ] IDLE
[ time 195 ] IO_DONE by JOB 0
[ time 195 ] Run JOB 0 at PRIORITY 0 [ TICKS 24 ALLOT 1 TIME 4 (of 100) ]
[ time 196 ] Run JOB 0 at PRIORITY 0 [ TICKS 23 ALLOT 1 TIME 3 (of 100) ]
[ time 197 ] Run JOB 0 at PRIORITY 0 [ TICKS 22 ALLOT 1 TIME 2 (of 100) ]
[ time 198 ] Run JOB 0 at PRIORITY 0 [ TICKS 21 ALLOT 1 TIME 1 (of 100) ]
[ time 199 ] Run JOB 0 at PRIORITY 0 [ TICKS 20 ALLOT 1 TIME 0 (of 100) ]
[ time 200 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround 200
  Job  1: startTime  10 - response   5 - turnaround  95

  Avg  1: startTime n/a - response 2.50 - turnaround 147.50
```

This uses the `-I` flag to move jobs that finish I/O to the front of the queue.

These are the commands you can use for each specific question. Let me know if you need further clarification or adjustments!
