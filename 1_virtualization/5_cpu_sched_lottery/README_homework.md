# Overview

This program, lottery.py, allows you to see how a lottery scheduler
works. As always, there are two steps to running the program. First, run
without the -c flag: this shows you what problem to solve without
revealing the answers.

```sh
prompt> ./lottery.py -j 2 -s 0
...
Here is the job list, with the run time of each job:
  Job 0 ( length = 8, tickets = 75 )
  Job 1 ( length = 4, tickets = 25 )

Here is the set of random numbers you will need (at most):
Random 511275
Random 404934
Random 783799
Random 303313
Random 476597
Random 583382
Random 908113
Random 504687
Random 281838
Random 755804
Random 618369
Random 250506
```

When you run the simulator in this manner, it first assigns you some random
jobs (here of lengths 8, and 4), each with some number of tickets (here 75 and
25, respectively). The simulator also gives you a list of random numbers,
which you will need to determine what the lottery scheduler will do. The
random numbers are chosen to be between 0 and a large number; thus, you'll
have to use the modulo operator to compute the lottery winner (i.e., winner
should equal this random number modulo the total number of tickets in the
system).

Running with -c shows exactly what you are supposed to calculate:

```sh
prompt> ./lottery.py -j 2 -s 0 -c
...
** Solutions **
Random 511275 -> Winning ticket 75 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:8 tix:75 ) (* job:1 timeleft:4 tix:25 )
Random 404934 -> Winning ticket 34 (of 100) -> Run 0
  Jobs:  (* job:0 timeleft:8 tix:75 ) (  job:1 timeleft:3 tix:25 )
Random 783799 -> Winning ticket 99 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:7 tix:75 ) (* job:1 timeleft:3 tix:25 )
Random 303313 -> Winning ticket 13 (of 100) -> Run 0
  Jobs:  (* job:0 timeleft:7 tix:75 ) (  job:1 timeleft:2 tix:25 )
Random 476597 -> Winning ticket 97 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:6 tix:75 ) (* job:1 timeleft:2 tix:25 )
Random 583382 -> Winning ticket 82 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:6 tix:75 ) (* job:1 timeleft:1 tix:25 )
--> JOB 1 DONE at time 6
Random 908113 -> Winning ticket 13 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:6 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 504687 -> Winning ticket 12 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:5 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 281838 -> Winning ticket 63 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:4 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 755804 -> Winning ticket 29 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:3 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 618369 -> Winning ticket 69 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:2 tix:75 ) (  job:1 timeleft:0 tix:--- )
Random 250506 -> Winning ticket 6 (of 75) -> Run 0
  Jobs:  (* job:0 timeleft:1 tix:75 ) (  job:1 timeleft:0 tix:--- )
--> JOB 0 DONE at time 12
```

As you can see from this trace, what you are supposed to do is use the random
number to figure out which ticket is the winner. Then, given the winning
ticket, figure out which job should run. Repeat this until all of the jobs are
finished running. It's as simple as that -- you are just emulating what the
lottery scheduler does, but by hand!

Just to make this absolutely clear, let's look at the first decision made in
the example above. At this point, we have two jobs (job 0 which has a runtime
of 8 and 75 tickets, and job 1 which has a runtime of 4 and 25 tickets). The
first random number we are given is 511275. As there are 100 tickets in the
system, 511275 \% 100 is 75, and thus 75 is our winning ticket.

If ticket 75 is the winner, we simply search through the job list until we
find it. The first entry, for job 0, has 75 tickets (0 through 74), and thus
does not win; the next entry is for job 1, and thus we have found our winner,
so we run job 1 for the quantum length (1 in this example). All of this is
shown in the print out as follows:

```sh
Random 511275 -> Winning ticket 75 (of 100) -> Run 1
  Jobs:  (  job:0 timeleft:8 tix:75 ) (* job:1 timeleft:4 tix:25 )
```

As you can see, the first line summarizes what happens, and the second simply
shows the entire job queue, with an \* denoting which job was chosen.

The simulator has a few other options, most of which should be
self-explanatory. Most notably, the -l/--jlist flag can be used to specify an
exact set of jobs and their ticket values, instead of always using
randomly-generated job lists.

```sh
prompt> ./lottery.py -h
Usage: lottery.py [options]

Options:
  -h, --help
      show this help message and exit
  -s SEED, --seed=SEED
      the random seed
  -j JOBS, --jobs=JOBS
      number of jobs in the system
  -l JLIST, --jlist=JLIST
      instead of random jobs, provide a comma-separated list
      of run times and ticket values (e.g., 10:100,20:100
      would have two jobs with run-times of 10 and 20, each
      with 100 tickets)
  -m MAXLEN, --maxlen=MAXLEN
      max length of job
  -T MAXTICKET, --maxtick=MAXTICKET
      maximum ticket value, if randomly assigned
  -q QUANTUM, --quantum=QUANTUM
      length of time slice
  -c, --compute
      compute answers for me
```

## Homework (Simulation)

This program, `lottery.py`, allows you to see how a lottery scheduler works. Use the following commands to complete the exercises.

### 1. Simulate with 3 jobs and random seeds of 1, 2, and 3

For this simulation, use the following commands to set the random seed and simulate 3 jobs.

`python lottery.py -s 1 -j 3 -c`

