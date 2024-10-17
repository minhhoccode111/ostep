# Overview

Welcome to multi.py, a rudimentary multi-CPU scheduling simulator. This
simulator has a number of features to play with, so pay attention! Or don't,
because you are lazy that way. But when that exam rolls around...

To run the simulator, all you have to do is type:

```sh
prompt> ./multi.py
```

This will then run the simulator with some random jobs.

Before we get into any such details, let's first examine the basics of such a
simulation.

In the default mode, there are one or more CPUs in the system (as specified
with the -n flag). Thus, to run with 4 CPUs in your simulation, type:

```sh
prompt> ./multi.py -n 4
```

Each CPU has a cache, which can hold important data from one or more running
processes. The size of each CPU cache is set by the -M flag. Thus, to make
each cache have a size of '100' on your 4-CPU system, run:

```sh
prompt> ./multi.py -n 4 -M 100
```

To run a simulation, you need some jobs to schedule. There are two ways to do
this. The first is to let the system create some jobs with random
characteristics for you (this is the default, i.e., if you specify nothing,
you get this); there are also some controls to control (somewhat) the nature
of randomly-generated jobs, described further below. The second is to specify
a list of jobs for the system to schedule precisely; this is also described in
more detail below.

Each job has two characteristics. The first is its 'run time' (how many time
units it will run for). The second is its 'working set size' (how much cache
space it needs to run efficiently). If you are generating jobs randomly, you
can control the range of these values by using the -R (maximum run-time flag)
and -W (maximum working-set-size flag); the random generator will then
generate values that are not bigger than those.

If you are specifying jobs by hand, you set each of these explicitly, using
the -L flag. For example, if you want to run two jobs, each with run-time of
100, but with different working-set-sizes of 50 and 150, respectively, you
would do something like this:

```sh
prompt> ./multi.py -n 4 -M 100 -L 1:100:50,2:100:150
```

Note that you assigned each job a name, '1' for the first job, and '2' for the
second. When jobs are auto-generated, names are assigned automatically (just
using numbers).

