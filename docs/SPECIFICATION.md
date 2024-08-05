# RVM specification v0.1.0
This specification covers the RVM library (librvm), the RVM command line utility (rvmcli), and the RVM assembler (ras).

## Project Structure
The project is split into three subprojects: librvm; a C library containing the virtual machine, rvmcli; a command line program for executing rvm assemblies and executables, and ras; a C library for converting between rvm assembly and bytecode.

## Virtual Machine Architecture

### Registers
There are a total of 11 registers. 
The first 8 registers (r0-r7) are general purpose. 
The ninth register is the program counter (r8), the tenth register is the stack pointer (r9), and the eleventh register (r10) is for status flags.

### Memory
There are two types of memory, stack and heap. The size of both stack and heap memory can be configured through parameters of the virtual machine.
The total memory used by the virtual machine will be a combination of both of these parameters (+ additional memory for registers and instructions).

### Stack 
Stack memory is used for storing the program and is stored on the physical stack of the machine.
The amount of stack memory is fixed upon starting the virtual machine and calculated as `(size of program + stack size parameter)`.
The stack size parameter is given when initialising the virtual machine.

>![WARNING]
> Stack memory is allocated using Variable Length Arrays (VLA). This means the stack remains very fast while also having its size determined at runtime.
> However, this also means allocating too much stack memory could cause a stack overflow.

### Heap
Heap memory is used for dynamic memory allocation. 
This memory must be manually allocated and deallocated by the program itself (no garbage collection).
Similar to stack memory, the heap size is a parameter to initialising the virtual machine.

>![NOTE]
> Much like a physical machine, memory capacity will not automatically increase at runtime. 
> If the program exceeds the heap capacity the virtual machine will crash.

## Instruction Set
| Value | Instruction | Example        | Description                                                                     |
|-------|-------------|----------------|---------------------------------------------------------------------------------|
| 0     | halt        | `halt`         | Stop the virtual machine.                                                       |
| 1     | noop        | `noop`         | No operation.                                                                   |
| 2     | load        | `load r0 10`   | Load a value into a register.                                                   |
| 3     | store       | `store r0 #10` | Store value in register at some address.                                        |
| 4     | push        | `push r0`      | Push value in register onto stack                                               |
| 5     | pop         | `pop r0`       | Pop value on stack into register                                                |
| 6     | add         | `add r0 r1`    | Add two registers together. This also works for a register and a value.         |
| 7     | sub         | `sub r0 r1`    | Subtract two registers together. This also works for a register and a value.    |
| 8     | mul         | `mul r0 r1`    | Multiply two registers together. This also works for a register and a value.    |
| 9     | div         | `div r0 r1`    | Divide two registers together. This also works for a register and a value.      |
| 10    | alloc       | `alloc r0 10`  | Allocate given bytes of memory and store the starting address in some register. |
| 11    | free        | `free r0 10`   | Free bytes of memory starting at some address stored in some register.          |
| 12    | print       | `print r0`     | Print value inside r0 as a character.                                           |


### Numeric suffixes
The virtual machine only accepts 32-bit signed integers stored in little endian.
However, a suffix (`#`) should be applied to any number that represents an address.



