# Week 4

> How do we pass more than 4 parameters to a procedure

- We can probably push more parameters on to the stack. Make the common case fast - most functions don't take more than 4 arguments.

## Arithmetic

### Addition

- Two's complement in coding means that the first 1 is negative

- The adder works exactly the same whether the numbes are two's complement or not
- don't need add AND subtraction, just adder with two's complement

### Subtraction

> for subtraction, the top number MUST BE greater than the bottom number when dealing with unsigned numbers.

```
 0010 1010 0111 1110
 1010 0010 1000 0010
+___________________
 1100 1101 0000 0000
```

```
 0010 1010 0111 1110
 1010 0010 1000 0010
-___________________
 1000 0111 1111 1100
```


### Add vs Addu
- so if it doesnt matter if the numbers are in two's complement or in unsigned why do we need both?
- They both produce the same results **BUT**
  - **add** will cause a trap (to the kernel (operating system)) when an overflow occures
    - checks for errpr
  - **addu** ignores overflows
- C/C++ compilers *only* use "addu" so no traps on the overflow

### Multiplication

> Mulitplication can take 2 orders of magnitude more cyclces than shifting, use shift when possible


### Division

> just like decimal division. Bring down bits until you run out of room ,then you have a rmeainer


#### These will probably be on the exam
through arithmetic
use mips greensheet
virtual data space

32bit mips cross compiler