```
ARG jlist
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 1

Here is the job list, with the run time of each job:
  Job 0 ( length = 1, tickets = 84 )
  Job 1 ( length = 7, tickets = 25 )
  Job 2 ( length = 4, tickets = 44 )


** Solutions **

Random 651593 -> Winning ticket 119 (of 153) -> Run 2
  Jobs:
 (  job:0 timeleft:1 tix:84 )  (  job:1 timeleft:7 tix:25 )  (* job:2 timeleft:4 tix:44 )
Random 788724 -> Winning ticket 9 (of 153) -> Run 0
  Jobs:
 (* job:0 timeleft:1 tix:84 )  (  job:1 timeleft:7 tix:25 )  (  job:2 timeleft:3 tix:44 )
--> JOB 0 DONE at time 2
Random 93859 -> Winning ticket 19 (of 69) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:7 tix:25 )  (  job:2 timeleft:3 tix:44 )
Random 28347 -> Winning ticket 57 (of 69) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:6 tix:25 )  (* job:2 timeleft:3 tix:44 )
Random 835765 -> Winning ticket 37 (of 69) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:6 tix:25 )  (* job:2 timeleft:2 tix:44 )
Random 432767 -> Winning ticket 68 (of 69) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:6 tix:25 )  (* job:2 timeleft:1 tix:44 )
--> JOB 2 DONE at time 6
Random 762280 -> Winning ticket 5 (of 25) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:6 tix:25 )  (  job:2 timeleft:0 tix:--- )
Random 2106 -> Winning ticket 6 (of 25) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:5 tix:25 )  (  job:2 timeleft:0 tix:--- )
Random 445387 -> Winning ticket 12 (of 25) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:4 tix:25 )  (  job:2 timeleft:0 tix:--- )
Random 721540 -> Winning ticket 15 (of 25) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:3 tix:25 )  (  job:2 timeleft:0 tix:--- )
Random 228762 -> Winning ticket 12 (of 25) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:2 tix:25 )  (  job:2 timeleft:0 tix:--- )
Random 945271 -> Winning ticket 21 (of 25) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:1 tix:25 )  (  job:2 timeleft:0 tix:--- )
--> JOB 1 DONE at time 12
```

`python lottery.py -s 2 -j 3 -c`

```
ARG jlist
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 2

Here is the job list, with the run time of each job:
  Job 0 ( length = 9, tickets = 94 )
  Job 1 ( length = 8, tickets = 73 )
  Job 2 ( length = 6, tickets = 30 )


** Solutions **

Random 605944 -> Winning ticket 169 (of 197) -> Run 2
  Jobs:
 (  job:0 timeleft:9 tix:94 )  (  job:1 timeleft:8 tix:73 )  (* job:2 timeleft:6 tix:30 )
Random 606802 -> Winning ticket 42 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:9 tix:94 )  (  job:1 timeleft:8 tix:73 )  (  job:2 timeleft:5 tix:30 )
Random 581204 -> Winning ticket 54 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:8 tix:94 )  (  job:1 timeleft:8 tix:73 )  (  job:2 timeleft:5 tix:30 )
Random 158383 -> Winning ticket 192 (of 197) -> Run 2
  Jobs:
 (  job:0 timeleft:7 tix:94 )  (  job:1 timeleft:8 tix:73 )  (* job:2 timeleft:5 tix:30 )
Random 430670 -> Winning ticket 28 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:7 tix:94 )  (  job:1 timeleft:8 tix:73 )  (  job:2 timeleft:4 tix:30 )
Random 393532 -> Winning ticket 123 (of 197) -> Run 1
  Jobs:
 (  job:0 timeleft:6 tix:94 )  (* job:1 timeleft:8 tix:73 )  (  job:2 timeleft:4 tix:30 )
Random 723012 -> Winning ticket 22 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:6 tix:94 )  (  job:1 timeleft:7 tix:73 )  (  job:2 timeleft:4 tix:30 )
Random 994820 -> Winning ticket 167 (of 197) -> Run 2
  Jobs:
 (  job:0 timeleft:5 tix:94 )  (  job:1 timeleft:7 tix:73 )  (* job:2 timeleft:4 tix:30 )
Random 949396 -> Winning ticket 53 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:5 tix:94 )  (  job:1 timeleft:7 tix:73 )  (  job:2 timeleft:3 tix:30 )
Random 544177 -> Winning ticket 63 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:4 tix:94 )  (  job:1 timeleft:7 tix:73 )  (  job:2 timeleft:3 tix:30 )
Random 444854 -> Winning ticket 28 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:3 tix:94 )  (  job:1 timeleft:7 tix:73 )  (  job:2 timeleft:3 tix:30 )
Random 268241 -> Winning ticket 124 (of 197) -> Run 1
  Jobs:
 (  job:0 timeleft:2 tix:94 )  (* job:1 timeleft:7 tix:73 )  (  job:2 timeleft:3 tix:30 )
Random 35924 -> Winning ticket 70 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:2 tix:94 )  (  job:1 timeleft:6 tix:73 )  (  job:2 timeleft:3 tix:30 )
Random 27444 -> Winning ticket 61 (of 197) -> Run 0
  Jobs:
 (* job:0 timeleft:1 tix:94 )  (  job:1 timeleft:6 tix:73 )  (  job:2 timeleft:3 tix:30 )
--> JOB 0 DONE at time 14
Random 464894 -> Winning ticket 55 (of 103) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:6 tix:73 )  (  job:2 timeleft:3 tix:30 )
Random 318465 -> Winning ticket 92 (of 103) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:5 tix:73 )  (* job:2 timeleft:3 tix:30 )
Random 380015 -> Winning ticket 48 (of 103) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:5 tix:73 )  (  job:2 timeleft:2 tix:30 )
Random 891790 -> Winning ticket 16 (of 103) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:4 tix:73 )  (  job:2 timeleft:2 tix:30 )
Random 525753 -> Winning ticket 41 (of 103) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:3 tix:73 )  (  job:2 timeleft:2 tix:30 )
Random 560510 -> Winning ticket 87 (of 103) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:2 tix:73 )  (* job:2 timeleft:2 tix:30 )
Random 236123 -> Winning ticket 47 (of 103) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:2 tix:73 )  (  job:2 timeleft:1 tix:30 )
Random 23858 -> Winning ticket 65 (of 103) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:1 tix:73 )  (  job:2 timeleft:1 tix:30 )
--> JOB 1 DONE at time 22
Random 325143 -> Winning ticket 3 (of 30) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:1 tix:30 )
--> JOB 2 DONE at time 23
```

