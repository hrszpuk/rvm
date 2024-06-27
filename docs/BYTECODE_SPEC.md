# RVM Bytecode Specification

## Layout
When reading bytecode, each line represents a single instruction. An instruction contains 1 instruction byte, 1 type byte and (optionally) an argument.

Example of bytecode shown below. I've place spaces between the hexadecimals, and given each the 0x prefix, to make each value more distinct.
There are also comments explaining each line.
```asm
0xFF 0x1 // data directive (empty)
0xFF 0x2 // code directive
0x4 0x4 0x2 // push 2 (i32)
0x4 0x4 0xA // push 10 (i32)
0x11 0x4    // add (i32)
0x4 0x4 0xA // push 10 (i32)
0x13 0x4    // mul (i32)
0x0 0x0     // halt
```

### Instruction byte
This is a complete list of all instruction bytes recognised by the virtual machine excluding the type byte.

| Symbol     |   | Description                                                                                                                                    | Real Value | Inline Arguments | Stack Arguments |
|------------|:--|------------------------------------------------------------------------------------------------------------------------------------------------|------------|------------------|-----------------|
| `halt`     |   | Stop the virtual machine.                                                                                                                      | `0x0`      | 0                | 0               |
| `noop`     |   | No operation; used as filler.                                                                                                                  | `0x1`      | 0                | 0               |
| `load`     |   | Loads a variable from the symbol table and places it at the top of the stack.                                                                  | `0x2`      | 1                | 0               |
| `store`    |   | Pops a value from the top of the stack and stores it in the symbol table.                                                                      | `0x3`      | 1                | 1               |
| `push`     |   | Pushes a constant value onto the stack.                                                                                                        | `0x4`      | 1                | 0               |
| `pop`      |   | Removes a constant value from the stack.                                                                                                       | `0x5`      | 0                | 1               |
| `dup`      |   | Duplicated the value at the top of the stack and places the duplicate value at the top of the stack.                                           | `0x6`      | 0                | 1               |
| `swap`     |   | Swaps the value at the top of the stack and the value 2nd from the top of the stack.                                                           | `0x7`      | 0                | 2               |
| `br`       |   | Unconditional branch to a label.                                                                                                               | `0x8`      | 1                | 0               |
| `brf`      |   | Branch to the given label if the value at the top of the stack is false (0).                                                                   | `0x9`      | 1                | 1               |
| `brt`      |   | Branch to the given label if the value at the top of the stack is true (1).                                                                    | `0xA`      | 1                | 1               |
| `beq`      |   | Branch to the given label if the value at the top of the stack and the value below it are equal.                                               | `0xB`      | 1                | 2               |
| `bge`      |   | Branch to the given label if the value at the top of the stack is greater than or equal to the value below it on the stack.                    | `0xC`      | 1                | 2               |
| `bgt`      |   | Branch to the given label if the value at the top of the stack is greater than the value below it on the stack.                                | `0xD`      | 1                | 2               |
| `ble`      |   | Branch to the given label if the value at the top of the stack is less than or equal to the value below it on the stack.                       | `0xE`      | 1                | 2               |
| `blt`      |   | Branch to the given label if the value at the top of the stack is less than the value below it on the stack.                                   | `0xF`      | 1                | 2               |
| `bne`      |   | Branch to the given label if the value at the top of the stack is equal to the value below it on the stack.                                    | `0x10`     | 1                | 2               |
| `add`      |   | Pop the top 2 value on the stack, add them together, and push the result to the top of the stack.                                              | `0x11`     | 0                | 2               |
| `sub`      |   | Pop the top 2 value on the stack, subtract them together, and push the result to the top of the stack.                                         | `0x12`     | 0                | 2               |
| `mul`      |   | Pop the top 2 value on the stack, multiply them together, and push the result to the top of the stack.                                         | `0x13`     | 0                | 2               |
| `div`      |   | Pop the top 2 value on the stack, divide them together, and push the result to the top of the stack.                                           | `0x14`     | 0                | 2               |
| `mod`      |   | Pop the top 2 value on the stack, modulo them together, and push the result to the top of the stack.                                           | `0x15`     | 0                | 2               |
| `and`      |   | Pop the top 2 value on the stack, apply a bitwise and (t1 & t2), and push the result to the top of the stack.                                  | `0x16`     | 0                | 2               |
| `or`       |   | Pop the top 2 value on the stack, apply a bitwise or (t1 \| t2), and push the result to the top of the stack.                                  | `0x17`     | 0                | 2               |
| `xor`      |   | Pop the top 2 value on the stack, apply a bitwise xor (t` ^ t2), and push the result to the top of the stack.                                  | `0x18`     | 0                | 2               |
| `shl`      |   | Pop the top 2 value on the stack, apply a bitwise left shift (t1 << t2), and push the result to the top of the stack.                          | `0x19`     | 0                | 2               |
| `shr`      |   | Pop the top 2 value on the stack, apply a bitwise right shift (t1 >> t2), and push the result to the top of the stack.                         | `0x1A`     | 0                | 2               |
| `not`      |   | Pop the value at the top of the stack, apply a bitwise not (~t1), and push the result to the top of the stack.                                 | `0x1B`     | 0                | 1               |
| `land`     |   | Pop the top 2 value on the stack, apply an and (t1 && t2), and push the result to the top of the stack.                                        | `0x1C`     | 0                | 2               |
| `lor`      |   | Pop the top 2 value on the stack, apply a or (t1 \|\|  t2), and push the result to the top of the stack.                                       | `0x1D`     | 0                | 2               |
| `neg`      |   | Pop the value at the top of the stack, apply a negation (!t1), and push the result to the top of the stack.                                    | `0x1E`     | 0                | 1               |
| `conv`     |   | Convert the value at the top of the stack to the type specified (type byte, i.e. convi32).                                                     | `0x1F`     | 0                | 1               |
| `eq`       |   | Pop the top 2 value on the stack, if both are equal then push 1 to the stack otherwise push 0.                                                 | `0x20`     | 0                | 2               |
| `ge`       |   | Pop the top 2 value on the stack, if the first value is greater than, or equal to, the second value then push 1 to the stack otherwise push 0. | `0x21`     | 0                | 2               |
| `gt`       |   | Pop the top 2 value on the stack, if the first value is greater than the second value then push 1 to the stack otherwise push 0.               | `0x22`     | 0                | 2               |
| `le`       |   | Pop the top 2 value on the stack, if the first value is less than, or equal to, the second value then push 1 to the stack otherwise push 0.    | `0x23`     | 0                | 2               |
| `lt`       |   | Pop the top 2 value on the stack, if the first value is less than the second value then push 1 to the stack otherwise push 0.                  | `0x24`     | 0                | 2               |
| `ne`       |   | Pop the top 2 value on the stack, if neither are equal then push 1 to the stack otherwise push 0.                                              | `0x25`     | 0                | 2               |
| `<label>:` |   |                                                                                                                                                | `0x26`     | 0                | 0               |

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
The argument can be anything but is encoded into bytes and decoded when the instruction is loaded.
The type byte is used to tell the virtual machine how to decode the bytes in the right order.

| Type   | Example Value                     | Example Decoded      |
|--------|-----------------------------------|----------------------|
| `void` | N/A                               | N/A                  |
| `i8`   | `0x1`                             | `1`                  |
| `i16`  | `0xA 0x0`                         | `10`                 |
| `i32`  | `0x0 0x0 0x0 0x3`                 | `50331648`           |
| `i64`  | `0x0 0x0 0x0 0x3 0x0 0x0 0x0 0x3` | `216172782114177024` |
| `u8`   | `0x5`                             | `5`                  |
| `u16`  | `0x6 0x0`                         | `6`                  |
| `u32`  | `0x0 0x7 0x0 0x0`                 | `1792`               |
| `u64`  | `0x0 0x0 0x8 0x0 0x0 0x0 0x0 0x0` | `2048`               |
| `f32`  | `0x9`                             |                      |
| `f64`  | `0xA`                             |                      |

NOTE: the spaces between each value in the example value is not present in the binary code.

The byte order used is little-endian.

## Directives
Directives provide metadata within the assembly. All directives are prefixed by a dot `.`. 
Directives, and [headers](#headers), are preprocessed by the virtual machine before bytecode begins executing. 

### Formatting
Lines containing a directive begin with `0xFF` after which a byte represents the type of directive.

### Directive list

| Symbol                         | Description                                                                                       | Value      |
|--------------------------------|---------------------------------------------------------------------------------------------------|------------|
| `.meta`                        | Symbolises the start of the metadata block.                                                       | `0xFF 0x0` |
| `.data`                        | Symbolises the start of the data block.                                                           | `0xFF 0x1` |
| `.code`                        | Symbolises the start of the code block.                                                           | `0xFF 0x2` |
| `.name <name>`                 | The name of the modules. This may be used when creating libraries.                                | `0xFF 0x3` |
| `.version <version>`           | Similar to above. This is used when creating libraries.                                           | `0xFF 0x4` |
| `.extern <name>`               | Used to externally link to another rvm binary.                                                    | `0xFF 0x5` |
| `.const <name> <type> <value>` | A constant value declared inside the data block.                                                  | `0xFF 0x6` |
| `.export <label>`              | A label in the `.code` block. This will make the label available to other binaries via `.extern`. | `0xFF 0x7` |

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
- dll