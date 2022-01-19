# Week 2 Instructions

- [2.1 Readings](#21-Readings-top)
- [2.2 The Information Revolution](#22-Operations-and-operands-top)
- [2.3 Program Performance](#23-memory-operands-top)

## 2.1 Readings ([top](#week-2-Instructions))

*Patterson and Hennesy*
[Chapter 2 | *Instructions: Language of the Computer*](/readings/README.md#Chapter-2--Instructions-Language-of-the-computer)

## 2.2 Operations and Operands ([top](#week-2-Instructions))

### Instruction Set
- The repertoire of instructions of a compiler
- Different computers have different instructions
  - by with many aspects in common
- Early computers had very simple instruction sets
  - Simplified implementation
- Many modern computers also have simple sets

## The MIPS Instruction Set
- The MIPS Instruction Set
- Used as the example throughout the book
- Stanford MIPS commercialized by MIPS Technologies [https://mips.com](https://mips.com)
- Large share of embedded core market
- Applications in consumer electronics, network/storage equipments, cameras, printers, and so on
- Typical of many modern ISAs
- See MIPS Reference Data tear out-card, and appendixes B and E in the text book.

### Arithmetic Operations
- Add and subtract, three operands
  - Two sources and one destination
  - `Add a,b,c # a gets b+c`
  - `Operation {destination} {source 1} {source 2}`
- All arithmetic operations have this form
- Design principal 1: Simplicity Favors Regularity
  - Regularity makes implementation simpler
  - Simplicity enables higher performance at lower cost

### Arithmetic Example
C code:
```C
// int f, g, h, i, j;
f = (g + h) - (i + j);
```
Compiled MIPS code:
```mips
add t0, g, h # temp t0 = g + h
add t1, i, j # temp t1 = i + j
sub f, t0, t1 # f = t0 - t1
```

### Register Operands
- Arithmetic instructions use register operands
- MIPS has a 32 x 32-bit (4 bytes) register file
  - user for frequently accessed data
  - numbered 0 to 31
  - 32-bit data called a **word**
- Assembler names
  - `$t0, $t1, ..., $t9` for temporary values
  - `$s0, $s1, ..., $s7` for saved values
- Design Principle 2: Smaller is faster
  - C.f. main memory: millions of locations

### Register Operand Example
C code:
```c
f = (g+h) - (i+j)
// f, .., j in $s0, ..., $s4 registers
```
Compiled MIPS code:
```
add $t0, $s1, $s2
add $t1, $s3, $s4
sub $s0, $t0, $t1
```

## 2.3 Memory Operands ([top](#week-2-Instructions))


### Memory Operands
- Main Memory is used for composite data
  - arrays, structures, dynamic data
- To apply arithmetics operations
  - Load values from memory into registers
  - Store result from register to memory
- Memory is byte-addressed
  - Each address identifies an 8-bit byte
- Words are aligned in memory
  - Address must be a multiple of 4!
- MIPS is **Big Endian**
  - Most-significant byte at least address of a word
  - C.F. **Little Endian**: Least-significant byte at least address

`[Least Endian][][][][][][][Most Endian]`

### Memory Operand Example 1
- C code:
```C
g = h + A[8];
// g in $s1, base address of A in $s3
```
- Compiled MIPS code:
  - Index 8 requires offset of 32, $s3 is called the base register
  - 4 bytes per word (4 byte integer) &times; 8 index
```
lw $t0 32($s3)    # load word, temp register $t0 gets A[8]
add $s1, $s2, $t0 # add $s2 and $t0 and set to $s1
```

### Async Question 1
> Which answer correctly translates the following C code into MIPS: A[2] = A[1] + x? (Assume x is in \$s0, and the base address of integer array A is in \$s1.)

```
lw $t0, 4($s1)
add $t0, $t0, $s0
sw $t0, 8($s1)
```

> Integers are 4 bytes each, therefore the offset from the base address needs to be in multiples of 4. The 'add' instruction cannot reference memory and the offset(base) notation is only for use with load/store operations.

### Memory Operand Example 2
- C code:
```C
A[12] = h + A[8]; //h in $s2, base address of A in $s3
```
- Compiled MIPS code:
  - index 8 requires offset of 32, $s3 is called the base register
```
lw $t0, 32($s3)   # load word, temp reg $t0 gets A[8]
add $t0, $s2, $t0 # temp reg $t0 gets h + A[8]
sw $t0, 48($s3)   # store word
                  # store h + A[8] back into A[12]
```

### Registers vs. Memory
- Registers are faster to access than memory
  - (registers are right next to the CPU - can't get much faster)
- Operating on memory data requires loads and stores
  - More instructions to be executed
- Compiler must use registers for variables as much as possible
  - only spill to memory for less frequently used variables
    - *not everything starts in memory though
  - register optimization is important!

### Immediate Operands
- Constant data specified in an instruction
```
addi $s3, $s3, 4
```
- No subtract immediate instruction
  - just use a negative constant
```
addi $s2, $s1, -1
```

- Design principle 3: **Make the common case fast**
  - Small constants are common
  - immediate operand avoids a load instruction

### The constant zero
- MIPS register 0 ($zero) is the constant 0
  - cannot be overwritten
- Useful for common operations
  - e.g. move between registers
```
add $t2, $s1, $zero # move $s1 to $t2
```

### Async Question 2
> Which answer correctly translates the following C code in to MIPS: x = A[3] + x; (Assume x is in \$s0 and the base address of integer array A is in \$s1).

```
lw $t0, 12($s1)
add $s0, $s0, $t0
```

## 2.4 Integer Representations ([top](#week-2-Instructions))