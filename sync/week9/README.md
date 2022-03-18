# Week 9 Memory Management
Virtual address is explicity supported by the processor (hardware) and is required.

## Virtual Memory
All pointers hold virtual addresssess!!!


## Physical Memory
- RAM is where data is actually stored at runtime?

- how do we convert form a virtual address to a physical address?
  1. Contiguous memory management
  - non-contiguous memory management
    2. Paging
    3. Segmentation

## Contiguous memory
[base, limit) for contiguous memory 

## Non-Contiguous Memory
### Pages and Segments
- Pages: address space is split into fixed size chunks. Programmer is not aware of details
- Segments: address space is split into variable sized chunks. Programmer has to decide where different variables go (which segment)


## hint hint wink wink

Question 9.5.2 probably on an exam

Given a 32-bit machine, 1kb page size, if each entry in the table takes 8 bytes, determin

1. How many bits for the offset (offset bits)?
2. How big is the page table