# RVM specification v0.1.0
This specification covers the RVM library (librvm), the RVM command line utility (rvmcli), and the RVM assembler (ras).

## Project Structure
The project is split into three subprojects: librvm; a C library containing the virtual machine, rvmcli; a command line program for executing rvm assemblies and executables, and ras; a C library for converting between rvm assembly and bytecode.

## Instruction Set Architecture

### Registers
There are a total of 16 registers. The first 12 registers (r0-r11) are general purpose, this means they can support any unsigned/signed integer as well as floating point values.
The last 4 registers are reserved for the program counter (r12), the stack pointer (r13), the frame pointer (r14), and the status/flag register (r15).

### Memory
There are two types of memory, stack and heap. The size of both stack and heap memory can be configured through parameters of the virtual machine.
The total memory used by the virtual machine will be a combination of both of these parameters (+ additional memory for registers and instructions).

### Stack 
Stack memory is used to manage local variables, function parameters, and return addresses.
The stack will grow and shrink dynamically as functions are called and return.

This memory can be accessed using the `push` and `pop` instructions.
Manual manipulation of the stack pointer can also be used.

### Heap
Heap memory is used for dynamic memory allocation. 
This memory must be manually allocated and deallocated by the program itself (no garbage collection).

>![NOTE]
> Much like a physical machine, memory capacity will not automatically increase at runtime. 
> If the program exceeds capacity the virtual machine will crash.

### Instruction Encoding
Instructions are stored in a binary format (.rvm). Each instruction is made up of a series of bytes:
- **Opcode byte**: Stores the instruction (i.e. `mov`, `add`, etc.).
- **Type byte**: Stores type information about operands.
- **Operands**: A variable length encoding of some data/reference.

#### Type byte structure
The type byte is structured in a way to convey all information necessary to process the instruction's operands.

- **Bits 0-1**: Operand 1 type
- **Bits 2-3**: Operand 2 type
- **Bits 4-5**: Operand 3 type
- **Bits 6-7**: Reserved for size/additional-type information

If an operand is not used in an instruction the bits for that operand will be ignored (i.e. `halt` will ignore the entire type byte.).

#### Operand types encoding
The operand type bits tell the virtual machine how to read the operand encoding. Without this information, operands may be parsed differently from how they are intended to be.
- `00` - Register (4-bit ID)
- `01` - Immediate Value 
- `10` - Memory address (32-bit ID)
- `11` - Extended Value

#### Immediate value size encoding
When an operand type is an immediate value the size is determined by bits 6-7.
- `00` - 8-bit integer
- `01` - 16-bit integer
- `10` - 32-bit integer
- `11` - 64-bit integer

#### Extended value type encoding
When an operand type is an extended value bits 6-7 are for 32-bit and 64-bit floating points.
- `00` - Reserved/unused
- `01` - Reserved/unused
- `10` - 32-bit floating point
- `11` - 64-bit floating point 

>[!NOTE] The split between immediate and extended values means instructions can only operate on operands of the same type.
> Values of different types must be cast to the same type before being operated on.

### Instruction List
| Value | Instruction | Example          | Description (of example)                                                                          |
|-------|-------------|------------------|---------------------------------------------------------------------------------------------------|
| 0x0   | halt        | `halt`           | Stops the virtual machine.                                                                        |
| 0x1   | noop        | `noop`           | No operation.                                                                                     |
| 0x2   | mov         | `mov r0, 10`     | Load the value 10 into register 0.                                                                |
| 0x3   | load        | `load r0, [10]`  | Load the address 10 into register 0.                                                              |
| 0x4   | store       | `store [3], r0`  | Store the value in register 0 in address 3.                                                       |
| 0x5   | push        | `push r0`        | Push value in register 0 onto stack.                                                              |
| 0x6   | pop         | `pop r0`         | Pop value on top of stack into register 0.                                                        |
| 0x7   | add         | `add r0, r1, r2` | Add the value in register 1 with the value in register 2 and store the result in register 0.      |
| 0x8   | sub         | `sub r0, r1, r2` | Subtract the value in register 1 with the value in register 2 and store the result in register 0. |
| 0x9   | mul         | `mul r0, r1, r2` | Multiply the value in register 1 with the value in register 2 and store the result in register 0. |
| 0xA   | div         | `div r0, r1, r2` | Divide the value in register 1 with the value in register 2 and store the result in register 0.   |
| 0xB   | alloc       | `alloc r0, 10`   | Allocate 10 bytes and store the first address in register 0.                                      |
| 0xC   | free        | `free r0, 10`    | Free 10 bytes starting at the address stored in register 0.                                       |

## Instruction Buffer
The instruction buffer loads, stores, and manages instructions/labels on the virtual machine.
Bytecode instructions are not stored in memory but a separate region called the instruction buffer.
The advantages of using this data structure is increased flexibility and better debugging support.

### Label Map
The label map is a hashmap of the label values to absolute/offset addresses within the code.
The instruction buffer will complete a single pass of the bytecode to fill the label map before the virtual machine begins executing.