# Overview

This program, scheduler.py, allows you to see how different schedulers perform
under scheduling metrics such as response time, turnaround time, and total
wait time. Three schedulers are "implemented": FIFO, SJF, and RR.

There are two steps to running the program.

First, run without the -c flag: this shows you what problem to solve without
revealing the answers. For example, if you want to compute response,
turnaround, and wait for three jobs using the FIFO policy, run this:

```sh
prompt> ./scheduler.py -p FIFO -j 3 -s 100
```

If that doesn't work, try this:

```sh
prompt> python ./scheduler.py -p FIFO -j 3 -s 100
```

This specifies the FIFO policy with three jobs, and, importantly, a specific
random seed of 100. If you want to see the solution for this exact problem,
you have to specify this exact same random seed again. Let's run it and see
what happens. This is what you should see:

```sh
prompt> ./scheduler.py -p FIFO -j 3 -s 100
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 100

Here is the job list, with the run time of each job:
  Job 0 (length = 1)
  Job 1 (length = 4)
  Job 2 (length = 7)
```

Compute the turnaround time, response time, and wait time for each job. When
you are done, run this program again, with the same arguments, but with -c,
which will thus provide you with the answers. You can use -s <somenumber> or
your own job list (-l 10,15,20 for example) to generate different problems for
yourself.

As you can see from this example, three jobs are generated: job 0 of length 1,
job 1 of length 4, and job 2 of length 7. As the program states, you can now
use this to compute some statistics and see if you have a grip on the basic
concepts.

Once you are done, you can use the same program to "solve" the problem and see
if you did your work correctly. To do so, use the "-c" flag. The output:

```sh
prompt> ./scheduler.py -p FIFO -j 3 -s 100 -c
ARG policy FIFO
ARG jobs 3
ARG maxlen 10
ARG seed 100

Here is the job list, with the run time of each job:
  Job 0 (length = 1)
  Job 1 (length = 4)
  Job 2 (length = 7)

** Solutions **

Execution trace:
  [time   0] Run job 0 for 1.00 secs (DONE)
  [time   1] Run job 1 for 4.00 secs (DONE)
  [time   5] Run job 2 for 7.00 secs (DONE)

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 1.00  Wait 0.00
  Job   1 -- Response: 1.00  Turnaround 5.00  Wait 1.00
  Job   2 -- Response: 5.00  Turnaround 12.00  Wait 5.00

  Average -- Response: 2.00  Turnaround 6.00  Wait 2.00
```

As you can see from the figure, the -c flag shows you what happened. Job 0 ran
first for 1 second, Job 1 ran second for 4, and then Job 2 ran for 7
seconds. Not too hard; it is FIFO, after all! The execution trace shows these
results.

The final statistics are useful too: they compute the "response time" (the
time a job spends waiting after arrival before first running), the "turnaround
time" (the time it took to complete the job since first arrival), and the
total "wait time" (any time spent ready but not running). The stats are shown
per job and then as an average across all jobs. Of course, you should have
computed these things all before running with the "-c" flag!

If you want to try the same type of problem but with different inputs, try
changing the number of jobs or the random seed or both. Different random seeds
basically give you a way to generate an infinite number of different problems
for yourself, and the "-c" flag lets you check your own work. Keep doing this
until you feel like you really understand the concepts.

