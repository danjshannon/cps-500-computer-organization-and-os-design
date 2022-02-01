# Week 3: Flow
## Agenda
- conditionals
- loops
  - for
  - while
- functions
  - leaf
  - non-leaf

## Conditionals
- Jump is unconditional branch
  - Jump no matter what
- bne and beq are conditional branches
  - branch if (not) equal
  - Jump only if registers are equal or not equal
- slt and slti
  - set if less than

## Pseudo Instructions
- blt branch less than `blt r1 r2 label`
```
slt $at r1 r2
bne $at $0 label
```

- ble branch if less than or equal `ble reg1 reg2 label`
```

```

### Tricks Part 1
1. x&lt;y
2. x&le;y is equivalent to !(y&lt;x)
3. x&gt;y is equivalent to y&lt;x
4. x&ge;y is equivalent to !(x&lt;y)

### Tricks Part 2
a) slt $t

### example 1
```C
if (x>0){
    x+=2;
}else{
    x-=2;
}
```

```
      slt $t0, $zero, $s0
      bne $t0, $zero, if
      addi $s0, $s0, -2
      J exit
If:   addi $s0, $s0, 2
Exit: 
```

### Tips
- do not jump or branch to the very next instruction

```C
int z=0;
if(x<y){
    if(x>0){
        z++;
    }else{
        z--;
    }
}else{
    z=5;
}
//x is in $s0
//y is in $s1
//z is in $s2
```

```
        addi $s2 $0 0

        slt $at $s1 $s0   if(x <= y)
        beq $at $0 outer

        addi $s2 $0 5
       j exit

if:    slt $t0 $0 $s0
       beq $t0 $0 else
       addi $s2, $s2, 1
else:  addi $s2 $s2 -1
exit:  ...

```


### While Loop Example
```C
int x=N;
while(x>0){
    x--;
}
```
```
        add $s0, $0, $s1
w1:
        slt $t0, $0, $s0
        beq $r0 $s0 exit
        addi $s0 $s0 -1
        j w1
exit:   ...
```

### For loop example
```C
int x =0;
for (int y=0;y<5;++y){x++;}
```
```
      addi $s0 $0 0 
      addi $s1 $0 0
loop: slti $t0 $s1 5
      beq $t0 $0 exit
      addi $s0 $s0 1
      addi $s1 $s1 1
      j loop
exit: ...
```

```C
int x=0;
for (int i = 0;i<N;i++){
    for (int j = i;j<N;++j){
        x++;
    }
}
```

mine
```
      addi $s0 $0 0
      addi $s1 $0 0 
loop1: slti $t0 $s1 N
      beq $t0 $0 exit
      addi $s0 $s0 1
      addi $t1 $0 $t0
loop2: slti $t1 $s0 N
      addi $t1 $t1 1
      addi $s1 $s1 1
j loop2
j loop1
exit: ...
```

bills
```
      addi $s0 $0 0
      addi $s1 $0 0  #i is in s1
loop1: slti $t0 $s1 N
      beq $t0 $0 exit
      addi $s0 $s0 1
      add $t1 $0 $t0
loop2: slti $t1 $s0 N
      addi $t1 $t1 1
      addi $s1 $s1 1
j loop2
j loop1
exit: ...
```

Use `$t0` for intermediate steps when it is mapping to a high level variable.

## Functions
- New instructions
  - `jr <reg>`
    - jump to a value held in a register (address)
  - `jal label`
    - jump to the label and set `$ra` equal to the next line
- registers:
  - `$ra` holds the return address to jump back to when a function is complete.
  - `$a0 - $a3` holds parameters to functions
  - `$v0 - $v1` hold return values from function
  - `$sp` hold the current value of the stack pointer, Remember the stack grows downwards.

### Temporary vs Saved Registers
- MIPS calling convention
- saved register must have their value unchanged by function calls (callee's responsibility)
- temorary registers are not saved across function calls, caller must be cautious

- this has lead to general rule of thumb that variables should be saved to s-registers


### waht gets saved on the stack
1. `$s-registers` by conventions s-registers nee to be saved this apply to boeth leaf and non-leaf functions
2. `$ra-register` for non leaf functions, we nee to save/restore the $ra register since it will be over-written by any function calls in the scope of this function
3. `$a-register` for non leaf functions, we may need to save/restore these on the stack since they will be over-written by any function calls in the scope of this function

> a leaf function is a function that doesn't call any other function

### leaf example
```C
min(3,4)

int min(int x, int y){
    int z=x;
    if(y<x){
        z=y;
    }
    return z;
}
```
```
addi $a0, $0, 3
addi $a1, $s0, 4
jal min #use $v0

-----
#calleee save architecture
min:
addi $sp, $sp, -4 #make room for 4 bytes
sw $s0, 0($sp)
add $s0, $0, $a0
slt $t0, $a1, $a0
beq $t0, $0 end
add $s0 S0 Sa1 #z=y

end:
add $v0, $s0 $0
lw $s0 0($sp)
addi $sp $sp 4 ##
jr $ra

```

### non-leaf example
```C
int sum(int x ){
    if(x<=0)return 0;
    return x+sum(x-1);
}
```

```
sum:
```