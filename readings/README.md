# Computer Organization and Design | *The Hardware/Software Interface*
## Patterson and Hennessy
- [Home](/README.md)
- [Vocab](#vocab)
- [Chapter 1 | *Computer Abstractions and Technology*](#Chapter-1--Computer-Abstractions-and-Technology)
- [Chapter 2 | *Instructions: Language of the computer*](#Chapter-2--Instructions-Language-of-the-computer)


# Chapter 1 | *Computer Abstractions and Technology*
([top](#Computer-Organization-and-Design--The-HardwareSoftware-Interface))
## The Big Picture
> The five classic components of a computer are input, output, memory, datapath, and control, with the last two sometimes combined and called the processor.


> Both hardware and software consist of hierarchical layers using abstraction, with each lower layer hiding details from the level above. One key interface between the levels of abstraction is the *instruction set architecture* - the interface between the hardware and low-level software. This abstract interface enables many *implementations* of varying cost and perfomance to run identical software.

> Always bear in mind that the only complete and reliable measure of computer performance is time. Figure 1.15 shows the basic measurements at different levels in the computer and what is being measured in each case. We can see how these factors are combined to yield execution time measured in seconds per program:
```
Time = Seconds/Program = Instructions/Program X ClockCycles/Instruction X Seconds/clockCycle
```
| Components of Performance | Units of Measure |
|---|---|
|CPU Execution time for a program|Seconds for the program|
|Instruction Count|Instructions executed for the program|
|Clock cycles per instruction (CPI)|Average number of clock cylces per instruction|
|Clock cycle time|Seconds per clock cycle|
<sup>Figure 1.15</sup>

> Execution time is the only valid and unimpeachable measure of performance. Many other metrics have been proposed and found wanting. Sometimes these metrics are flawed from the start by not relfecting execution time; other times a metric that is valid in a limited context is extended and used beyond that context or without the additional clarification needed to make it valid.

# Chapter 2 | *Instructions: Language of the Computer*
([top](#Computer-Organization-and-Design--The-HardwareSoftware-Interface))
### The Big Picture
> Today's computers are built on two key principles:
>   1. Instructions are represented as numbers.
>   2. Programs are stored in memory to be read or written; just like numbers;
> 
> These principles lead to the stored-program concept; its invention let the computing genie out of its bottle. Figure 2.7 shows the power of the concept specifically, memory can contain the source code for an editor program, the corresponding compiled machine code, the text that the compiled program is using, and even the compiler that generated the machine code.

<img src='storedProgramExample.png' title='Figure 2.7 Stored Program Example'>
<br>
<sup>Figure 2.7</sup>

### Notes

#### Design Principals
1. *Simplicity favors regularity.*
2. *Smaller is faster.*
3. *Good design demands good compromises.*

#### Bounds Check Shortcut
> Use this shortcut to reduce an index-out-of-bounds check; jumpp to IndexOutOfBounds if $s1 &ge; $t2 or if $s1 is negative
```
sltu $t0, $s1, $t2 # $t0 = 0 if $s1>=length or $s1<0
beq $t0, $zero, IndexOutOfBounds #if bad, goto Error label
```

## Vocab
([top](#Computer-Organization-and-Design--The-HardwareSoftware-Interface))
#### instruction set
> *The vocabulary of commands understood by a given architecture.*

#### stored-program concept
> *The idea that instructions and data of many types can be stored in memory as numbers, leading to the stored program* computer.

#### word
> *The natural unit of access in a computer, usually a group of 32 bits; corresponds to the size of a register in the MIPS architecture.*

#### data transfer instruction
> *A command that moves data between memory and registers.*

#### address
> *A value used to delineate the location of a specific data element within a memory array*

#### alignment restriction
> *A requirement that data be aligned in memory on natural boundaries*

#### binary digit
> *Also called a **binary bit**. One of the two numbers in base 2, 0 or 1, that are the components of information.*

#### least significant bit
> *The rightmost bit in a MIPS word.*

#### most significant bit
> *The leftmost bit in a MIPS word.*

#### instruction format
> *A form of representation of an instruction composed of fields of binary numbers*

#### machine language
> *Binary representation used for communication with a computer system*

#### hexadecimal
> *Numbers in base 16*

#### MIPS fields
> #### op
> *Basic operation of the instruction, traditionally called the opcode*
> #### rs
> *The first register source operand*
> #### rt
> The second register source operand*
> #### rd
> *The register destination operand. It gets the result of the operation*
> #### shamt
> *Shift amount*
> #### funct
> *Function. This field, often called the function code, selects the specific variant of the operation in the op field*

#### opcode
> *The field that denotes the operation and format of an instruction*

#### AND
> *A logical bit-by-bit operation with two operands that calculates a 1 only if there is a 1 in both operands*

#### OR
> *A logical bit-by-bit operation with two operands that calculates a 1 if there is a 1 in either operand.*

#### NOT
> *A logical bit-by-bit operation with one operand that inverts the bits; that is, it replaces every 1 with a 0, and every 0 with a 1.*

#### NOR
> *A logical bit-by-bit operation with two operands that calculates the NOT of the OR of the two operands. That is, it calculates a 1 only if there is a 0 in both operands*

#### conditional branch
> *An instruction that requires the comparison of two values and that allows for a subsequent transfer of control to a new address in the program based on the outcome of the comparison.

#### basic block
> *A sequence of instructions without branches (except possibly at the end) and without branch targets or branch labels (except possibly at the beginning).*

#### jump address table
> *Also called **jump table**. A table of addresses of alternative instruction sequences*

#### procedure
> *A stored subroutine that performs a specific task based on the parameters with which it is provided* Procedures are one way to implement abstraction in software.

#### jump-and-link instruction
> *An instruction that jumps to an address and simultaneously saves the address of the following instructions in a register ($ra in MIPS)*

#### return address
> *A link to the calling site that allows a procedure to return to the proper address; in MIPS it is stored in register $ra.*

#### caller
> *The program that instigates a procedure and provides the necessary paremeter values.*

#### callee
> *A procedure that executes a series of stored instructions based on parameters provided by the caller and then returns control to the caller*

#### program counter (PC)
> *The register containing the address of the instruction the program being executed* A more sensible name would have been *instruction address register.*

#### stack
> *A data structure for spilling registers organized as last-in-firs-out queue.*

#### stack pointer
> *A value denoting the most recently allocated address in a stack that shows where registers should be spilled or where old register values can be found.* In MIPS, it is register $sp.

#### push
> *Add element to stack*

#### pop
> *Remove element from stack*

