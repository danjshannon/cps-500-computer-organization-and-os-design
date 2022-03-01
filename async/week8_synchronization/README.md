# Week 8 Synchronization

- [Home](/README.md#async-table-of-contents)
- [8.1 Readings](#81-readings)
- [8.2 Concurrency](#82-concurrency)

## Questions
- 

## 8.1 Readings
([top](#week-8-processes-and-threads))

*Oh*
[Chapter 3 | *Synchronization*](/readings/README.md#oh-Chapter-3--synchronization)

## 8.2 Concurrency
([top](#week-8-concurrency))

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