# RVM Bytecode Specification

## Layout
When reading bytecode, each line represents a single instruction. An instruction contains 1 instruction byte, 1 type byte and (optionally) an argument.

Example of bytecode shown below. I've place spaces between the hexadecimals, and given each the 0x prefix, to make each value more distinct.
There are also comments explaining each line.
```asm
0xFF 0xFF 0x1
0xFF 0xFF 
0xFF 0xFF 0x2 // program header directive
0x4 0x4 0x2 // push 2 (i32)
0x4 0x4 0xA // push 10 (i32)
0x11 0x4    // add (i32)
0x4 0x4 0xA // push 10 (i32)
0x13 0x4    // mul (i32)
0x0 0x0     // halt
```

### Instruction byte
This is a complete list of all instruction bytes recognised by the virtual machine excluding the type byte.

| Symbol  | Description                                                                                          | Real Value | Inline Arguments | Stack Arguments |
|---------|------------------------------------------------------------------------------------------------------|------------|------------------|-----------------|
| `halt`  | Stop the virtual machine.                                                                            | `0x0`      | 0                | 0               |
| `noop`  | No operation; used as filler.                                                                        | `0x1`      | 0                | 0               |
| `load`  | Loads a variable from the symbol table and places it at the top of the stack.                        | `0x2`      | 1                | 0               |
| `store` | Pops a value from the top of the stack and stores it in the symbol table.                            | `0x3`      | 1                | 1               |
| `push`  | Pushes a constant value onto the stack.                                                              | `0x4`      | 1                | 0               |
| `pop`   | Removes a constant value from the stack.                                                             | `0x5`      | 0                | 1               |
| `dup`   | Duplicated the value at the top of the stack and places the duplicate value at the top of the stack. | `0x6`      | 0                | 1               |
| `swap`  | Swaps the value at the top of the stack and the value 2nd from the top of the stack.                 | `0x7`      | 0                | 2               |
| `br`    |                                                                                                      | `0x8`      | 1                | 0               |
| `brf`   |                                                                                                      | `0x9`      | 1                | 1               |
| `brt`   |                                                                                                      | `0xA`      | 1                | 1               |
| `beq`   |                                                                                                      | `0xB`      | 1                | 2               |
| `bge`   |                                                                                                      | `0xC`      | 1                | 2               |
| `bft`   |                                                                                                      | `0xD`      | 1                | 2               |
| `ble`   |                                                                                                      | `0xE`      | 1                | 2               |
| `blt`   |                                                                                                      | `0xF`      | 1                | 2               |
| `bne`   |                                                                                                      | `0x10`     | 1                | 2               |
| `add`   |                                                                                                      | `0x11`     | 0                | 2               |
| `sub`   |                                                                                                      | `0x12`     | 0                | 2               |
| `mul`   |                                                                                                      | `0x13`     | 0                | 2               |
| `div`   |                                                                                                      | `0x14`     | 0                | 2               |
| `mod`   |                                                                                                      | `0x15`     | 0                | 2               |
| `and`   |                                                                                                      | `0x16`     | 0                | 2               |
| `or`    |                                                                                                      | `0x17`     | 0                | 2               |
| `xor`   |                                                                                                      | `0x18`     | 0                | 2               |
| `shl`   |                                                                                                      | `0x19`     | 0                | 2               |
| `shr`   |                                                                                                      | `0x1A`     | 0                | 2               |
| `not`   |                                                                                                      | `0x1B`     | 0                | 1               |
| `neg`   |                                                                                                      | `0x1C`     | 0                | 1               |
| `conv`  |                                                                                                      | `0x1D`     | 0                | 1               |
| `eq`    |                                                                                                      | `0x1E`     | 0                | 2               |
| `ge`    |                                                                                                      | `0x1F`     | 0                | 2               |
| `gt`    |                                                                                                      | `0x20`     | 0                | 2               |
| `le`    |                                                                                                      | `0x21`     | 0                | 2               |
| `lt`    |                                                                                                      | `0x22`     | 0                | 2               |
| `ne`    |                                                                                                      | `0x23`     | 0                | 2               |

### Type byte
The type byte represents the type the instruction is operating on. Every type has its own dedicated value as shown below.

| Type   | Value |
|--------|-------|
| `void` | `0x0` |
| `i8`   | `0x1` |
| `i16`  | `0x2` |
| `i32`  | `0x3` |
| `i64`  | `0x4` |
| `u8`   | `0x5` |
| `u16`  | `0x6` |
| `u32`  | `0x7` |
| `u64`  | `0x8` |
| `f32`  | `0x9` |
| `f64`  | `0xA` |

### Argument
The argument can be anything but is usually encoded into bytes and decoded when the instruction is loaded.

## Directives
Directives provide metadata within the assembly. All directives are prefixed by a dot `.`. 
Directives, and [headers](#headers), are preprocessed by the virtual machine before bytecode begins executing. 

### Formatting
Lines containing a directive begin with `0xFF` after which a byte represents the type of directive.

### Directive list

| Symbol       | Description | Value      |
|--------------|-------------|------------|
| `[metadata]` |             | `0xFF 0x0` |
| `[data]`     |             | `0xFF 0x1` |
| `[program]`  |             | `0xFF 0x2` |
| `.name`      |             | `0xFF 0x3` |
| `.version`   |             | `0xFF 0x4` |
| `.extern`    |             | `0xFF 0x5` |
| `.const`     |             | `0xFF 0x6` |


## Headers
Headers are a special kind of directive that are used to structure the assembly into different sections such as `data` and `program`.

#### Formatting
Lines containing a header begin with `0xFF 0xFF` and the following bytes represents the header name.
Only 3 header names are recognised by the virtual machine: `metadata` (`0x0`), `data` (`0x1`), and `program` (`0x2`).

### Metadata header
The `[metadata]` header contains metadata about the assembly itself or details for pre-requisites for how the assembly should run.
```asm
[metadata]
.name "Program name"
.version 0.2.0
.extern someLib
```

### Data header
The `[data]` header contains constant data in the assembly. These symbols are automatically loaded into the symbol table upon start up.
```asm
[data]
.const x i32 234
```

### Program
The `[program]` header contains the instructions within the assembly.
```asm
[program]
pushi32 100
store y
load x
load y
addi32
store z
```

## External Assemblies
External assemblies can be imported using the `.extern` directive within the `[metadata]` header.
The name given in the `.extern <name>` statement much match the assembly's `.name` value.

The following names are reserved by the virtual machine:
- io
- mem
- math
- rand
- vm
- str
- os
- sys
- gc
- dll