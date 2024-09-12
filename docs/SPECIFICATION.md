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
- **Type word**: Stores type information about operands.
- **Operands**: A variable length encoding of some data/reference.

#### Type word structure
The type word is a 16-bit structure used to describe the types of the operands in an instruction.

- **Bit 0**: Reserved
- **Bits 1-2**: Operand 1 type
- **Bits 3-5**: Operand 1 type info
- **Bits 6-7**: Operand 2 type
- **Bits 8-10**: Operand 2 type info
- **Bits 10-11**: Operand 3 type
- **Bits 12-15**: Operand 3 type info

If an operand is not used in an instruction the bits for that operand will be ignored (i.e. `halt` will ignore the entire type byte.).
However, the type bits are not required 

#### Operand types encoding
The operand type bits describe the category

| Hex   | Name      | Purpose                                                                    |
|-------|-----------|----------------------------------------------------------------------------|
| `0x0` | Register  | For references to registers.                                               |
| `0x1` | Immediate | For using signed/unsigned integer values.                                  |
| `0x2` | Extended  | For floating point values, floating point registers, and 32-bit addresses. |
| `0x3` | Reserved  | Reserved for future extensions to the instruction set architecture.        |


#### Register value size/type encoding
When the register type is used, the following values can be specified in the type info bits.

| Hex | Type                    |
|-----|-------------------------|
| 0x0 | 8-bit integer           |
| 0x1 | 16-bit integer          |
| 0x2 | 32-bit integer          |
| 0x3 | 64-bit integer          |
| 0x4 | unsigned 8-bit integer  |
| 0x5 | unsigned 16-bit integer |
| 0x6 | unsigned 32-bit integer |
| 0x7 | unsigned 64-bit integer |


#### Immediate value size/type encoding
When an operand type is an immediate value, the following values can be specified in the type info bits.

| Hex | Type                    |      
|-----|-------------------------|      
| 0x0 | 8-bit integer           |      
| 0x1 | 16-bit integer          |      
| 0x2 | 32-bit integer          |      
| 0x3 | 64-bit integer          |      
| 0x4 | unsigned 8-bit integer  |      
| 0x5 | unsigned 16-bit integer |      

#### Extended value size/type encoding
When an operand type is an extended value, the following values can be specified in the type info bits.       

| Hex | Type                           |      
|-----|--------------------------------|      
| 0x0 | 32-bit floating point          |      
| 0x1 | 64-vit floating point          |      
| 0x2 | 32-bit floating point register |      
| 0x3 | 64-bit floating point register |      
| 0x4 | 32-bit address                 |         

>[!NOTE] Reserved bits are for future extensions. Using reserved bits will cause the virtual machine to crash.

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
| 0xA   | mul         | `mul r0, r1, r2` | Multiply the value in register 1 with the value in register 2 and store the result in register 0. |
| 0xB   | div         | `div r0, r1, r2` | Divide the value in register 1 with the value in register 2 and store the result in register 0.   |
| 0xC   | alloc       | `alloc r0, 10`   | Allocate 10 bytes and store the first address in register 0.                                      |
| 0xD   | free        | `free r0, 10`    | Free 10 bytes starting at the address stored in register 0.                                       |

## Instruction Buffer
The instruction buffer loads, stores, and manages instructions/labels on the virtual machine.
Bytecode instructions are not stored in memory but a separate region called the instruction buffer.
The advantages of using this data structure is increased flexibility and better debugging support.

### Label Map
The label map is a hashmap of the label values to absolute/offset addresses within the code.
The instruction buffer will complete a single pass of the bytecode to fill the label map before the virtual machine begins executing.