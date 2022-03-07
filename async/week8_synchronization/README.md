# Week 8 Synchronization

- [Home](/README.md#async-table-of-contents)
- [8.1 Readings](#81-readings)
- [8.2 Concurrency](#82-concurrency)
- [8.3 Synchronization](#83-synchronization)
- [8.4 Semaphores](#84-Semaphores)
- [8.5 Classical Semaphore Problems](#85-classical-semaphore-problems)
- [8.6 Monitors](#86-monitors)
- [8.7 Deadlocks](#87-deadlocks)

## Questions
- Examples of critical 
- does adding semaphores slow down parallelization?
  - what is the nuance between putting the semaphore inside the loop vs surrounding the loop?
- Producer consumer pseudo code - producer/consumer procedure vs function?

## 8.1 Readings
([top](#week-8-processes-and-threads))

*Oh*
[Chapter 4 | *Synchronization*](/readings/README.md#oh-Chapter-4--synchronization)

## 8.2 Concurrency
([top](#week-8-Synchronization))

### Shared Address Space
- Threads in the same process share memory address space.
- The OS can preempt the currently running thread at **ANY** time.
- What does this mean when updating shared memory?

#### Question
- What do you think the result of this program will be?

```java
import java.util.ArrayList;
import java.util.List;

class MyThreadExample extends Thread{
    private long id;
    public static int sum = 0;
    
    public MyThreadExample(int id){
        this.id=id;
    }

    public void run(){
        for(int i =0;i<10000;i++){
            sum+=id;
        }
    }

    public static void main(String[] args) throws InterruptedException
    {
        List<MyThreadExample> threads = new ArrayList<>();
        for (int i=1;i<=5;i++){
            threads.add(new MyThreadExample(i));
            threads.get(i-1).start();
        }
        for(MyThreadExample thread : threads){thread.joing();}
        System.out.println(MyThreadExample.sum);
    }
}
```

> At first the run() method will increment by 1, but by the end of the program, since this.id is shared across threads, run() will increment the loop by 5. We'll miss printing some numbers between 1 and 10000.

### Shared Memory
- **sum** is shared memory
- When threads write to sum, some qrites are done at the same time leading to overwriting values.
- how to solve this problem?
  - **synchronization**


### Critical sections
- **critical section** an area of code that accesses shared memory from concurrent programming (threads or processes)
- **race condition** when the output of a program is dependent upon the order in which its concurrent constituents are run (results in incorrect behavior)
- race conditions might be 1 in 10,000 and are notoriously hard to debug and solve.

## 8.3 Synchronization
([top](#week-8-Synchronization))


### Attempted Solutions
### Mutual Exclusion
- **Mutual exclusion** only one thread can enter a critical section at the same time
- solution myst be free from **deadlocks**
- **Deadlock** occurs when two or more processes/threads are waiting on each other in such a way that they will never wake up.

### Four conditions for mutual exclusion
1. No two processes are simultaneously in the corresponding critical section
2. No assumptions are made about speeds or numbers of CPUs available
3. No process running outside of a critical section may block another process that wants to enter a coreresponding critical section (or is in the critical section)
4. No process must wait forever to enter its critical section.


### Attempted Solutions: Interrupts
- **Solution 1** turn off interrupts (happens in HW) before you enter critical section; turn on interupts afterward
- interrupts are what allow the CPU to run something other than its current path of execution (current thread)
- By disabling interrupts, the code will be **atomic**. An atomic section of code (or code run automatically) will run without interruption
- what about long ciritical sections? What happens if the program halts in critical section? Or if divide-by-zero? Or is malicious?

- NO GOOD

### Attempted Solutions: SW Flag
- have a shared flag that is set to "0" when the critical section is empty and "1" when it is occupied

```
boolean global variable being_used = false;
void entry_contition() {
    while (being_used != false); // loop until 0
        being_used = true;       //
}
void exit_condition() {being_used = false;}
```

#### Question 
- Where can we insert an interrupt to cause incorret execution?
> after the while loop

### Test and Set
- An atomic operation (supported in instruction set and hardware)
  - atomic - can't split up
- Writes a 1 into a memory value and returns the previous value
- Used with busy waiting

```
enter_region:
  TSL REGISTER, LOCK  | copy lock to register and set lock to 1
  CMP REGISTER, #0    | was lock zero
  JNE enter_region    | if it was non zero, lock was set, so loop
  RET                 | return to caller, critical region entered

leave_region:
  MOVE LOCK, #0       | store a 0 in lock
  RET
```

## 8.4 Semaphores
([top](#week-8-Synchronization))

### Busy Waiting Issues
- Inefficient CPU usuage
- Priority inversion issues
- **Better Idea** instead of busy waiting for the critical section to become available, block the requesting process.

### Semaphore

```java
class Semaphore {
private:
    // Counter
    int value;
    // list of processes sleepin gin the semaphore
    std::vector<Process*> *queue;
public:
    // acquire lock
    void P();
    // release lock
    void V();
};
```


### Semaphore Implementation
``` java
void Semaphore::P() {
    disableInterrupts();
    value = value - 1;
    if (value < 0){
        // add the calling process to this semaphore's list; block this prcoess
    }
    enableInterrupts();
}

void Semaphore::V(){
    disableInterrupts();
    value = value + 1;
    if (value <= 0){
        //remove a process from the semaphore's list
        //wake up the removed process
    }
    enableInterrupts();
}
```

### Interrupts?

Didn't we say disabling interrupts were dangerous?
- yes
- *class semaphore exists only in the kernel*
- system call needed to invoke functions
- critically important disabling/enabling interrupts are handled correctly
- luckily this is done by OS designer, not application developer!
- Other implementations useing test and set

### semaphore usage

```
global s = new sempaphore(1);

object thread1{
    some code
    void run()
    non-critical section code
    s.P()
    critical section
    s.V()
    non-critical section code
}

object thread2{
    some code
    void run()
    non-critical section code
    s.P()
    critical section
    s.V()
    non-critical section code
}
```

### Mutex: Binary Semaphore
- a mutex is semaphore with a single count
- mutex is best for critical sections


## 8.5 Classical Semaphore Problems
([top](#week-8-Synchronization))

### Producer and Consumer
- Two types of workers: producer and consumer
- Producer generates data and writes it to a queue. If the queue is full, producer sleeps
- Consumer consumes data from the queue and sleeps if the queue is empty
- Fixed-length queue

### Solution
```C
mutex buffer_mutex;
semaphore fillCount = 0;
semaphore emptyCount = BUFFER_SIZE; //k

procedure producer(){
    while (true){
        down(fillCount);                 //s.P()
            down(buffer_mutex);
                putItemIntoBuffer(item); // critical section
            up(buffer_mutex);            // s.V()
        up(fillCount);                   //counting semaphore
    }
}

procedure consumer(){
    while (true){
        down(fillCount);
            down(buffer_mutex);                 // s.P()
                item = removeItemFromBuffer();  // critical section
            up(buffer_mutex);                   // s.V()
        up(emptyCount);
        consumeItem(item);                      // non critical
    }
}
```

### Dining Philosophers
- Philosophers eat/think
- Each needs two forks to eat.

```c
#define N;       // 5
#define LEFT;    // (i+N-1)%N
#define RIGHT;   // (i+1)%N
#define THINKING 0;
#define HUNGRY   1;
#define EATING   2;

typedef int semaphore;
int state[N];
semaphore mutex=1;
semaphore s[N];

void philosopher (int i){
    while (TRUE){
        think();
        take_forks(i);
        eat();
        put_forks(i);
    }
}

void take_forks(int i){
    down(&mutex);
    state[i]=HUNGRY;
    test(i);
    up(&mutex);
    down(&s[i]);
}

void put_forks(int i){
    down(&mutex);
    state[i]=THINKING;
    test(LEFT);
    test(RIGHT);
    up(&mutex);
}

void test(int i){
    if(state[i]==HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING){
        state[i]=EATING;
        up(&s[i]);
    }
}
```

## 8.6 Monitors
([top](#week-8-Synchronization))

### Problems with Semaphores

Semaphores and mutexes can be prone to errors
- Acquire and release must be put in the correct location; othewise, prgram can seize up.
- Very hard to debug if triggered on via a race condition

### Monitors
- monitors are a higher-level construct (ie part of a programming language)
- only one thread allowed in a monitor procedure at a time (image the methods are wrapped by `mutex.p()` and `mutex.v()`)
- **Condition variable** a queue of threads waiting for some condition to become true. Zero or more can be associated with a monitor.

### Condition Variable
- Within a monitor, calling **wait** on a conditional variable will cause the current thread to sleep on the condition variable. The thread releases the lock.

- When another thread calls **signal** on the conditional variable, one of the bocked threads is allowed to progress.
  - the thread calling signal must own the monitor lock.
  - **Boradcast** will unblock all of the blocked threads
  - Signal has no effect if no threads are blocked (ie no count variable associated with condtion variables)

### Producer Consumer with Monitors

```
monitor ProducerConsumer
    condition full, empty;
    integer count;
    procedure insert(item: integer);
    begin
        if count = N then wait(full);
        insert_item(item);
        count := count + 1;
        if count = 1 then signal(empty)
    end;
    function remove: integer,
    begin
        if count = 0 then wait(empty)
        remove = remove_item;
        count := count - 1;
        if count = N - 1 then signal(full)
    end;
    count := 0;
end monitor
```

```
procedure producer;
begin
    while true do
    begin
        item = produce_item;
        ProducerConsumer.insert(item)
    end
end;
procedure consumer;
begin
    while true do
    begin
        item = ProducerConsumer.remove;
        consume_item(item)
    end
end;
```

### Java Monitors
- Java supports monitors via synchronized **keywords**
- Synchronized methods within a class can be access by only **one thread per instance of the class** (not across all instances of the class)
- Synchronized statements, allow arbitrary sections of code to be sunchronized on any Java object.
- Java object class supports **wait** and **notify** (also **notifyall**)

## 8.7 Deadlocks
([top](#week-8-Synchronization))

- A deadlock occurs when multiple processes are waiting on each other, mutually blocking each other, and thus will never run
- The most common apporach to deadlocks is to do **nothing**
- However in a nuclear power plant, airplane control systems, and so on, ignoring deadlocks is not an option

### Deadlock Detection
- Allow deadlocks to happen, but detect it when it does
- Periodically check for deadlock state.
- Construct the wait-for graph, and kill one or more threads/processes that are deadlocked

### Deadlock Aoidance
- Before granting requests for locks, the operating system checks if granting that request would move the system into an **unsafe state**
- and unsafe state occurs when there is the possibility of deadlock
- *Dijkstra* developed the banker's algorithm to achieve deadlock avoidance

### Deadlock Prevention
- Through enforceable locking policy, prevent deadlocks from happening
- If all of the resources can be enumerated, on policy can ensure that they must be requested in that order.
  - a thread that holds resouce (eg lock) numbered `X` can only request resources `X > Y`

