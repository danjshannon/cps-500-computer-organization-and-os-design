# Computer Organization and Design | *The Hardware/Software Interface*
## Patterson and Hennessy
- [Home](/README.md)
- [Chapter 1 | *Computer Abstractions and Technology*](#Chapter-1--Computer-Abstractions-and-Technology)
- [Chapter 2 | *Instructions: Language of the computer*](#Chapter-2--Instructions-Language-of-the-computer)


# Chapter 1 | *Computer Abstractions and Technology*
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

### The Big Picture
> Today's computers are built on two key principles:
>   1. Instructions are represented as numbers.
>   2. Programs are stored in memory to be read or written; just like numbers;
> 
> These principles lead to the stored-program concept; its invention let the computing genie out of its bottle. Figure 2.7 shows the power of the concept specifically, memory can contain the source code for an editor program, the corresponding compiled machine code, the text that the compiled program is using, and even the compiler that generated the machine code.

<img src='storedProgramExample.png' title='Figure 2.7 Stored Program Example'>
<br>
<sup>Figure 2.7</sup>

### Vocab
>**instruction set** *The vocabulary of commands understood by a given* architecture.

>**stored-program concept** *The idea that instructions and data of many types can be stored in memory as numbers, leading to the stored program* computer.

>**word** *The natural unit of access in a computer, usually a group of 32 bits; corresponds to the size of a register in the MIPS architecture.*

>**data transfer instruction** *A command that moves data between memory and registers.*

>**address** *A value used to delineate the location of a specific data element within a memory array*

>**alignment restriction** *A requirement that data be aligned in memory on natural boundaries*

>**binary digit** *Also called a **binary bit**. One of the two numbers in base 2, 0 or 1, that are the components of information.*

>**least significant bit** *The rightmost bit in a MIPS word.*

>**most significant bit** *The leftmost bit in a MIPS word.*

>**instruction format**  *A form of representation of an instruction composed of fields of binary numbers*

>**machine language** *Binary representation used for communication with a computer system*

>**hexadecimal** *Numbers in base 16*

> **MIPS fields**
> - **op**: *Basic operation of the instruction, traditionally called the opcode*
> - **rs**: *The first register source operand*
> - **rt**: *The second register source operand*
> - **rd**: *The register destination operand. It gets the result of the operation*
> - **shamt**: *Shift amount*
> - **funct**: *Function. This field, often called the function code, selects the specific variant of the operation in the op field*

>**opcode** *The field that denotes the operation and format of an instruction*

### Notes

**Design Principals:**
1. *Simplicity favors regularity.*
2. *Smaller is faster.*
3. *Good design demands good compromises.*


