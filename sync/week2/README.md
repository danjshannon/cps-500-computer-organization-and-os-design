# Week 2

## Assembly Language
- Assembly language is a human readable representaion of processor level instructions
- Much lower level than C code
- Generally, very fine-grained instructions that do some arithmetic, logical operation, on operands and store the result somewhere.
- On MIPS, operands and distinations are typically registers
- Registers are a very fast type of storage that is part of the processor
  - Registers are named and numbered on MIPS

## example

```c
x = x + 5
```
```
addi $s0, $s0, 5
```

```
addi $s1 $s0

addi $t0 $s2 -5
add $s0 $s1 $t0

add $t0 $s1 $s2
sub $t1 $s3 $s0
add $s4 $t0 $t1

addi $t0 $s0 1
addi $t1 $s0 -5
add $s0 $t01 $t1
```

## Bitwise and Logical Instructions
Shift Left Logical (SLL)
Shift Right Logical (SRL)

```
sll $s1 $s2 A
```
meaning: `$s1`=`$s2`&#8810;A
equivalent to &times;2<sup>A</sup>
`sll $s1 $s2 A`

```
srl $s1 $s2 A
```
meaning: `$s1`=`$s2`&#8811;A
equivalent to &divide;2<sup>A</sup>
`srl $s1 $s2 A`

*it's a lot faster to use bitwise shift than multiply for powers*

## NOT?
How do we perform NOT?

use nor and $0

`NOR $s0, $s1, $0`

`1100 1110` sll `0111 0000`
`1100 1110` srl `0000 1110`

0000 0111
0001 1111
0000 0100

0000 0100
0001 1111
0001 1111

not 1010 0101 = 0101 1010

## MIPS has 32 Registers
**Question** If there are only 32 registers how can we have hundres of variables? (Thinking of an array of intergers that has length 100?)

**Answer** We only keep a subset of variables in registers, the rest is stored in memory until needed

**How?**
Who or what determins which subset of variables are in the register at any point in time?

**Solution** It's the compilers job to do register optimization
load word: from memory to register
`LW $s1, x($s2)`
`$s1 = Memory[$s2+X]`
Reads 4 bytes from memory

load byte: from memory to register
`LB $s1, x($s2)`
`$s1 = Memory[$s2+X]`
Reads 1 byte from memory

Store register (word) to memory
`SW $s1, x($s2)`
`Memory[$s2+X]=$s1`


**X has to be a constant!!**

```C
A[i] = x;
y = A[x];
```
`assume base address of a in in $s3 and x is in $s0 y is in $s1`
```
sll $t0, $s0, 2
add $t0, $t0, $s3
sw  $s1, 0($t0)
lw  $s1, 0($t0)
```

what is memory? You can should think of memory as a huge array:byte[N] memory;
N=2<sup>32</sup>

Memory addresses are just unsigned integers. Pointers are just unsigned integers.

```C
#include <stdio.h>

int global_data1 = 1001;
int global_data2 = 1002;

int main(void){
    int* pointer = &global_data1;    // get address of global variable 1
    printf("%d\n", *pointer);
    long int_value = (long)pointer;  // convert pointer to long
    int_value +=4;                   // add 4 to
    int* pointer1 = (int*)int_value;
    printf("%d\n",*pointer1);
}
```


```
1) A[0]=x;
sw $s0 0($s3)


2) z=A[5]+3;
lw $t0 20($s3)
addi $s2 $t0 3


3) A[z]=x+y
add $t0 $s0 $s1
sll $t1 $s2 2       # 4*z
add $t1 $t1 $s3     # @A + 4 * z
sw $t0 0($t1)


4) A[x]=z-(A[y]+3);
sll $t0 $s1 2
add $t0 $s3 $t0
lw $t0 0($t0)       # A[y]

addi $t0 $t0 3      # A[y]+3
sub $t0 $s2 $t2     # t0 = z - A[y] + 3

sll $t1 $s0 2
add $t1 $t1 $s3
sw $t0 0($t1)