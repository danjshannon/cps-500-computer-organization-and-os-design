# Week 7

## Lab 3

- a little more time for everyone on lab 3

### Learning Objectives

1. Difference between process and thread
2. strong understadning of processthread state and their transtiitions
3. difference between user threads and kernel threads (and hybrid threads)
4. System calls: `fork()`, `wait()`, `join()` 
5. **terms** context switches, multi-programming, interrupts, interrupt handling, trap, user-mode, kernel-mode, starvation, system calls (blocking vs non-blocking)
6. Scheduling: Batch: no human interaction interactive: require human interaction, graphical windows/ui based, PC applications, pre-emptive scheduling

### UNIX Process Management
- `fork()` starts a new process which is just a child copy of itself
- `exec()` starts a program
- `wait()` blocks the caller until some process exits, any pid.
  - `waitpid()` blocks until a specific process returns

### Pipes
- a simple, **unnamed** pipe provides a one-way flow of data between two process
- declared in parent and used with child
- other variations:
  - stream pipes
  - FIFOs
- `pipe()` returns array of 2 file descriptors (int)

### `pipe()`

``` C
#include <stduni.h>

int pipe(int pipefd[2])
```

### named pipes
- when generated, names pipes havea directory entry
- named pipes use a directory and outlive processes
- `mknod` or `mkfifo` commands

### redirecting standard I/O
- a process that communicates solely with another process doesn't use its standard i/o
- if process communicates with another process only via pipes, redirect standard I/O to the pipe ends
- functions: `dup()`, `dup2()`
  - file descriptor 1 `stdin`
  - file descriptor 2 `stdout`
  - file descriptor 3 `stderror`

```C
#include <unistd.h>
int dup(int fd)

int dup2(int fromFD, int toFD)

dup2(pipefd[1],1)
```


`readline` is good for reading shell