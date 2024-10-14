# Overview

There are now two simulators related to this chapter. The first,
`fork.py`, is a simple tool to show what a process tree looks like
when processes are created and destroyed. Read more about it
[here](README_fork.md).

The second is a program, `generator.py`, that creates real C programs
that use `fork()`, `wait()`, and `exit()` to show how `fork` works in
running programs. Read more about it [here](README_generator.md).

## Homework (Simulation)

### Questions

1. Run `./fork.py -s 10` and see which actions are taken. Can you predict what the process tree looks like at each step? Use the `-c` flag to check your answers. Try some different random seeds (`-s`) or add more actions (`-a`) to get the hang of it.

`./fork.py -s 10 -c -a 5`

```
ARG seed 10
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```

2. One control the simulator gives you is the `fork_percentage`, controlled by the `-f` flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., `-a 100`) and vary the `fork_percentage` from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with `-c`.

`./fork.py -s 5 -a 100 -f 0.1 -c > 10_percent`

Output [file of 10%](10_percent_fork_output)

`./fork.py -s 5 -a 100 -f 0.9 -c > 90_percent`

Output [file of 90%](90_percent_fork_output)

3. Now, switch the output by using the `-t` flag (e.g., run `./fork.py -t`). Given a set of process trees, can you tell which actions were taken?

`./fork.py -t -c`

```
ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list
ARG show_tree True
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c forks d
                               a
                               ├── b
                               └── c
                                   └── d
Action: b forks e
                               a
                               ├── b
                               │   └── e
                               └── c
                                   └── d
Action: b EXITS
                               a
                               ├── c
                               │   └── d
                               └── e
```

4. One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: `./fork.py -A a+b,b+c,c+d,c+e,c-`. This example has process `a` create `b`, which in turn creates `c`, which then creates `d` and `e`. However, then, `c` exits. What do you think the process tree should look like after the exit? What if you use the `-R` flag? Learn more about what happens to orphaned processes on your own to add more context.

`./fork.py -A a+b,b+c,c+d,c+e,c- -c`

```
ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               ├── b
                               ├── d
                               └── e
```

`./fork.py -A a+b,b+c,c+d,c+e,c- -c -R`

```
ARG seed -1
ARG fork_percentage 0.7
ARG actions 5
ARG action_list a+b,b+c,c+d,c+e,c-
ARG show_tree False
ARG just_final False
ARG leaf_only False
ARG local_reparent True
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c forks d
                               a
                               └── b
                                   └── c
                                       └── d
Action: c forks e
                               a
                               └── b
                                   └── c
                                       ├── d
                                       └── e
Action: c EXITS
                               a
                               └── b
                                   ├── d
                                   └── e
```

5. One last flag to explore is the `-F` flag, which skips intermediate steps and only asks to fill in the final process tree. Run `./fork.py -F` and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.

`./fork.py -F -s 20 -a 20 -c`

```
ARG seed 20
ARG fork_percentage 0.7
ARG actions 20
ARG action_list
ARG show_tree False
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: b EXITS
Action: a forks c
Action: c forks d
Action: a forks e
Action: c EXITS
Action: a forks f
Action: d EXITS
Action: e forks g
Action: e EXITS
Action: f forks h
Action: a forks i
Action: h forks j
Action: i forks k
Action: a forks l
Action: j forks m
Action: f EXITS
Action: a forks n
Action: h forks o
Action: l forks p

                        Final Process Tree:
                               a
                               ├── g
                               ├── i
                               │   └── k
                               ├── l
                               │   └── p
                               ├── h
                               │   └── o
                               ├── j
                               ├── m
                               └── n
```

6. Finally, use both `-t` and `-F` together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.

`./fork.py -t -F -s 20 -a 20 -c`

```txt
ARG seed 20
ARG fork_percentage 0.7
ARG actions 20
ARG action_list
ARG show_tree True
ARG just_final True
ARG leaf_only False
ARG local_reparent False
ARG print_style fancy
ARG solve True

                           Process Tree:
                               a

Action: a forks b
Action: b EXITS
Action: a forks c
Action: c forks d
Action: a forks e
Action: c EXITS
Action: a forks f
Action: d EXITS
Action: e forks g
Action: e EXITS
Action: f forks h
Action: a forks i
Action: h forks j
Action: i forks k
Action: a forks l
Action: j forks m
Action: f EXITS
Action: a forks n
Action: h forks o
Action: l forks p

                        Final Process Tree:
                               a
                               ├── g
                               ├── i
                               │   └── k
                               ├── l
                               │   └── p
                               ├── h
                               │   └── o
                               ├── j
                               ├── m
                               └── n
```

## Homework (Code)

### Questions

1. Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

[Solution](1_homework.c)

Answer: the child process gets a copy of the parent's variables, but they are in separate memory spaces, so changes in one do not effect the other

2. Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

[Solution](2_homework.c)

Answer: the file descriptor is shared between the processes, but concurrent writes can result in unpredictable output due to race conditions

3. Write another program using `fork()`. The child process should print "hello"; the parent process should print "goodbye". You should try to ensure that the child process always prints first; can you do this _without_ calling `wait()` in the parent?

[Solution](3_homework.c)

Answer: Use `pipe()`, the child process writes a signal (any character) to the pipe to inform the parent process that it has finished printing. The parent process reads from the pipe. It will block (wait) until there is data to read from the pipe (i.e., until the child writes its signal)

4. Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do you think there are so many variants of the same basic call?

[Solution](4_homework.c)

Answer: The different variants of `exec()` exist to offer flexibility in how the program and arguments are specified and how environment variables are handled

- `l` variants: these take the arguments as a list of individual parameters
- `v` variants: these take the arguments as an array (vector)
- `p` variants: these search for the executable in the directories specified in the `PATH` environment variable
- `e` variants: these allow passing a custom environment (`envp`), separate from the parent process's environment

5. Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

[Solution](5_homework.c)

Answer: `wait()` returns the PID of the terminated child and fills a status variable with the child's exist status. Calling `wait()` in the child process has no effect (returns an error), as the child has no child processes

6. Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

[Solution](6_homework.c)

Answer: It is useful in cases where you need to control multiple child processes or when non-blocking behavior is needed

7. Write a program that creates a child process, and then in the child closes standard output (`STDOUT_FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

[Solution](7_homework.c)

Answer: when `STDOUT` is closed in the child process, any subsequent calls to `printf()` (or other functions that write to standard output) will have no visible effect, as the data will have nowhere to go

8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the `pipe()` system call.

[Solution](8_homework.c)

Answer: the program demonstrates inter-process communication using `pipe()` and `fork()`. The child process writes its output to the pipe, and the second child process reads from the pipe. This technique is commonly used to chain commands together in Linux systems, similar to using pipes (`|`) in the shell (e.g., `ls | wc -l`)
