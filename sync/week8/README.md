# Week 8 Sync

## lab 4

use argset abstraction

user recursion to get argset

1. figure out how to start a single process
2. Run a command
3. then figure out how
  4. chdir chan't be forked


## Syncrhonization
- Monitors
  - *terrible name*

### Motivation for Monitors
- semaphores are a big step from low-level loads and stores
- however, semaphores are used for both mutual exclusion and synchronization
- Monitors separate these two concerns.'


### monitor defined
- monitor: a lock + conditional variables
- lock: provides mutual exclusion to shared data
- condition variable: provides a queue for waiting threads inside critical section

### LOcks
- `lock.acquire()`
  - wait until lock is free then grab it
- `lock.release()`
  - un lock wake up anyone waiting to acquire
- lock is initially free

- always acquire a lock before critical section
- always release the lock after critical section

```
addToQueue{
    lock.acquire();
    // push 1 item to queue
    condition.signal(); // does not go into effect until the lock is released
    lock.release();
}

removeFromQueue{
    lock.acquire()
    while nothing on queue // this is a standard check of some state
        condition.wait()
    item = // pop item from queue
    lock.release()
    return item
}
```

### Pthread mutexes
has an API

### Conditional variables
- lock and sleep in one action

> semaphores keep score 
*mark wess*

### spurious wakeup
place wait signal inside while loop


use `while` for spurious wakeup, not `if`!!

### multiple locks
> If you're going to acquire multuple locks in different threads, always acquire them in the same order and release them in the same reversed order.

```
//thread 1
lock m1
push random int to q1
signal c1
release m1


//thread 2
lock m1
lock m2
while q1 empty
  wait c1

pop from q1 -> square -> push to q2
signal c2

release 2
release 1

// thread 3
lock m2
while q2 empty
  wait c2

console pop q2
release m2

```