`python lottery.py -s 3 -j 3 -c`

```
ARG jlist
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 3

Here is the job list, with the run time of each job:
  Job 0 ( length = 2, tickets = 54 )
  Job 1 ( length = 3, tickets = 60 )
  Job 2 ( length = 6, tickets = 6 )


** Solutions **

Random 13168 -> Winning ticket 88 (of 120) -> Run 1
  Jobs:
 (  job:0 timeleft:2 tix:54 )  (* job:1 timeleft:3 tix:60 )  (  job:2 timeleft:6 tix:6 )
Random 837469 -> Winning ticket 109 (of 120) -> Run 1
  Jobs:
 (  job:0 timeleft:2 tix:54 )  (* job:1 timeleft:2 tix:60 )  (  job:2 timeleft:6 tix:6 )
Random 259354 -> Winning ticket 34 (of 120) -> Run 0
  Jobs:
 (* job:0 timeleft:2 tix:54 )  (  job:1 timeleft:1 tix:60 )  (  job:2 timeleft:6 tix:6 )
Random 234331 -> Winning ticket 91 (of 120) -> Run 1
  Jobs:
 (  job:0 timeleft:1 tix:54 )  (* job:1 timeleft:1 tix:60 )  (  job:2 timeleft:6 tix:6 )
--> JOB 1 DONE at time 4
Random 995645 -> Winning ticket 5 (of 60) -> Run 0
  Jobs:
 (* job:0 timeleft:1 tix:54 )  (  job:1 timeleft:0 tix:--- )  (  job:2 timeleft:6 tix:6 )
--> JOB 0 DONE at time 5
Random 470263 -> Winning ticket 1 (of 6) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:6 tix:6 )
Random 836462 -> Winning ticket 2 (of 6) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:5 tix:6 )
Random 476353 -> Winning ticket 1 (of 6) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:4 tix:6 )
Random 639068 -> Winning ticket 2 (of 6) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:3 tix:6 )
Random 150616 -> Winning ticket 4 (of 6) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:2 tix:6 )
Random 634861 -> Winning ticket 1 (of 6) -> Run 2
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (  job:1 timeleft:0 tix:--- )  (* job:2 timeleft:1 tix:6 )
--> JOB 2 DONE at time 11
```

### 2. Run with two specific jobs (job 0 with 1 ticket, job 1 with 100 tickets)

For this exercise, simulate two jobs, each with a run-time of 10, but one with 1 ticket and the other with 100 tickets.

`python lottery.py -l 10:1,10:100 -c`

```
ARG jlist 10:1,10:100
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 0

Here is the job list, with the run time of each job:
  Job 0 ( length = 10, tickets = 1 )
  Job 1 ( length = 10, tickets = 100 )


** Solutions **

Random 844422 -> Winning ticket 62 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:10 tix:100 )
Random 757955 -> Winning ticket 51 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:9 tix:100 )
Random 420572 -> Winning ticket 8 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:8 tix:100 )
Random 258917 -> Winning ticket 54 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:7 tix:100 )
Random 511275 -> Winning ticket 13 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:6 tix:100 )
Random 404934 -> Winning ticket 25 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:5 tix:100 )
Random 783799 -> Winning ticket 39 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:4 tix:100 )
Random 303313 -> Winning ticket 10 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:3 tix:100 )
Random 476597 -> Winning ticket 79 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:2 tix:100 )
Random 583382 -> Winning ticket 6 (of 101) -> Run 1
  Jobs:
 (  job:0 timeleft:10 tix:1 )  (* job:1 timeleft:1 tix:100 )
--> JOB 1 DONE at time 10
Random 908113 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:10 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 504687 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:9 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 281838 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:8 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 755804 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:7 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 618369 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:6 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 250506 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:5 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 909747 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:4 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 982786 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:3 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 810218 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:2 tix:1 )  (  job:1 timeleft:0 tix:--- )
Random 902166 -> Winning ticket 0 (of 1) -> Run 0
  Jobs:
 (* job:0 timeleft:1 tix:1 )  (  job:1 timeleft:0 tix:--- )
--> JOB 0 DONE at time 20
```

Observe how often job 0 (with fewer tickets) runs before job 1 completes.

### 3. Run with two jobs of length 100 and equal tickets

Simulate two jobs of length 100 with equal ticket allocations of 100.

`python lottery.py -l 100:100,100:100 -c`

