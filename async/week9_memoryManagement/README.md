# Week 9 Memory Management

- [Home](/README.md#async-table-of-contents)
- [9.1 Readings](#91-readings)
- [9.2 Memory Management](#92-memory-management)
- [9.3 Contiguous Memory Allocation](#93-contiguous-memory-allocation)
- [9.4 Noncontiguous Memory Allocation](#94-noncontiguous-memory-allocation)
- [9.5 Page Table Alternatives](#95-page-table-alternatives)

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

## 9.4 Noncontiguous Memory Allocation
([top](#week-9-memory-management))

### Process Larger Than RAM?
- With contiguous memory, a program's address space must fit into RAM
- Can we load only part of a process's address space into RAM

### Overlays
- Overlays are commonly used in video games (think game stages, boards, etc)
- The application programmer must manually divide the program into multiple parts
- Each overlay must individually fit into RAM
- Overlays can start their virtual address space at 0 (and use base/limit pairs)
- Notice in game consoles, typicaly amount of RAM is non configurable
- Just OS and one game playing at a time

### Paging
- Overlays can be of variable size
- programmer must split up program
- programmer should know how large RAM is
- can we do better?

- **paging** split procress address space into equal fixed-size chunks (pages)
  - automatically done by the operating system
  - programmer doesn't need to know RAM size

- Assume we have a process of 35 MB (&gt;2<sup>25</sup>) and page size of 8 KB (2<sup>13</sup>), we need 2<sup>26</sup>/2<sup>13</sup>=2<sup>13</sup> (more than 8,000 pages)
- RAM must also be divided into page frames. 16GB RAM with 8KB pages will have 2<sup>34</sup>/2<sup>13</sup>=2<sup>21</sup> (~2 million pages)
- a page from any progress can go in any page frame in RAM


### How to Translate?
- Each PCG (process control block) will have a page table
- Pages that are not in memory will be kept in a special area on the hard disk called (swap)
- MMU has pointer to the memory address of the page Table for currently running process

### Virtual Address
- a virtual address is composed of two elements, the page number and an offeset (within the page)
- `virtual page number = |Virtual Address/Page Size|`
- `Offset = virtual address - virtual page number * page size`
- in 32-bit machine, addresses are 32 bits. If the page size is 8KB (2<sup>13</sup>), the last 13 bits are used for the offset. The remaining 19 bits are used for the page number.

### Full Translation
1. Convert the virtual address into a virtual page number and offset
2. Look up the virtual page number in the process's pages table to find the physical page number
3. The exact physical address is at:
   - `Physical Page Number x Page Size + Offset`

What happends at step 2, if we find that the page needed is in swap space (ie not in RAM


## 9.5 Page Table Alternatives
([top](#week-9-memory-management))

### Page Table (continued)
- How much memory does a page table itself take up?
- 32-bit machine, 8 KB (2<sup>13</sup>) page size, 2<sup>19</sup> pages
- If each entry in the table is 8 bytes, then 2<sup>3</sup> * 2<sup>19</sup> = 4MB
- 64-bit machine 16 KB (2<sup>14</sup>) page size, 2<sup>50</sup> * 2<sup>3</sup> = 2<sup>53</sup> = 8 TB

### Multilevel Page Table
- Two-tier page table
- we can avoid allocating second-tier tables if not in use (as stack and heap grow)
- second-tier page tables themselves can be a page

### Inverted Page Table
- 64-bit machine has virtual address space of 2<sup>64</sup>, 16EB (exibytes)
- Most physical RAM is still only about 8 GB (2<sup>33</sup>)
- Create a mapping from physical to virtual pages
- Maps from physical page number to process id, virtual page number
- 1 IPT per system (rather than process)


#### Question
Given a machine with:

- 64 bits.
- 4 GB RAM.
- Each inverted page table entry uses 16 bytes.
- 8 kb page size.

How big will the inverted page table be?

> 8MB 
`	(4GB = 2^32) / (8kb = 2^13) = 2^19 page frames * (16 bytes per IPT entry ) 2^4 bytes = 2^23 bytes = 8 MB`