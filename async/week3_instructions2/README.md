# Week 3 Instructions
- [Home](/README.md)
- [3.1 Readings](#31-Readings)
- [2.2 The Information Revolution](#22-Operations-and-operands)

## 3.1 Readings
([top](#week-3-Instructions))

*Patterson and Hennesy*
[Chapter 2 | *Instructions: Language of the Computer*](/readings/README.md#Chapter-2--Instructions-Language-of-the-computer)

## 3.2 Conditional Operations
([top](#week-3-Instructions))


### Branch if (not) equal
- Branch to a labeled instruction if a condition is true
  - Otherwise, continue sequentially
- `beq rs, rt, L1 # branch if equal`
  - if (rs==rt) branch to instruction labeled L1
- `bne rs, rt, L1 # branch if not equal`
  - if (rs!=rt) branch to instruction labeled L1
- `j L1`
  - unconditional jump to instruction labeled L1

### Compiling IF statements

- C code;
```C
if (i == j) f = g + h;
else f = g - h;
// f, g, h in $s0, $s1, $s2
```

- Compiled MIPS code:
```
  bne $s3, $s4, Else
  add $s0, $s1, $s2
  j Exit
Else: sub $s0, $s1, $s2 # Else is serving as a label
Exit: ... # Exit is label
```
<img src="ifFlow.png">

Above compiled the `if` statement into `bne`. What if it were beq?
```
  beq $s3, $s4, If
  sub $s0, $s1, $s2 # swap if and else labels
  j Exit
If: add $s0, $s1, $s2
Exit: ...
```

#### Assuming x is in $s0 and y is in $s1, which answer correctly captures the semantics of the following C code?

```C
if (x > y) {
  y++;
} else {
  y--;
}
```

```
slt $t0, $s1, $s0 # t0 = 1 IFF y < x.
beq $t0, $00, else # If $t0 = 0 jump to else statement.
addi $s1, $s1, 1  # $t0 = 1 on this line, so y < x is true, increment y.
j end             # Needed to ensure we don't execute both if-body and else-body.
else:             # Else label.
addi $s1, $s1, -1 # Decrement y since y is not less than x.
end:              # Next line after if-statement.
```

### Compiling Loop Statements
- C code:
```C
while (save[i] == k) i += 1;
// i in $s3, k in $s5, address of save in $s6
```
- Compiled MIPS code
```
Loop: sll $t1, $s3, 2     # multiple 2*2 = 4, 
      add $t1, $t1, $s6   # position of i (the index i of save)
      lw $t0, 0($t1)      # copying out of array into register $t0
      bne $t0, $s5, Exit  # $t0 is save[i], $s5 is k. if save[i]!=k jump to exit
      addi $s3, $s3, 1    # increment i
      j Loop              # jump to loop (it's a loop)
Exit...
```

#### Assuming i is in $s0, which answer correctly captures the semantics of the following C code?

```C
while (i > 0) {
  i *= 2;
}
```

```
loop:            # A label to jump back to. 
slt $t0, $0, $s0 # $t0 = 1 IFF 0 < x.
beq $t0, $0, end # $t0 = 0 IFF 0 >= x (so exit loop).
sll $s0, $s0, 1  # Execute loop body (x *= 2).
j loop           # repeat loop.
end:             # # a label to jump to when loop is done.
```

### Basic Blocks
- A basic block is a sequence of instruction with
  - No embedded branched (except and end)
  - No branch targets (except at beginning)
- A compiler identifies basic blocks for optimization
- An advanced processor can accelerate execution of basic blocks

### More Conditional Operations
- Set result to 1 if a condition is true
  - Otherwise set to 0
- `slt`
```
slt rd, rs, rt #
```
```C
if (rs < rt) rt = 1;
else rt = 0;
```
- `slti`
```
slti rt, rs constant
```
```C
if (rs < constant) rt = 1;
else rt = 0;
```
- Use in combination with beq, bne
- "branch if less than"
```
slt $t0, $s1, $s2  # if ($s1 < $s2)
bne $t0, $0, L  # branch to L
```

### Branch instruction design
- why not blt, bge, and so on?
- Hardware for <, &ge;,..slower than =, <>
  - Combining with branch involves more work per instruction, requiring a slower clock
  - all instructions are penalized!
- beq and bne are the common case
- This is a good design compromise

### Signed vs Unsigned
- signed comparrison: `slt, slti`
- unisigned comparison: `sltu, sltui`
- example
```
$s0 = 1111 1111 1111 1111 1111 1111 1111 1111 = -1
$s1 = 0000 0000 0000 0000 0000 0000 0000 0001 = 1
```
```
slt $t0, $s0, $s1 # signed
```
- -1 &lt; +1 &rArr; $t0 = 1
```
sltu $t0, $s0, $s1 # unsigned
```
- +4,294,976,295 &lt; +1 &rArr; $t0 = 0
