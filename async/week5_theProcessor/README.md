# Week 5 The Processor
- [Home](/README.md#async-table-of-contents)
- [5.1 Readings](#51-readings)
- [5.2 The Processor](#52-the-processor)
- [5.3 Logical Design](#53-logical-design)
- [5.4 Building a Datapath](#54-building-a-datapath)

## Questions
- Why do we shift left by 2 on the branch instruction? Not clear.

## 5.1 Readings
([top](#week-5-the-processor))

*Patterson and Hennesy*
[Chapter 4 | *The Processor*](/readings/README.md#Chapter-4--the-processor)

## 5.2 The Processor
([top](#week-5-the-processor))

### MIPS Subset
- Hardware implementation for a subset of MIPS
  1. Memory references: Load/Store
  2. Arithmetic/Logical: `add`, `sub`, `AND`, `OR`, `slt`
  3. Branching: `beq`, `jump`
- Not all arithmetic instructions (no multiple divide, shift)
- No floating point math

### Instruction Execution Step
1. PC (program counter) &rarr; instruction memory, fetch instruction
   - PC holds the address of the instruction
2. Register numbers &rarr; register file, read registers
3. Depending on instruction class
   - use [ALU](/vocab/README.md/#Arithmetic-Logic-Unit) to calculate
     1. Arithmetic result
     2. Memory address for load/store
     3. Branch target address
4. Access data memory for load/store
5. PC &larr; target address or PC + 4
   - update pc

### MIPS Data Flow

<img src="MIPSDataFlow.png" title="MIPS Data Flow"/>

### With Control

<img src="MIPSDataFlowWithControl.png" title="MIPS Data Flow With Control"/>

## 5.3 Logical Design
([top](#week-5-the-processor))

### Logical Elements
- **Combinational Elements** Output depends only upon their current inputs
  - Examples: ALU, Adder, Mutliplexer
- **State (sequential) elements** Has an internal state that impacts its output
  - Examples: Instruction and data memory, registers
  - Has two inputs:
    - Data: value to be written
    - Clock: determines when data are written

### Clocking Methodology
- **Clocking methodology** Defines when read and writes can happen
  - If a value is read and written at the same time, result could be some mix of new and old (or either).
  - Makes hardware predictable
- **Edge-triggered clocking** Sequential elements are updated only on a clock edge (transition from low to high or vice versa)

### Sequential Elements
- Register: stores data in a circuit
  - uses a clock signal to determine when to update the stored value.
  - Edge-triggered: update when clock changes from 0 to 1

<img src="SequentialElements.png"  width=500/>

- Register with write control
  - Only updates on clock edge when write control input is 1
  - Used when stored value is required late

<img src="SequentialElementsRegisterWithControl.png"/>

### Clocking Methodology
- Combinational logic transforms data during clock cycles
  - between clock edges
  - input from state elements, output to state element
  - longest delay determine clock period

<img src="CombinationalLogic.png"  width=500/>

## 5.4 Building a Datapath
([top](#week-5-the-processor))

- Datapath
  - elements that process data and addresses in the CPU
    - Registers, ALUs, muxs, memories
  - how data moves around within the CPU

### Instruction Fetch

(common for all instructions)
<img src="instructionfetch.png" width=500 alt='common for all instructions' title='common for all instructions'/>

### R-Format Instructions
- read two register operands
- perform artihmetic/logical operation
- write register result

<img src='rformatInstructions.png' width=500>
- ALU zero output
  - 1 if ALU is zero
  - 0 if ALU is non-zero

### Load/Store Instructions
1. Read register operands
2. Calculate address using 16-bit offset
   - use ALU, but sign-extend offset
3. Load: reed memory and update register
4. Store: write register value to memory

<img src="loadStoreInstructions.png" width=500 title='load/store instructions' />

### Branch Instructions
1. Read register operands
2. Compare operands
   - Use ALU, subtract, and check zero output
3. Calculate target address
   - Sign-extend displacement
   - Shift left two places (word displacement)
   - Add to PC +4
     - Already caclulated by instruction fetch

<img src='BranchInstruction.png' width=500 title='branch instruction'/>

### Composing the Elements
- First-cut datapath does an instruction in one clock cycle
  - Each datapath element can do only one function at a time
  - Hence, we need separate instruction and memories
- use multiplexers where alternate data sources are used for different instructions

### R-Type/Load/Store Datapath

<img src="RTypeLoadStoreDatapath.png" title='R-type/load/store datapath' alt='R-type/load/store datapath'/>

### Full Datapath (Single-Cycle Datapath)
<img src='FullDatapath_SingleCycle.png' title='FullDatapath_SingleCycle' alt='FullDatapath_SingleCycle' />

#### Question
> What is the branch target address for the following instruction

```
# PC = 4012
bne $t1, $t2, 11
```
...
```
PC + 4 = 4016
11 in dec, extended by 32 bits = 0000 1011 in bi

shift left by 2
0010 1100 = 44

PC + 32 extenstion + shift left 4
4012 + 44 + 4

```