```
ARG jlist 100:100,100:100
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 0

Here is the job list, with the run time of each job:
  Job 0 ( length = 100, tickets = 100 )
  Job 1 ( length = 100, tickets = 100 )


** Solutions **

Random 844422 -> Winning ticket 22 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:100 tix:100 )  (  job:1 timeleft:100 tix:100 )
Random 757955 -> Winning ticket 155 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:99 tix:100 )  (* job:1 timeleft:100 tix:100 )
Random 420572 -> Winning ticket 172 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:99 tix:100 )  (* job:1 timeleft:99 tix:100 )
Random 258917 -> Winning ticket 117 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:99 tix:100 )  (* job:1 timeleft:98 tix:100 )
Random 511275 -> Winning ticket 75 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:99 tix:100 )  (  job:1 timeleft:97 tix:100 )
Random 404934 -> Winning ticket 134 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:98 tix:100 )  (* job:1 timeleft:97 tix:100 )
Random 783799 -> Winning ticket 199 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:98 tix:100 )  (* job:1 timeleft:96 tix:100 )
Random 303313 -> Winning ticket 113 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:98 tix:100 )  (* job:1 timeleft:95 tix:100 )
Random 476597 -> Winning ticket 197 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:98 tix:100 )  (* job:1 timeleft:94 tix:100 )
Random 583382 -> Winning ticket 182 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:98 tix:100 )  (* job:1 timeleft:93 tix:100 )
Random 908113 -> Winning ticket 113 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:98 tix:100 )  (* job:1 timeleft:92 tix:100 )
Random 504687 -> Winning ticket 87 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:98 tix:100 )  (  job:1 timeleft:91 tix:100 )
Random 281838 -> Winning ticket 38 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:97 tix:100 )  (  job:1 timeleft:91 tix:100 )
Random 755804 -> Winning ticket 4 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:96 tix:100 )  (  job:1 timeleft:91 tix:100 )
Random 618369 -> Winning ticket 169 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:95 tix:100 )  (* job:1 timeleft:91 tix:100 )
Random 250506 -> Winning ticket 106 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:95 tix:100 )  (* job:1 timeleft:90 tix:100 )
Random 909747 -> Winning ticket 147 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:95 tix:100 )  (* job:1 timeleft:89 tix:100 )
Random 982786 -> Winning ticket 186 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:95 tix:100 )  (* job:1 timeleft:88 tix:100 )
Random 810218 -> Winning ticket 18 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:95 tix:100 )  (  job:1 timeleft:87 tix:100 )
Random 902166 -> Winning ticket 166 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:94 tix:100 )  (* job:1 timeleft:87 tix:100 )
Random 310147 -> Winning ticket 147 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:94 tix:100 )  (* job:1 timeleft:86 tix:100 )
Random 729832 -> Winning ticket 32 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:94 tix:100 )  (  job:1 timeleft:85 tix:100 )
Random 898839 -> Winning ticket 39 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:93 tix:100 )  (  job:1 timeleft:85 tix:100 )
Random 683984 -> Winning ticket 184 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:92 tix:100 )  (* job:1 timeleft:85 tix:100 )
Random 472143 -> Winning ticket 143 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:92 tix:100 )  (* job:1 timeleft:84 tix:100 )
Random 100701 -> Winning ticket 101 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:92 tix:100 )  (* job:1 timeleft:83 tix:100 )
Random 434172 -> Winning ticket 172 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:92 tix:100 )  (* job:1 timeleft:82 tix:100 )
Random 610887 -> Winning ticket 87 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:92 tix:100 )  (  job:1 timeleft:81 tix:100 )
Random 913011 -> Winning ticket 11 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:91 tix:100 )  (  job:1 timeleft:81 tix:100 )
Random 966607 -> Winning ticket 7 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:90 tix:100 )  (  job:1 timeleft:81 tix:100 )
Random 477010 -> Winning ticket 10 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:89 tix:100 )  (  job:1 timeleft:81 tix:100 )
Random 865310 -> Winning ticket 110 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:88 tix:100 )  (* job:1 timeleft:81 tix:100 )
Random 260492 -> Winning ticket 92 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:88 tix:100 )  (  job:1 timeleft:80 tix:100 )
Random 805028 -> Winning ticket 28 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:87 tix:100 )  (  job:1 timeleft:80 tix:100 )
Random 548699 -> Winning ticket 99 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:86 tix:100 )  (  job:1 timeleft:80 tix:100 )
Random 14041 -> Winning ticket 41 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:85 tix:100 )  (  job:1 timeleft:80 tix:100 )
Random 719705 -> Winning ticket 105 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:84 tix:100 )  (* job:1 timeleft:80 tix:100 )
Random 398823 -> Winning ticket 23 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:84 tix:100 )  (  job:1 timeleft:79 tix:100 )
Random 824845 -> Winning ticket 45 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:83 tix:100 )  (  job:1 timeleft:79 tix:100 )
Random 668153 -> Winning ticket 153 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:82 tix:100 )  (* job:1 timeleft:79 tix:100 )
Random 1142 -> Winning ticket 142 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:82 tix:100 )  (* job:1 timeleft:78 tix:100 )
Random 493578 -> Winning ticket 178 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:82 tix:100 )  (* job:1 timeleft:77 tix:100 )
Random 867603 -> Winning ticket 3 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:82 tix:100 )  (  job:1 timeleft:76 tix:100 )
Random 243911 -> Winning ticket 111 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:81 tix:100 )  (* job:1 timeleft:76 tix:100 )
Random 325204 -> Winning ticket 4 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:81 tix:100 )  (  job:1 timeleft:75 tix:100 )
Random 870472 -> Winning ticket 72 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:80 tix:100 )  (  job:1 timeleft:75 tix:100 )
Random 191067 -> Winning ticket 67 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:79 tix:100 )  (  job:1 timeleft:75 tix:100 )
Random 567511 -> Winning ticket 111 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:78 tix:100 )  (* job:1 timeleft:75 tix:100 )
Random 238616 -> Winning ticket 16 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:78 tix:100 )  (  job:1 timeleft:74 tix:100 )
Random 967541 -> Winning ticket 141 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:77 tix:100 )  (* job:1 timeleft:74 tix:100 )
Random 803180 -> Winning ticket 180 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:77 tix:100 )  (* job:1 timeleft:73 tix:100 )
Random 447970 -> Winning ticket 170 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:77 tix:100 )  (* job:1 timeleft:72 tix:100 )
Random 80445 -> Winning ticket 45 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:77 tix:100 )  (  job:1 timeleft:71 tix:100 )
Random 320054 -> Winning ticket 54 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:76 tix:100 )  (  job:1 timeleft:71 tix:100 )
Random 507941 -> Winning ticket 141 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:75 tix:100 )  (* job:1 timeleft:71 tix:100 )
Random 932834 -> Winning ticket 34 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:75 tix:100 )  (  job:1 timeleft:70 tix:100 )
Random 109057 -> Winning ticket 57 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:74 tix:100 )  (  job:1 timeleft:70 tix:100 )
Random 551267 -> Winning ticket 67 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:73 tix:100 )  (  job:1 timeleft:70 tix:100 )
Random 706562 -> Winning ticket 162 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:72 tix:100 )  (* job:1 timeleft:70 tix:100 )
Random 547441 -> Winning ticket 41 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:72 tix:100 )  (  job:1 timeleft:69 tix:100 )
Random 814467 -> Winning ticket 67 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:71 tix:100 )  (  job:1 timeleft:69 tix:100 )
Random 540284 -> Winning ticket 84 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:70 tix:100 )  (  job:1 timeleft:69 tix:100 )
Random 963839 -> Winning ticket 39 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:69 tix:100 )  (  job:1 timeleft:69 tix:100 )
Random 603186 -> Winning ticket 186 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:68 tix:100 )  (* job:1 timeleft:69 tix:100 )
Random 587617 -> Winning ticket 17 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:68 tix:100 )  (  job:1 timeleft:68 tix:100 )
Random 444989 -> Winning ticket 189 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:67 tix:100 )  (* job:1 timeleft:68 tix:100 )
Random 596287 -> Winning ticket 87 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:67 tix:100 )  (  job:1 timeleft:67 tix:100 )
Random 384901 -> Winning ticket 101 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:66 tix:100 )  (* job:1 timeleft:67 tix:100 )
Random 575651 -> Winning ticket 51 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:66 tix:100 )  (  job:1 timeleft:66 tix:100 )
Random 290329 -> Winning ticket 129 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:65 tix:100 )  (* job:1 timeleft:66 tix:100 )
Random 189391 -> Winning ticket 191 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:65 tix:100 )  (* job:1 timeleft:65 tix:100 )
Random 186729 -> Winning ticket 129 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:65 tix:100 )  (* job:1 timeleft:64 tix:100 )
Random 612773 -> Winning ticket 173 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:65 tix:100 )  (* job:1 timeleft:63 tix:100 )
Random 656660 -> Winning ticket 60 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:65 tix:100 )  (  job:1 timeleft:62 tix:100 )
Random 476531 -> Winning ticket 131 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:64 tix:100 )  (* job:1 timeleft:62 tix:100 )
Random 89824 -> Winning ticket 24 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:64 tix:100 )  (  job:1 timeleft:61 tix:100 )
Random 757604 -> Winning ticket 4 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:63 tix:100 )  (  job:1 timeleft:61 tix:100 )
Random 876771 -> Winning ticket 171 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:62 tix:100 )  (* job:1 timeleft:61 tix:100 )
Random 923381 -> Winning ticket 181 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:62 tix:100 )  (* job:1 timeleft:60 tix:100 )
Random 842461 -> Winning ticket 61 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:62 tix:100 )  (  job:1 timeleft:59 tix:100 )
Random 898174 -> Winning ticket 174 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:61 tix:100 )  (* job:1 timeleft:59 tix:100 )
Random 923083 -> Winning ticket 83 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:61 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 540600 -> Winning ticket 0 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:60 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 391296 -> Winning ticket 96 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:59 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 705284 -> Winning ticket 84 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:58 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 275634 -> Winning ticket 34 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:57 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 811629 -> Winning ticket 29 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:56 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 849486 -> Winning ticket 86 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:55 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 895039 -> Winning ticket 39 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:54 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 589801 -> Winning ticket 1 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:53 tix:100 )  (  job:1 timeleft:58 tix:100 )
Random 949765 -> Winning ticket 165 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:52 tix:100 )  (* job:1 timeleft:58 tix:100 )
Random 579695 -> Winning ticket 95 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:52 tix:100 )  (  job:1 timeleft:57 tix:100 )
Random 450563 -> Winning ticket 163 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:51 tix:100 )  (* job:1 timeleft:57 tix:100 )
Random 660246 -> Winning ticket 46 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:51 tix:100 )  (  job:1 timeleft:56 tix:100 )
Random 996258 -> Winning ticket 58 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:50 tix:100 )  (  job:1 timeleft:56 tix:100 )
Random 916942 -> Winning ticket 142 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:49 tix:100 )  (* job:1 timeleft:56 tix:100 )
Random 793325 -> Winning ticket 125 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:49 tix:100 )  (* job:1 timeleft:55 tix:100 )
Random 82373 -> Winning ticket 173 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:49 tix:100 )  (* job:1 timeleft:54 tix:100 )
Random 612783 -> Winning ticket 183 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:49 tix:100 )  (* job:1 timeleft:53 tix:100 )
Random 486444 -> Winning ticket 44 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:49 tix:100 )  (  job:1 timeleft:52 tix:100 )
Random 630147 -> Winning ticket 147 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:48 tix:100 )  (* job:1 timeleft:52 tix:100 )
Random 845078 -> Winning ticket 78 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:48 tix:100 )  (  job:1 timeleft:51 tix:100 )
Random 243035 -> Winning ticket 35 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:47 tix:100 )  (  job:1 timeleft:51 tix:100 )
Random 731489 -> Winning ticket 89 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:46 tix:100 )  (  job:1 timeleft:51 tix:100 )
Random 117134 -> Winning ticket 134 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:45 tix:100 )  (* job:1 timeleft:51 tix:100 )
Random 220460 -> Winning ticket 60 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:45 tix:100 )  (  job:1 timeleft:50 tix:100 )
Random 794583 -> Winning ticket 183 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:44 tix:100 )  (* job:1 timeleft:50 tix:100 )
Random 332536 -> Winning ticket 136 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:44 tix:100 )  (* job:1 timeleft:49 tix:100 )
Random 815913 -> Winning ticket 113 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:44 tix:100 )  (* job:1 timeleft:48 tix:100 )
Random 100607 -> Winning ticket 7 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:44 tix:100 )  (  job:1 timeleft:47 tix:100 )
Random 146358 -> Winning ticket 158 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:43 tix:100 )  (* job:1 timeleft:47 tix:100 )
Random 697671 -> Winning ticket 71 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:43 tix:100 )  (  job:1 timeleft:46 tix:100 )
Random 45234 -> Winning ticket 34 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:42 tix:100 )  (  job:1 timeleft:46 tix:100 )
Random 573866 -> Winning ticket 66 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:41 tix:100 )  (  job:1 timeleft:46 tix:100 )
Random 910016 -> Winning ticket 16 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:40 tix:100 )  (  job:1 timeleft:46 tix:100 )
Random 534198 -> Winning ticket 198 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:39 tix:100 )  (* job:1 timeleft:46 tix:100 )
Random 680589 -> Winning ticket 189 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:39 tix:100 )  (* job:1 timeleft:45 tix:100 )
Random 26696 -> Winning ticket 96 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:39 tix:100 )  (  job:1 timeleft:44 tix:100 )
Random 635000 -> Winning ticket 0 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:38 tix:100 )  (  job:1 timeleft:44 tix:100 )
Random 606339 -> Winning ticket 139 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:37 tix:100 )  (* job:1 timeleft:44 tix:100 )
Random 575953 -> Winning ticket 153 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:37 tix:100 )  (* job:1 timeleft:43 tix:100 )
Random 391209 -> Winning ticket 9 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:37 tix:100 )  (  job:1 timeleft:42 tix:100 )
Random 370140 -> Winning ticket 140 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:36 tix:100 )  (* job:1 timeleft:42 tix:100 )
Random 980517 -> Winning ticket 117 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:36 tix:100 )  (* job:1 timeleft:41 tix:100 )
Random 36392 -> Winning ticket 192 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:36 tix:100 )  (* job:1 timeleft:40 tix:100 )
Random 21636 -> Winning ticket 36 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:36 tix:100 )  (  job:1 timeleft:39 tix:100 )
Random 961032 -> Winning ticket 32 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:35 tix:100 )  (  job:1 timeleft:39 tix:100 )
Random 184972 -> Winning ticket 172 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:34 tix:100 )  (* job:1 timeleft:39 tix:100 )
Random 123895 -> Winning ticket 95 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:34 tix:100 )  (  job:1 timeleft:38 tix:100 )
Random 210576 -> Winning ticket 176 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:33 tix:100 )  (* job:1 timeleft:38 tix:100 )
Random 800747 -> Winning ticket 147 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:33 tix:100 )  (* job:1 timeleft:37 tix:100 )
Random 936970 -> Winning ticket 170 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:33 tix:100 )  (* job:1 timeleft:36 tix:100 )
Random 22782 -> Winning ticket 182 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:33 tix:100 )  (* job:1 timeleft:35 tix:100 )
Random 425619 -> Winning ticket 19 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:33 tix:100 )  (  job:1 timeleft:34 tix:100 )
Random 101500 -> Winning ticket 100 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:32 tix:100 )  (* job:1 timeleft:34 tix:100 )
Random 259920 -> Winning ticket 120 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:32 tix:100 )  (* job:1 timeleft:33 tix:100 )
Random 220829 -> Winning ticket 29 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:32 tix:100 )  (  job:1 timeleft:32 tix:100 )
Random 646926 -> Winning ticket 126 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:31 tix:100 )  (* job:1 timeleft:32 tix:100 )
Random 350294 -> Winning ticket 94 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:31 tix:100 )  (  job:1 timeleft:31 tix:100 )
Random 180318 -> Winning ticket 118 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:30 tix:100 )  (* job:1 timeleft:31 tix:100 )
Random 503637 -> Winning ticket 37 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:30 tix:100 )  (  job:1 timeleft:30 tix:100 )
Random 39378 -> Winning ticket 178 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:29 tix:100 )  (* job:1 timeleft:30 tix:100 )
Random 100921 -> Winning ticket 121 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:29 tix:100 )  (* job:1 timeleft:29 tix:100 )
Random 988236 -> Winning ticket 36 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:29 tix:100 )  (  job:1 timeleft:28 tix:100 )
Random 199355 -> Winning ticket 155 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:28 tix:100 )  (* job:1 timeleft:28 tix:100 )
Random 358555 -> Winning ticket 155 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:28 tix:100 )  (* job:1 timeleft:27 tix:100 )
Random 731599 -> Winning ticket 199 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:28 tix:100 )  (* job:1 timeleft:26 tix:100 )
Random 838327 -> Winning ticket 127 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:28 tix:100 )  (* job:1 timeleft:25 tix:100 )
Random 918482 -> Winning ticket 82 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:28 tix:100 )  (  job:1 timeleft:24 tix:100 )
Random 169424 -> Winning ticket 24 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:27 tix:100 )  (  job:1 timeleft:24 tix:100 )
Random 672641 -> Winning ticket 41 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:26 tix:100 )  (  job:1 timeleft:24 tix:100 )
Random 966549 -> Winning ticket 149 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:25 tix:100 )  (* job:1 timeleft:24 tix:100 )
Random 58051 -> Winning ticket 51 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:25 tix:100 )  (  job:1 timeleft:23 tix:100 )
Random 676202 -> Winning ticket 2 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:24 tix:100 )  (  job:1 timeleft:23 tix:100 )
Random 845425 -> Winning ticket 25 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:23 tix:100 )  (  job:1 timeleft:23 tix:100 )
Random 342312 -> Winning ticket 112 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:22 tix:100 )  (* job:1 timeleft:23 tix:100 )
Random 250687 -> Winning ticket 87 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:22 tix:100 )  (  job:1 timeleft:22 tix:100 )
Random 596791 -> Winning ticket 191 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:21 tix:100 )  (* job:1 timeleft:22 tix:100 )
Random 442314 -> Winning ticket 114 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:21 tix:100 )  (* job:1 timeleft:21 tix:100 )
Random 174819 -> Winning ticket 19 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:21 tix:100 )  (  job:1 timeleft:20 tix:100 )
Random 471625 -> Winning ticket 25 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:20 tix:100 )  (  job:1 timeleft:20 tix:100 )
Random 409905 -> Winning ticket 105 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:19 tix:100 )  (* job:1 timeleft:20 tix:100 )
Random 569113 -> Winning ticket 113 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:19 tix:100 )  (* job:1 timeleft:19 tix:100 )
Random 508600 -> Winning ticket 0 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:19 tix:100 )  (  job:1 timeleft:18 tix:100 )
Random 311446 -> Winning ticket 46 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:18 tix:100 )  (  job:1 timeleft:18 tix:100 )
Random 357152 -> Winning ticket 152 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:17 tix:100 )  (* job:1 timeleft:18 tix:100 )
Random 837662 -> Winning ticket 62 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:17 tix:100 )  (  job:1 timeleft:17 tix:100 )
Random 250932 -> Winning ticket 132 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:16 tix:100 )  (* job:1 timeleft:17 tix:100 )
Random 560600 -> Winning ticket 0 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:16 tix:100 )  (  job:1 timeleft:16 tix:100 )
Random 12436 -> Winning ticket 36 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:15 tix:100 )  (  job:1 timeleft:16 tix:100 )
Random 741575 -> Winning ticket 175 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:14 tix:100 )  (* job:1 timeleft:16 tix:100 )
Random 335916 -> Winning ticket 116 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:14 tix:100 )  (* job:1 timeleft:15 tix:100 )
Random 45696 -> Winning ticket 96 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:14 tix:100 )  (  job:1 timeleft:14 tix:100 )
Random 280883 -> Winning ticket 83 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:13 tix:100 )  (  job:1 timeleft:14 tix:100 )
Random 240130 -> Winning ticket 130 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:12 tix:100 )  (* job:1 timeleft:14 tix:100 )
Random 953130 -> Winning ticket 130 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:12 tix:100 )  (* job:1 timeleft:13 tix:100 )
Random 352225 -> Winning ticket 25 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:12 tix:100 )  (  job:1 timeleft:12 tix:100 )
Random 287878 -> Winning ticket 78 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:11 tix:100 )  (  job:1 timeleft:12 tix:100 )
Random 359201 -> Winning ticket 1 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:10 tix:100 )  (  job:1 timeleft:12 tix:100 )
Random 946906 -> Winning ticket 106 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:9 tix:100 )  (* job:1 timeleft:12 tix:100 )
Random 633748 -> Winning ticket 148 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:9 tix:100 )  (* job:1 timeleft:11 tix:100 )
Random 621077 -> Winning ticket 77 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:9 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 715620 -> Winning ticket 20 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:8 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 388017 -> Winning ticket 17 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:7 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 414418 -> Winning ticket 18 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:6 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 650833 -> Winning ticket 33 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:5 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 1524 -> Winning ticket 124 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:4 tix:100 )  (* job:1 timeleft:10 tix:100 )
Random 192309 -> Winning ticket 109 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:4 tix:100 )  (* job:1 timeleft:9 tix:100 )
Random 334402 -> Winning ticket 2 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:4 tix:100 )  (  job:1 timeleft:8 tix:100 )
Random 239416 -> Winning ticket 16 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:3 tix:100 )  (  job:1 timeleft:8 tix:100 )
Random 637400 -> Winning ticket 0 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:2 tix:100 )  (  job:1 timeleft:8 tix:100 )
Random 378648 -> Winning ticket 48 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:1 tix:100 )  (  job:1 timeleft:8 tix:100 )
--> JOB 0 DONE at time 192
Random 875424 -> Winning ticket 24 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:8 tix:100 )
Random 568151 -> Winning ticket 51 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:7 tix:100 )
Random 414406 -> Winning ticket 6 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:6 tix:100 )
Random 402267 -> Winning ticket 67 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:5 tix:100 )
Random 701830 -> Winning ticket 30 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:4 tix:100 )
Random 418226 -> Winning ticket 26 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:3 tix:100 )
Random 662196 -> Winning ticket 96 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:2 tix:100 )
Random 46779 -> Winning ticket 79 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:1 tix:100 )
--> JOB 1 DONE at time 200
```

