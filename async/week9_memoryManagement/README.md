# Week 9 Memory Management

- [Home](/README.md#async-table-of-contents)
- [9.1 Readings](#91-readings)
- [9.2 Memory Management](#92-memory-management)
- [9.3 Contiguous Memory Allocation](#93-contiguous-memory-allocation)

## Questions


## 9.1 Readings
([top](#week-9-memory-management))

*Oh*
[Chapter 3 | *Memory Management*](/readings/README.md#oh-Chapter-3--Memory-management)

## 9.2 Memory Management
([top](#week-9-memory-management))

### Why Memory Management?
- Data protection (between user processes, between user process and operating system)
- Run programs larger than our physical RAM
- Translate virtual memory to physical memory

### Heirarchy
- **CPU registers** Typically have 32 registers, each typically 1 word (usually 4 bytes)
- **L1 cache** 10s of KB
- **L2 cache** a few megabytes
- **Main memory (RAM)** GB/TB (10s ns currently)
- **Hard disk** GB to PB (10 ms currently)

### Locality of Reference
- **Spatial locality** Addresses near recently referenced memory locations will be used soon.
Example:
1. Arrays (contiguous memory), iterating over each index.
2. Program execution is often linear.

- **Temoral locality** Addresses referenced recently are likely to be referenced again soon.
Example:
1. Saving a vlue into a variable (to be read later)
2. For loop `for(int i = 0; i < x; i++)`, `i` and `x` will be used again soon.

#### Question
- What impact to C style `goto` statements have on localitly of reference?


## 9.3 Contiguous Memory Allocation
([top](#week-9-memory-management))

### Process Address Space
- We can't assume process is loaded into RAM starting at address 0
- Compiler does assume program starts at 0 (were should it assume the prcess would go into memory?)
- **Physical address**: Where a process's address space is loaded in RAM
- **Virtual address**: The linear address space that begins at 0 that the executable assembly is based on

### MMU: Memory Management Unit
- We need to convert virtual address to physical address

<img src='MemoryManagementUnity.png' width=500>

### Physical Memory
- The simplest solution: assign every process a start (base) and end (limit) pointer into RAM.
- CPU will have special base/limit registers to translate
- The virtual address goes linearly into this portion

### Memory Translation
- To convert we merely add the offset to the virtual address
- and we ensure the program is not accessing memory outside of its partition

```c
int Translate(int virtualAddr){
    int result = virtualAddr + startAddr;
    if (result > endAddr) {
        raise exception;
    }
    return result;
}
```

### Question
- What problems does this create?

### Two Problems with this approach
- Process memory cannot be bigger than RAM. Recall that process address space includes heap, static data, stack, and instructions
- The RAM will slowly become fragmented into many small noncontiguous gaps as processes terminate

### how to fix?
- Periodic memory compaction?
  - Extremely time-consuming
  - All user process will be blocked
  - Potentially copying over large amounts of memory

## Finding Free RAM
- To track memory, the OS must keep track of all free RAM
- Can keep a linked-list of start, end pairs of free RAM
- Sorted by start address to merge consecutive holes
- How to choose which block?

### Choosing a Free Ram Block
- **First Fit** first free RAM block from beginning of list that fits new program (might be too large_.
- **Next Fit** start off searching where the last search ended. Move evenly using RAM, rather than focussing on lower addresses.
- **Best Fit** smallest free RAM block that fits new program; need to search entire list.
- **Worst Fit** largest free RAM block that fits new program; need to search entire list.