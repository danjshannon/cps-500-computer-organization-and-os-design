# Week 1 Introduction

## 1.1 Readings
- Patterson and Hennesy
  - [Chapter 1 | *Computer Abstractions and Technology*](/readings/README.md#Chapter-1--Computer-Abstractions-and-Technology)
## 1.2 The Information Revolution
1. **Agricultural Revolution** 10,000 B.C.
2. **Industrial Revolution** 18<sup>th</sup> century
3. **Information Revolution** (20<sup>th</sup> and 21<sup>st</sup> century)

### Classes of Computers
- Personal Computers
  - General Purpose, variety of software
  - Subject to cost/performance trade-fss
- Server computers
  - Network-based
  - high cpacity, perfomance, reliability
  - Small to building-sized
- Super computers
  - High-end scientific and engineering calculations
  - small fraction of market
- Embedded computers
  - Hidden as components of systemms
  - Tight power/performance constraints

*Are smart phones personal computers or super computers? Or are they server computers*

### Post-PC Era
- Perosonal mobile devices (smartphone, tables, etc)
  - battery-operated
  - connects to internet
  - cheap (100s of dollars)
- Cloud computing
  - Warehouse-scale computing
  - Software sa a Service (SaaS)
  - Portion of software runs on PMD, portion runs in the cloud
  - Amazon and Google

### Moore's Law
- Progress in computing technology is underpinned by Moore's law
- **Moore's law**: number of transistors double every two years (or 18 months)
  - (the speed of the processor)
- Attributed to Gordon Moore, cofounder of Intel, in 1965
- Lasted until about 2012, now about 2.5 years, should last until late 2017 at the 10 nm scale.

|Decimal Term|Abbreviation|Value|Binary Term|Abbreviation|Value|% Larger|
|---|---|---|---|---|---|---|
|kilobyte|KB|10<sup>3</sup>|kibibyte|KiB|2<sup>10</sup>|2%|
|megabyte|MB|10<sup>6</sup>|mebibyte|MiB|2<sup>20</sup>|5%|
|gigabyte|GB|10<sup>9</sup>|gibibyte|GiB|2<sup>30</sup>|7%|
|terabyte|TB|10<sup>12</sup>|tebibyte|TiB|2<sup>40</sup>|10%|
|petabyte|PB|10<sup>15</sup>|pebibyte|PiB|2<sup>50</sup>|13%|
|exabyte|PB|10<sup>18</sup>|exibibyte|EiB|2<sup>60</sup>|15%|
|zettabyte|ZB|10<sup>21</sup>|zebibyte|ZiB|2<sup>70</sup>|18%|
|yottabyte|YB|10<sup>24</sup>|yobibyte|YiB|2<sup>80</sup>|21%|

## 1.3 Program Performance
### Below Your Program
- Application software (**program**)
  - Written in high-level language
- System Software
  - **Compiler**: translates HLL to machine code
  - **Operating System**: service code
    - Handling I/O (Input/Output)
    - Managing memory and storage
    - Cheduling tasks and sharing resources
- Hardware

### Levels of Program Code
- High-level language (C/C++, Java, etc)
  - Level of abstraction closer to problem domain
  - Provides for productivity and portability
- Assembly language
  - Textual representation of instructions
- Hardware representation
  - Binary Digits (bits)
  - Encoded instructions *and* data
  
### Program Performance
- **Algorithm** recipe to solve a problem
  - A **Program** can be thought of as an implementation of an algorithm in a specific language.
  - Determines the number of operations executed
- **Compiler**
  - Determine the number of machine instructions
- Processor and memory system
  - Determine how fast instructions are executed
- I/O system (including OS)
  - Determines how fast I/O operations are executed

## 1.4 Under the Covers
### Abstract Components of a Computer
Five classic components of a computer:

<img src='abstractComputer.png' title='Abstract Computer'>

1. Input
2. Output
3. Memory
4. Datapath
5. Control