### 4. Test fairness as the quantum size increases

Increase the **quantum** size to see how it affects fairness. For example, use quantum values of 10, 50, and 100.

`python lottery.py -l 100:100,100:100 -q 10 -c`

```
ARG jlist 100:100,100:100
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 10
ARG seed 0

Here is the job list, with the run time of each job:
  Job 0 ( length = 100, tickets = 100 )
  Job 1 ( length = 100, tickets = 100 )


** Solutions **

Random 844422 -> Winning ticket 22 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:100 tix:100 )  (  job:1 timeleft:100 tix:100 )
Random 757955 -> Winning ticket 155 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:90 tix:100 )  (* job:1 timeleft:100 tix:100 )
Random 420572 -> Winning ticket 172 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:90 tix:100 )  (* job:1 timeleft:90 tix:100 )
Random 258917 -> Winning ticket 117 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:90 tix:100 )  (* job:1 timeleft:80 tix:100 )
Random 511275 -> Winning ticket 75 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:90 tix:100 )  (  job:1 timeleft:70 tix:100 )
Random 404934 -> Winning ticket 134 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:80 tix:100 )  (* job:1 timeleft:70 tix:100 )
Random 783799 -> Winning ticket 199 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:80 tix:100 )  (* job:1 timeleft:60 tix:100 )
Random 303313 -> Winning ticket 113 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:80 tix:100 )  (* job:1 timeleft:50 tix:100 )
Random 476597 -> Winning ticket 197 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:80 tix:100 )  (* job:1 timeleft:40 tix:100 )
Random 583382 -> Winning ticket 182 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:80 tix:100 )  (* job:1 timeleft:30 tix:100 )
Random 908113 -> Winning ticket 113 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:80 tix:100 )  (* job:1 timeleft:20 tix:100 )
Random 504687 -> Winning ticket 87 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:80 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 281838 -> Winning ticket 38 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:70 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 755804 -> Winning ticket 4 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:60 tix:100 )  (  job:1 timeleft:10 tix:100 )
Random 618369 -> Winning ticket 169 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:50 tix:100 )  (* job:1 timeleft:10 tix:100 )
--> JOB 1 DONE at time 150
Random 250506 -> Winning ticket 6 (of 100) -> Run 0
  Jobs:
 (* job:0 timeleft:50 tix:100 )  (  job:1 timeleft:0 tix:--- )
Random 909747 -> Winning ticket 47 (of 100) -> Run 0
  Jobs:
 (* job:0 timeleft:40 tix:100 )  (  job:1 timeleft:0 tix:--- )
Random 982786 -> Winning ticket 86 (of 100) -> Run 0
  Jobs:
 (* job:0 timeleft:30 tix:100 )  (  job:1 timeleft:0 tix:--- )
Random 810218 -> Winning ticket 18 (of 100) -> Run 0
  Jobs:
 (* job:0 timeleft:20 tix:100 )  (  job:1 timeleft:0 tix:--- )
Random 902166 -> Winning ticket 66 (of 100) -> Run 0
  Jobs:
 (* job:0 timeleft:10 tix:100 )  (  job:1 timeleft:0 tix:--- )
--> JOB 0 DONE at time 200
```

