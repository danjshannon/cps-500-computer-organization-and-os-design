# Week 2 Instructions 1
- [Home](/README.md#async-table-of-contents)
- [2.1 Readings](#21-Readings)
- [2.2 The Information Revolution](#22-Operations-and-operands)
- [2.3 Program Performance](#23-memory-operands)
- [2.4 Integer Representations](#24-integer-representations)
- [2.5 Instruction Representation](#25-instruction-representation)
- [2.6 Logical Operations](#26-logical-operations)

## 2.1 Readings
([top](#week-2-Instructions-1))

*Patterson and Hennesy*
[Chapter 2 | *Instructions: Language of the Computer*](/readings/README.md#Chapter-2--Instructions-Language-of-the-computer)

## 2.2 Operations and Operands
([top](#week-2-Instructions-1))

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

## 2.3 Memory Operands
([top](#week-2-Instructions-1))


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

#### Async Question 1
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

#### Async Question 2
> Which answer correctly translates the following C code in to MIPS: x = A[3] + x; (Assume x is in \$s0 and the base address of integer array A is in \$s1).

```
lw $t0, 12($s1)
add $s0, $s0, $t0
```

## 2.4 Integer Representations
([top](#week-2-Instructions-1))

### Unsigned Binary Integers
- Given an n-bit number
- Range: [0, &plus;2<sup>n</sup> &minus; 1]
- Example:
> base<sub>2</sub>: 0000 0000 0000 0000 0000 0000 0000 1011

> = 0 + ... + 1&times;2<sup>3</sup> + 0&times;2<sup>2</sup> + 1&times;2<sup>1</sup> + 1&times;2<sup>0</sup>

> = 0 + ... + 8 + 0 + 2 + 1

> base<sub>10</sub>: 11
- Using 32 bits:
  - 0 to &plus;4,294,697,295

### Two's Compliment Signed Integers
- bit 31 is sign bit
  - 1 for negative numbers
  - 0 for non-negative numbers
- -(-2<sup>n-1</sup>) can't be represented
- non-negative numbers have same unsigned and 2s-complement representation
- Given an n-bit number
- Range: [&minus;2<sup>n-1</sup>, &plus;2<sup>n-1</sup>&minus;1]

Example:
> base<sub>2</sub>: 1111 1111 1111 1111 1111 1111 1111 1100

> = &minus;1&times;2<sup>31</sup> &plus; 1&times;2<sup>30</sup> &plus; ... &plus; 1&times;2<sup>2</sup> &plus; 0&times;2<sup>1</sup> &plus; 1&times;2<sup>0</sup> &plus; 0&times;2<sup>0</sup>

> = &minus;2,147,483,648 &plus; 2,147,483,644

> base<sub>10</sub>: &minus;4
- Using 32 bits:
  - &minus;2,147,483,658 to &plus;2,147,483,647

- Some Specific Numbers:
  - 0: 0000 0000 ... 0000
  - &minus;1: 1111 1111 ... 1111
  - Most-negative: 1000 0000 ... 0000
  - Most-positive: 0111 1111 ... 1111
  - (the most negative number is one greater than the most positive number)

#### Async Question
> What is the following two's complement binary number in base 10: 10001011?
```
-1 * 2^7 = -128
+... 0
+1 * 2^3 = 8
+0 * 2^2 = 0
+1 * 2^1 = 2
+1 * 2^0 = 1
------------
-117
```

### Signed Negation
- Complement and add 1
- Complement means 1&rarr;0, 0&rarr;1
- Example: negate
  - &plus;2 = 0000 0000 ... 0010<sub>2</sub>
  - &minus;2 = 1111 1111 ... 1101<sub>2</sub> + 1 =  1111 1111 ... 1110<sub>2</sub>

### Sign Extension
- Representing a number using more bits
  - Preserve the numeric value
- In MIPS instruction set
  - addi: extend immediate value
  - lb, lh: extend loaded byte/halfword
  - beq, bne: extend the displacement

- Replicate the sign bit to the left
  - C.f. unsigned values, extend with 0s
- Examples: 8-bit to 16-bit
> &plus;2: 0000 0010 	&rArr; 0000 0000 0000 0000

> &minus;2: 1111 1110 &rArr; 1111 1111 1111 1110

#### Async Question
> What is the signed negation of the following binary number: 01001011?
```
compliment: 10110100
        +1: 10110101
```

## 2.5 Instruction Representation
([top](#week-2-Instructions-1))

- Instructions are encoded in binary
  - called machine code
- MIPS instructions
  - Encoded as 32-bit (4 bytes) instruction words
  - Small numbe rof formats encoding operation code (opcode), register numbers, and so on
  - Regularity!

### Representing Instructions
- Register numbers
- `$t0 - $t7` are registers 8-15
- `$t8 - $t9` are registers 24-25
- `$s0 - $s7` are registers 16-23

| Register | Variable |
|:---:|:---:|
|0|$zero|
|...|...|
|8|$t0|
|9|$t1|
|10|$t2|
|11|$t3|
|12|$t4|
|13|$t5|
|14|$t6|
|15|$t7|
|16|$s0|
|17|$s1|
|18|$s2|
|19|$s3|
|20|$s4|
|21|$s5|
|22|$s6|
|23|$s7|
|24|$t8|
|25|$t9|

### MIPS R-Format Instrcutions

|op|rs|rt|rd|shamt|funct|
|:---:|:---:|:---:|:---:|:---:|:---:|
|6 bits|5 bits|5 bits|5 bits|5 bits|6 bits|

- Instruction Fields
  - **op**: *operation code (opcode)*
  - **rs**: *first source register number*
  - **rt**: *second source register number*
  - **rd**: *destination register number*
  - **shamt**: *shift amount (00000 for now)*
  - **funct**: *function code (extends opcode)*

### R-Format Example

```
add $t0, $s1, $s2
```

| |op|rs|rt|rd|shamt|funct|
|:---|:---:|:---:|:---:|:---:|:---:|:---:|
|**assembly**|special|$s1|$s2|$t0|0|add|
|**register**|0|17|18|8|0|32|
|**machine**|000000|10001|10010|01000|00000|100000|

> 00000010001100100100000000100000<sub>2</sub> = 02324020<sub>16</sub>

### Hexadecimal
- Base 16
  - Compact representation of bit strings
  - 4 bits per hex digit

|h|b|h|b|h|b|h|b|
|---|---|---|---|---|---|---|---|
|**0**|0000|**4**|0100|**8**|1000|**c**|1100|
|**1**|0001|**5**|0101|**9**|1001|**d**|1101|
|**2**|0010|**6**|0110|**10**|1010|**e**|1110|
|**3**|0011|**7**|0111|**11**|1011|**f**|1111|

- Example
  - hex:    `eca8 6420`
  - binary: `1110 1100 1010 1000 0110 0100 0010 0000`

### MIPS I-Format Instructions
|op|rs|rt|constant or address|
|:---:|:---:|:---:|:---:|
|6 bits|5 bits|5 bits|16 bits|

- Immediate arithmetic and load/store instructions
  - rt: destination or source register number
  - Constant: &minus;2<sup>15</sup> to &plus;2<sup>15</sup>&minus;1
  - Address: offset added to base address in rs
- **Design principle 4**: *Good design demands good compromises*
  - Different formats complicate decoding but allow 32-bit instructions uniformly
  - Keep formats as similar as possible

## 2.6 Logical Operations
([top](#week-2-Instructions-1))
### Logical Operations
- Instructions for bitwise manipulation

|Operation|C|Java|MIPS|
|:---:|:---:|:---:|:---:|
|Shift left|<<|<<|sll|
|Shift rigth|>>|>>>|srl|
|Bitwise AND|&|&|and,andi|
|Bitwise OR| \| | \| | or, ori|
|Bitwise NOT| ~ | ~ | nor|

- Useful for extracting and inserting groups of bits in a word.

### SHIFT Operations
- **shamt** how many positions to shift
- **SLL** Shift Left Logical
  - shift left and fill with 0 bits
  - sll by i bits multiplies by 2i
- **SRL** Shift Right Logical
  - shift right and fill with 0 bits
  - srl by i bits divides by [2i] (unsigned only)
    - takes the floor (round down)

**sll**
> `...0x28...0101`
> 0&times;2<sup>4</sup> + 0&times;2<sup>3</sup> + 1&times;2<sup>2</sup> + 0&times;2<sup>1</sup> + 1&times;2<sup>0</sup>
> 0 + 0 + 4 + 0 + 1 = **5**
> `00101 sll 00001`
> `...0x28...1010`
> 1&times;2<sup>3</sup> + 0&times;2<sup>2</sup> + 1&times;2<sup>1</sup> + 0&times;2<sup>0</sup>
> 8 + 0 + 2 + 0 = **10**

**srl**
> `...0x28...0101`
> `0101 srl 0001`
> `0...0x28...010`
> 0 + 1&times;2<sup>1</sup> + 0
> 0 + 2 + 0 = **2**

### AND Operations
- useful to mask bits in a word
  - select some bits, clear others to 0
- a bit is 1 in the result if and only if it is 1 in both inputs

```
and $t0, $t1, $t2

$t2 0000 0000 0000 0000 0000 1101 1100 0000
$t1 0000 0000 0000 0000 0011 1100 0000 0000
$t0 0000 0000 0000 0000 0000 1100 0000 0000
```
```
0 and 0 = 0
0 and 1 = 0
1 and 0 = 0
1 and 1 = 1
```
### OR Operations
- useful to include bits in a word
  - set some bits to 1, leave others unchanged

```
or $t1, $t2, $t3

$t2 0000 0000 0000 0000 0000 1101 1100 0000
$t1 0000 0000 0000 0000 0011 1100 0000 0000
$t0 0000 0000 0000 0000 0011 1101 1100 0000
```
```
0 or 0 = 0
0 or 1 = 1
1 or 0 = 1
1 or 1 = 1
```

### NOT Operations
- Useful to invert bits in a word
  - change 0 to 1, and 1 to 0
- MIPS has a NOR 3-operand instruction
  - a NOR b == NOT (a or b)

```
nor $t0, $t1, $zero

$zero 0000 0000 0000 0000 0000 0000 0000 0000
$t1   0000 0000 0000 0000 0011 1100 0000 0000
$t0   1111 1111 1111 1111 1100 0011 1111 1111
```
```
0 nor 0 = 1
0 nor 1 = 0
1 nor 0 = 0
1 nor 1 = 0
```