# Week 6

## lab 3 tips
- set up an array of strings for the register number to string
```
0 $r1
1 $r2
2 $t1
3 $t2
4 ...
5
6
7
```

- Watch out for register order. sometimes the destination register is swapped depending on the instructoin type - R J or I

### Half way through the class
>now we're starting operating systems.

### Interrupts, Exceptions, and System Calls

- different variations of the same thing.
### Exception or Interrupt?
- Some harware platforms refer to both external and software exceptions as interrupts, MIPS reers to both as exceptions.

|Type of event|From where|MIPS terminology|
|:-:|:-:|:-:|
|IO device request|external|interrupt|
|Invoke the os from user program|internal|exception|
|Arithmetic overflow|internal|exception|
|Using an undefined instruction|internal|exception|
|Hardware malfunctions|either|exception or interrupt|


- what.
- In kernel mode, there are additional registers
- change the memory map register 
  - only available as kernel, never as user mode.
- (let's say) clock interrupt interrupts every 60 times per second.
  - context switch every 1/60 second
- When the OS boots, the first user program is called

### What happens During an exception?
- an exception occurs
- os trap
- saving the PC where the exception happens
  - are there better spots to switch than others
- save the operating system state
- run exceptions code
- resume the last instruction before it traps, or terminate the program

> the set of the registers saved with the PC is called the context.

### Exception Handling in MIPS
- Consider two types of exceptions
  - arithmetic overflow
  - undefined instruction
- First save the address of the offending instruction in **Exception Program Counter (EPC)**
  - > EPC only availabile in kernel mode
- Transfer contorl to the **operating system (OS)** to some sepcified addres
- OS provides some service
- OS can stop the program or restart the program using EPC

### OS Algorithm
- how does the OS know the cause of the exception?
  - MIPS uses a **status register (Cause Register)** that holds a field that indicates the reason for an exception
    - ONLY AVAILABLE FORM KERNEL space
  - Alternatively in **vectored interrupts**, the address to which control is transferred to is determined by the cause of the exception
  - In this case the OS knows what happened by virtue of where control is transferred to.
  - when the exception is not vectored a single entry point for all exceptions is used

### non- vectored exceptions
  - asingle entry point is **8000 0180<sub>hex</sub>**
  - the os id ecodeing the status ragister to find the cause
  - two regi

### MIPS Exception Mechanism
- the processor operates in 
  - user mode
  - kernel mode
- access to additional set of registers and to **user mode** restricted memory space available when the processor operates in **kernel mode**.

 > When an excpeption occurs, the memory map does not chage!
 - jumps to **8000 0180** - must be mapped into every virtual memory space.
 - can get to the 

 > need to map virtual memory to physical memory address.

 - MIPS architecutre uses co-processor

 ### Co-processor
 - contains registers useful for handling exceptions
 - not accessible in **user mode**
 - includes the status register, cause register, BadVaddr, and EPC (exception program counter)

### Saving registers
- as with any procedure, the exception handler must first save any register it may modify, and then respotre them before returning to the interrupted rpgoram.
- saving registers in memory poses a problem in MIPS. Addressing the moemry requires a register (base) to form an address
- this means that a register must be modified before any register can be saved!
- The MIPS register useage convention $26 $($k0) and $27 $(k1) fro the user of the interrupt handler.

### System Calls in MIPS
- system calls in MIPS are treated like another form of exception
- there is a special instruction SYSCALL in MIPS used to trigger an exception
- Why can't we just use a function call?
  - Exceptions also force system to go from user to kernel mode?

## Signal Handling
### Unix Signals
- a way for the OS to notify a process of an event/
- steps:
  - event gains attention of the OS
  - OS stops the application and sends it the signal
  - Signal handler (special function in application) executes to completion
  - applicaiton resumes where it left off

#### ommon signals
- ctrl-z: sigtstp
- ctrl-\: sigquit
- ctrl-c: sigint

### sending signals from application
- `raise (int signalNumber);`
  - commonds os to send signal of type signalNumber
  - not common
### signal handlers
- a proram can install its own handler for any type of signal
  - except:
    - sigkill
    - sigstop
  - example
    - `sighanlder_t signal(int signum, sighandler_t hanler);`
    - installs function handler to run when the prcoess receives signals of type `signum`

- > restarting the instruction after a syscall does not restart the C code.
- > only the offending assembly instruction is rerun