How effectively a job runs on a particular CPU depends on whether the cache of
that CPU currently holds the working set of the given job. If it doesn't, the
job runs slowly, which means that only 1 tick of its runtime is subtracted
from its remaining time left per each tick of the clock. This is the mode
where the cache is 'cold' for that job (i.e., it does not yet contain the
job's working set). However, if the job has run on the CPU previously for
'long enough', that CPU cache is now 'warm', and the job will execute more
quickly. How much more quickly, you ask? Well, this depends on the value of
the -r flag, which is the 'warmup rate'. Here, it is something like 2x by
default, but you can change it as needed.

How long does it take for a cache to warm up, you ask? Well, that is also set
by a flag, in this case, the -w flag, which sets the 'warmup time'. By
default, it is something like 10 time units. Thus, if a job runs for 10 time
units, the cache on that CPU becomes warm, and then the job starts running
faster. All of this, of course, is a gross approximation of how a real system
works, but that's the beauty of simulation, right?

So now we have CPUs, each with caches, and a way to specify jobs. What's left?
Aha, you say, the scheduling policy! And you are right. Way to go, diligent
homework-doing person!

The first (default) policy is simple: a centralized scheduling queue, with a
round-robin assignment of jobs to idle CPUs. The second is a per-CPU
scheduling queue approach (turned on with -p), in which jobs are assigned to
one of N scheduling queues (one per CPU); in this approach, an idle CPU will
(on occasion) peek into some other CPU's queue and steal a job, to improve
load balancing. How often this is done is set by a 'peek' interval (set by the
-P flag).

With this basic understanding in place, you should now be able to do the
homework, and study different approaches to scheduling. To see a full list of
options for this simulator, just type:

```sh
prompt> ./multi.py -h
Usage: multi.py [options]

Options:
Options:
  -h, --help            show this help message and exit
  -s SEED, --seed=SEED  the random seed
  -j JOB_NUM, --job_num=JOB_NUM
                        number of jobs in the system
  -R MAX_RUN, --max_run=MAX_RUN
                        max run time of random-gen jobs
  -W MAX_WSET, --max_wset=MAX_WSET
                        max working set of random-gen jobs
  -L JOB_LIST, --job_list=JOB_LIST
                        provide a comma-separated list of
                        job_name:run_time:working_set_size (e.g.,
                        a:10:100,b:10:50 means 2 jobs with run-times of 10,
                        the first (a) with working set size=100, second (b)
                        with working set size=50)
  -p, --per_cpu_queues  per-CPU scheduling queues (not one)
  -A AFFINITY, --affinity=AFFINITY
                        a list of jobs and which CPUs they can run on (e.g.,
                        a:0.1.2,b:0.1 allows job a to run on CPUs 0,1,2 but b
                        only on CPUs 0 and 1
  -n NUM_CPUS, --num_cpus=NUM_CPUS
                        number of CPUs
  -q TIME_SLICE, --quantum=TIME_SLICE
                        length of time slice
  -P PEEK_INTERVAL, --peek_interval=PEEK_INTERVAL
                        for per-cpu scheduling, how often to peek at other
                        schedule queue; 0 turns this off
  -w WARMUP_TIME, --warmup_time=WARMUP_TIME
                        time it takes to warm cache
  -r WARM_RATE, --warm_rate=WARM_RATE
                        how much faster to run with warm cache
  -M CACHE_SIZE, --cache_size=CACHE_SIZE
                        cache size
  -o, --rand_order      has CPUs get jobs in random order
  -t, --trace           enable basic tracing (show which jobs got scheduled)
  -T, --trace_time_left
                        trace time left for each job
  -C, --trace_cache     trace cache status (warm/cold) too
  -S, --trace_sched     trace scheduler state
  -c, --compute         compute answers for me
```

Probably the best to learn about are some of the tracing options (like -t, -T,
-C, and -S). Play around with these to see better what the scheduler and
system are doing.

## Homework (Simulation)

In this homework, we’ll use `multi.py` to simulate a multi-processor CPU scheduler, and learn about some of its details. Read the related README for more information about the simulator and its options.

### Questions

1. To start things off, let’s learn how to use the simulator to study how to build an effective multi-processor scheduler. The first simulation will run just one job, which has a run-time of 30, and a working-set size of 200. How long will it take to complete? Turn on the appropriate flag to see a final answer, and a trace of the job and how it is scheduled.

`./multi.py -n 1 -L a:30:200 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']


Finished time 30

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
```

2. Now increase the cache size so as to make the job’s working set fit into the cache. Can you predict how fast the job will run once it fits in cache? Check your answer by enabling the solve flag.

`./multi.py -n 1 -L a:30:200 -M 300 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 300
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']


Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]
```

3. One cool thing about `multi.py` is that you can see more detail about what is going on with different tracing flags. Run the same simulation as above, but this time enable time left tracing. This shows both the job that was scheduled on a CPU at each time step, as well as how much run-time that job has left after each tick. What do you notice about how that decreases?

`./multi.py -n 1 -L a:30:200 -M 300 -T -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 300
ARG random_order False
ARG trace False
ARG trace_time True
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']

   0   a [ 29]
   1   a [ 28]
   2   a [ 27]
   3   a [ 26]
   4   a [ 25]
   5   a [ 24]
   6   a [ 23]
   7   a [ 22]
   8   a [ 21]
   9   a [ 20]
----------------
  10   a [ 18]
  11   a [ 16]
  12   a [ 14]
  13   a [ 12]
  14   a [ 10]
  15   a [  8]
  16   a [  6]
  17   a [  4]
  18   a [  2]
  19   a [  0]

Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]
```

4. Now add tracing to show the status of each CPU cache for each job. For each job, each cache will either show a blank space (if the cache is cold for that job) or a 'w' (if the cache is warm for that job). At what point does the cache become warm for the job in this simple example? What happens as you change the warmup time parameter to lower or higher values than the default?

`./multi.py -n 1 -L a:30:200 -M 300 -C -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:30:200
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 300
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache True
ARG trace_sched False
ARG compute True

Job name:a run_time:30 working_set_size:200

Scheduler central queue: ['a']

   0   a cache[ ]
   1   a cache[ ]
   2   a cache[ ]
   3   a cache[ ]
   4   a cache[ ]
   5   a cache[ ]
   6   a cache[ ]
   7   a cache[ ]
   8   a cache[ ]
   9   a cache[w]
-------------------
  10   a cache[w]
  11   a cache[w]
  12   a cache[w]
  13   a cache[w]
  14   a cache[w]
  15   a cache[w]
  16   a cache[w]
  17   a cache[w]
  18   a cache[w]
  19   a cache[w]

Finished time 20

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 50.00 ]
```

5. At this point, you should have a good idea of how the simulator works for a single job running on a single CPU. But hey, isn’t this a multi-processor CPU scheduling chapter? So, let’s start working with multiple jobs. Specifically, run multiple jobs on a two-CPU system. Can you predict how long this will take, given a round-robin centralized scheduler? Dive down into details and see whether caches got warmed effectively for these jobs. What do you notice?

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:50,c:100:50
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:50
Job name:c run_time:100 working_set_size:50

Scheduler central queue: ['a', 'b', 'c']


Finished time 150

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
```

6. Now we’ll apply some explicit controls to study cache affinity, as described in the chapter. Restrict different jobs to specific CPUs and predict how fast this version will run. Why does it do better? Will other combinations of jobs on the processors run faster or slower?

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:50,c:100:50
ARG affinity a:0,b:1,c:1
ARG per_cpu_queues False
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:50
Job name:c run_time:100 working_set_size:50

Scheduler central queue: ['a', 'b', 'c']


Finished time 110

Per-CPU stats
  CPU 0  utilization 50.00 [ warm 40.91 ]
  CPU 1  utilization 100.00 [ warm 81.82 ]
```

7. One interesting aspect of caching multiprocessors is the opportunity for better-than-expected speedup of jobs when using multiple CPUs (and their caches) compared to running jobs on a single processor. Sometimes you can speed up by more than a factor of the number of CPUs, a situation called super-linear speedup. Experiment with different CPU and cache configurations. What do you notice about performance as the number of CPUs scales?

`./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -M 50 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:100,c:100:100
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 50
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:100
Job name:c run_time:100 working_set_size:100

Scheduler central queue: ['a', 'b', 'c']


Finished time 300

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
```

`./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -M 50 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:100,c:100:100
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 50
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:100
Job name:c run_time:100 working_set_size:100

Scheduler central queue: ['a', 'b', 'c']


Finished time 150

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
```

`./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 50 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:100,c:100:100
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 3
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 50
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:100
Job name:c run_time:100 working_set_size:100

Scheduler central queue: ['a', 'b', 'c']


Finished time 100

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
  CPU 2  utilization 100.00 [ warm 0.00 ]
```

8. Another aspect worth studying is the per-CPU scheduling option. Compare how this option works against manually controlled affinity limits. How does performance change as you alter the peek interval? How does this approach work as the number of CPUs scales?

`./multi.py -n 1 -L a:100:100,b:100:100,c:100:100 -M 100 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:100,c:100:100
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 1
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:100
Job name:c run_time:100 working_set_size:100

Scheduler central queue: ['a', 'b', 'c']


Finished time 300

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
```

`./multi.py -n 2 -L a:100:100,b:100:100,c:100:100 -M 100 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:100,c:100:100
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:100
Job name:c run_time:100 working_set_size:100

Scheduler central queue: ['a', 'b', 'c']


Finished time 150

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 0.00 ]
  CPU 1  utilization 100.00 [ warm 0.00 ]
```

`./multi.py -n 3 -L a:100:100,b:100:100,c:100:100 -M 100 -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:100,c:100:100
ARG affinity
ARG per_cpu_queues False
ARG num_cpus 3
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:100
Job name:c run_time:100 working_set_size:100

Scheduler central queue: ['a', 'b', 'c']


Finished time 55

Per-CPU stats
  CPU 0  utilization 100.00 [ warm 81.82 ]
  CPU 1  utilization 100.00 [ warm 81.82 ]
  CPU 2  utilization 100.00 [ warm 81.82 ]
```

9. Finally, feel free to generate random workloads and see if you can predict their performance on different numbers of processors, cache sizes, and scheduling options. If you do this, you’ll soon be a multi-processor scheduling master, which is a pretty awesome thing to be. Good luck!

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -p -c`

```
ARG seed 0
ARG job_num 3
ARG max_run 100
ARG max_wset 200
ARG job_list a:100:100,b:100:50,c:100:50
ARG affinity
ARG per_cpu_queues True
ARG num_cpus 2
ARG quantum 10
ARG peek_interval 30
ARG warmup_time 10
ARG cache_size 100
ARG random_order False
ARG trace False
ARG trace_time False
ARG trace_cache False
ARG trace_sched False
ARG compute True

Job name:a run_time:100 working_set_size:100
Job name:b run_time:100 working_set_size:50
Job name:c run_time:100 working_set_size:50

Scheduler CPU 0 queue: ['a', 'c']
Scheduler CPU 1 queue: ['b']


Finished time 100

Per-CPU stats
  CPU 0  utilization 95.00 [ warm 35.00 ]
  CPU 1  utilization 95.00 [ warm 75.00 ]
```