One other useful flag is "-l" (that's a lower-case L), which lets you specify
the exact jobs you wish to see scheduled. For example, if you want to find out
how SJF would perform with three jobs of lengths 5, 10, and 15, you can run:

```sh
prompt> ./scheduler.py -p SJF -l 5,10,15
ARG policy SJF
ARG jlist 5,10,15

Here is the job list, with the run time of each job:
  Job 0 (length = 5.0)
  Job 1 (length = 10.0)
  Job 2 (length = 15.0)
...
```

And then you can use -c to solve it again. Note that when you specify the
exact jobs, there is no need to specify a random seed or the number of jobs:
the jobs lengths are taken from your comma-separated list.

Of course, more interesting things happen when you use SJF (shortest-job
first) or even RR (round robin) schedulers. Try them and see!

And you can always run

```sh
prompt> ./scheduler.py -h
```

to get a complete list of flags and options (including options such as setting
the time quantum for the RR scheduler).

### Questions

This program, `scheduler.py`, allows you to see how different schedulers perform under scheduling metrics such as response time, turnaround time, and total wait time. See the README for details.

1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.

`./scheduler.py -j 3 -l 200,200,200 -p SJF -c`

```
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00

```

`./scheduler.py -j 3 -l 200,200,200 -p FIFO -c`

```
ARG policy FIFO
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 200.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 1 for 200.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job 2 for 200.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 200.00  Wait 0.00
  Job   1 -- Response: 200.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 400.00  Turnaround 600.00  Wait 400.00

  Average -- Response: 200.00  Turnaround 400.00  Wait 200.00
```

2. Now do the same but with jobs of different lengths: 100, 200, and 300.

`./scheduler.py -j 3 -l 100,200,300 -p SJF -c`

```
ARG policy SJF
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

`./scheduler.py -j 3 -l 100,200,300 -p FIFO -c`

```
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 200.00 secs ( DONE at 300.00 )
  [ time 300 ] Run job 2 for 300.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 300.00  Wait 100.00
  Job   2 -- Response: 300.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33
```

3. Now do the same, but also with the RR scheduler and a time-slice of 1.

`./scheduler.py -j 3 -l 100,200,300 -p RR -q 1 -c`

[Output](3_homework_output)

4. For what types of workloads does SJF deliver the same turnaround times as FIFO?

If the jobs have the same length, both SJF and FIFO should give the same turnaround times

`./scheduler.py -j 3 -l 100,100,100 -p SJF -c`
`./scheduler.py -j 3 -l 100,100,100 -p FIFO -c`

```
ARG policy FIFO
ARG jlist 100,100,100

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 100.0 )
  Job 2 ( length = 100.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 100.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 2 for 100.00 secs ( DONE at 300.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 200.00  Wait 100.00
  Job   2 -- Response: 200.00  Turnaround 300.00  Wait 200.00

  Average -- Response: 100.00  Turnaround 200.00  Wait 100.00
```

5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?

When all jobs have the same length and equal time slice

`./scheduler.py -j 3 -l 100,100,100 -p SJF -c`
`./scheduler.py -j 3 -l 100,100,100 -p RR -q 100 -c`

```
ARG policy SJF
ARG jlist 100,100,100

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 100.0 )
  Job 2 ( length = 100.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job 1 for 100.00 secs ( DONE at 200.00 )
  [ time 200 ] Run job 2 for 100.00 secs ( DONE at 300.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 200.00  Wait 100.00
  Job   2 -- Response: 200.00  Turnaround 300.00  Wait 200.00

  Average -- Response: 100.00  Turnaround 200.00  Wait 100.00
```

6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?

`SJF` with small jobs

`./scheduler.py -j 3 -l 50,100,150 -p SJF -c`

```
ARG policy SJF
ARG jlist 50,100,150

Here is the job list, with the run time of each job:
  Job 0 ( length = 50.0 )
  Job 1 ( length = 100.0 )
  Job 2 ( length = 150.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 50.00 secs ( DONE at 50.00 )
  [ time  50 ] Run job 1 for 100.00 secs ( DONE at 150.00 )
  [ time 150 ] Run job 2 for 150.00 secs ( DONE at 300.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 50.00  Wait 0.00
  Job   1 -- Response: 50.00  Turnaround 150.00  Wait 50.00
  Job   2 -- Response: 150.00  Turnaround 300.00  Wait 150.00

  Average -- Response: 66.67  Turnaround 166.67  Wait 66.67
```

`SJF` with larger jobs

`./scheduler.py -j 3 -l 500,1000,1500 -p SJF -c`

```
ARG policy SJF
ARG jlist 500,1000,1500

Here is the job list, with the run time of each job:
  Job 0 ( length = 500.0 )
  Job 1 ( length = 1000.0 )
  Job 2 ( length = 1500.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job 0 for 500.00 secs ( DONE at 500.00 )
  [ time 500 ] Run job 1 for 1000.00 secs ( DONE at 1500.00 )
  [ time 1500 ] Run job 2 for 1500.00 secs ( DONE at 3000.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 500.00  Wait 0.00
  Job   1 -- Response: 500.00  Turnaround 1500.00  Wait 500.00
  Job   2 -- Response: 1500.00  Turnaround 3000.00  Wait 1500.00

  Average -- Response: 666.67  Turnaround 1666.67  Wait 666.67
```

7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given **N** jobs?

`RR` with small quantum

`./scheduler.py -j 3 -l 100,200,300 -p RR -q 1 -c`

[Output](4_homework_output)

`RR` with larger quantum

`./scheduler.py -j 3 -l 100,200,300 -p RR -q 100 -c`

```
ARG policy RR
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )


** Solutions **

Execution trace:
  [ time   0 ] Run job   0 for 100.00 secs ( DONE at 100.00 )
  [ time 100 ] Run job   1 for 100.00 secs
  [ time 200 ] Run job   2 for 100.00 secs
  [ time 300 ] Run job   1 for 100.00 secs ( DONE at 400.00 )
  [ time 400 ] Run job   2 for 100.00 secs
  [ time 500 ] Run job   2 for 100.00 secs ( DONE at 600.00 )

Final statistics:
  Job   0 -- Response: 0.00  Turnaround 100.00  Wait 0.00
  Job   1 -- Response: 100.00  Turnaround 400.00  Wait 200.00
  Job   2 -- Response: 200.00  Turnaround 600.00  Wait 300.00

  Average -- Response: 100.00  Turnaround 366.67  Wait 166.67
```
