# Overview: `fork.py`

The simulator `fork.py` is a simple tool to show what a process tree
looks like when processes are created and destroyed.

To run it, just:

```sh
prompt> ./fork.py
```

What you'll see then is a list of actions, such as whether a process
calls `fork` to create another process, or whether a process calls
`exit` to stop running.

Each process that is running can have multiple children (or
none). Every process, except the initial process (which we call `a`
here for simplicity), has a single parent. Thus, all processes are
related in a tree, rooted at the initial process. We will call this
tree the `Process Tree` and understanding what it looks like as
processes are created and destroyed is the point of this simple
homework.

# Simple Example

Here is a simple example:

```sh
prompt> ./fork.py -s 4

                           Process Tree:
                               a
Action: a forks b
Process Tree?
Action: a forks c
Process Tree?
Action: b forks d
Process Tree?
Action: d EXITS
Process Tree?
Action: a forks e
Process Tree?
```

From the output, you can see two things. First, on the right, is the
initial state of the system. As you can see, it contains one process,
`a`. Operating systems often create one or a few initial processes to
get things going; on Unix, for example, the initial process is called
`init` which spawns other processes as the system runs.

Second, on the left, you can see a series of `Action` listings, in
which various actions take place, and then a question is posed about
the state of the process tree is at that point.

To solve, and show all outputs, use the `-c` flag, as follows:

```sh
prompt> ./fork.py -s 4 -c                                                                       +100

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: b forks d
                               a
                               ├── b
                               │   └── d
                               └── c
Action: d EXITS
                               a
                               ├── b
                               └── c
Action: a forks e
                               a
                               ├── b
                               ├── c
                               └── e
prompt>
```

As you can see, the expected tree that results (shown left-to-right)
from a particular operation is shown now. After the first action, `a
forks b`, you see a very simple tree, with `a` shown as `b`'s
parent. After a few more forks, a call to `exit` is made by `d`, which
reduces the tree. Finally, `e` is created, and the final tree, with
`a` as parent of `b`, `c`, and `e` (which are considered "siblings"),
as the final state.

In a simplified mode, you can just test yourself by trying to write
down the final process tree, using the `-F` flag:

```sh
prompt> ./fork.py -s 4 -F
                           Process Tree:
                               a

Action: a forks b
Action: a forks c
Action: b forks d
Action: d EXITS
Action: a forks e

                        Final Process Tree?
```

Once again, you can use the `-c` flag to compute the answer and see if
you were right (in this case, you should be, because it's the same
problem!)

# Other Options

A number of other options exist with the `fork` simulator.

You can flip the question around with the `-t` flag, which allows you
to view process tree states and then guess what action must have taken
place.

You can use different random seeds (`-s` flag) or just don't specify
one to get different randomly generated sequences.

You can change what percent of actions are forks (vs exits) with
the `-f` flag.

You can specify specific fork and exit sequences with the `-A`
flag. For example, to have `a` fork `b`, `b` then fork `c`; `c`
exit, and finally, `a` fork `d`, just type (we show `-c` here to solve
the problem, too):

```sh
prompt> ./fork.py -A a+b,b+c,c-,a+d -c

                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: b forks c
                               a
                               └── b
                                   └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
```

You can only show the final output (and see if you can guess all the
intermediates to get there) with the `-F` flag.

Finally, you can change the printing style of the tree with the `-P`
flag.

### Questions

1. Run `./fork.py -s 10` and see which actions are taken. Can you predict what the process tree looks like at each step? Use the `-c` flag to check your answers. Try some different random seeds (`-s`) or add more actions (`-a`) to get the hang of it.

2. One control the simulator gives you is the `fork_percentage`, controlled by the `-f` flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., `-a 100`) and vary the `fork_percentage` from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with `-c`.

3. Now, switch the output by using the `-t` flag (e.g., run `./fork.py -t`). Given a set of process trees, can you tell which actions were taken?

4. One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: `./fork.py -A a+b,b+c,c+d,c+e,c-`. This example has process `a` create `b`, which in turn creates `c`, which then creates `d` and `e`. However, then, `c` exits. What do you think the process tree should look like after the exit? What if you use the `-R` flag? Learn more about what happens to orphaned processes on your own to add more context.

5. One last flag to explore is the `-F` flag, which skips intermediate steps and only asks to fill in the final process tree. Run `./fork.py -F` and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.

6. Finally, use both `-t` and `-F` together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.