`python lottery.py -l 100:100,100:100 -q 50 -c`

```
ARG jlist 100:100,100:100
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 50
ARG seed 0

Here is the job list, with the run time of each job:
  Job 0 ( length = 100, tickets = 100 )
  Job 1 ( length = 100, tickets = 100 )


** Solutions **

Random 844422 -> Winning ticket 22 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:100 tix:100 )  (  job:1 timeleft:100 tix:100 )
Random 757955 -> Winning ticket 155 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:50 tix:100 )  (* job:1 timeleft:100 tix:100 )
Random 420572 -> Winning ticket 172 (of 200) -> Run 1
  Jobs:
 (  job:0 timeleft:50 tix:100 )  (* job:1 timeleft:50 tix:100 )
--> JOB 1 DONE at time 150
Random 258917 -> Winning ticket 17 (of 100) -> Run 0
  Jobs:
 (* job:0 timeleft:50 tix:100 )  (  job:1 timeleft:0 tix:--- )
--> JOB 0 DONE at time 200
```

`python lottery.py -l 100:100,100:100 -q 100 -c`

```
ARG jlist 100:100,100:100
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 100
ARG seed 0

Here is the job list, with the run time of each job:
  Job 0 ( length = 100, tickets = 100 )
  Job 1 ( length = 100, tickets = 100 )


** Solutions **

Random 844422 -> Winning ticket 22 (of 200) -> Run 0
  Jobs:
 (* job:0 timeleft:100 tix:100 )  (  job:1 timeleft:100 tix:100 )
--> JOB 0 DONE at time 100
Random 757955 -> Winning ticket 55 (of 100) -> Run 1
  Jobs:
 (  job:0 timeleft:0 tix:--- )  (* job:1 timeleft:100 tix:100 )
--> JOB 1 DONE at time 200
```

### 5. Create a graph like in the chapter

Recreate the graph that visualizes fairness by running simulations with different parameters and plotting the results.
