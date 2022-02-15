# Week 5

## Quiz 1

### Instructoin in Coding
  - Remmber that in stored program computer, instructions are stored in memory (just like data)
  - Each instruction is fetched (according to the address specified in the PC), decoded, and executed by the CPU
  - The ISA defines the format of an instruction (syntax) and its meaning (semantics)
  - AND ISA will define a number of different instruction formats
  - each format has different fields
  - the OPCODE filed says the instruction does (eg ADD)
  - the OPERAND field(s) say where to find inputs and outputs of the instruction

### MIPS Encoding
- The nice thing about MIPS (and other RISC machines) is that is has very few instruction formats (basically just 3)
- All instructoins are the same size (32 bits=1 word)
- The formats are consisten with eachohter (IE the OPCODE field is always in the same plae)

1. i type add
2. r type register
3. j type jump

### i type (immediate) format
- and immediate instruction has the form:
> `XXXI rt, rs, immed`

- recall that we have 32 registers, so we need ??? (5) bits each to specify the rt and rs registers
- we allow 6 bits for the opcode (this implies a maximum of ??? opcodes, but there are actually more)
- this leaves 16 bits for the immediate field

|opc|rs|rt|immed|
|-|-|-|-|
|31-26|25-21|20-16|15-0|

`ADDI $a0, $12, 33  # a0<-r12 +3`

|opc|rs|rt|immed|
|-|-|-|-|
|8|12|4|33|
|31-26|25-21|20-16|15-0|

- count over to the rt
- shift right
- shift left
- count from the right (31-left register boundary)

- preconstruct a bunch of 
- c macro  #define

|||||
|-|-|-|-|
|||||

### r type (register) format
- bits 31-26 are always 0 (how you know it's r type)


> use breakout session for lab3