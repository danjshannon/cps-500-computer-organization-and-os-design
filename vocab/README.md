## Vocab
- [Home](/README.md)

### Chapter 2

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

#### global pointer
> *The register that is reserved to point to the static area.*

#### procedure frame
> *Also called **activation record**. The segment of the stack containing a procedure's saved registers and local variables.*

#### frame pointer
> *A value denoting the location of the saved registers and loal variables for a given procedure*

#### text segment
> *The segment of a UNIX object file that contains the machine language code for routines in the source file*

#### PC-relative addressing (program counter)
> *An addressin regime in which the address is the sum of the program counter (PC) and a constant in the instruction.*

#### addressing mode
> *One of several addressing regimes delimited by their varied use of operands and/or addresses.*



### Chapter 3
#### Arithmetic Logic Unit (ALU)
> *Hardware that performs addition, subtraction, and usually logical operations such as AND and OR*

#### exception
> *Also caled **interupt**. An unscheduled event that disrupts program execution; used to detect overflow.*

#### interrupt
> *An exception that comes from outside of the processor. (Some architectures use the term interrupt for all exceptions.)

#### dividend
> *A number being divided*

#### divisor
> *a number that the dividend is divided by*

#### quotient
> *the primary result of a division; a number that when multiplied by the divisor and added to the raminder produces the dividend.*

#### remainder
> *the secondary result of a division; a number that when added to the product of the quotient and the divisor produces the dividend.*

