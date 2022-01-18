# Week 1 Notes
## Agenda
- Welcome!
- Syllabus review
- Academic integrity policy
- c primer
- code

- Homework sometimes
- 4 labs, 1 extra credit
  - 5 total

## Compilers
- take high-level language and generate executable code.
- compilers generate executable code for specific architectures and operating systems
  - the same program compiled for a mac won't work on a windows machine
  - code compiled for an x86 architecture won't run on ARM
- Compilers generate a large portion of processes **virtual address space**
- Compiers are intricately linked with assigning variables an address. Variables go into three different locations:
  - **Data** static or global variables
  - **Stack** variables instantiated within a function without the new/malloc operator
  - **Heap** variables instantiated using the new/malloc operator


### Compiler Generated
- TEXT Segment
  1. Read only
  2. Size doesn't change
  3. Contains your executable machine instructions
  4. Can be shared if running multiple lines
- RODAata