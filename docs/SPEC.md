# Specification for RVM

### Table of Contents
- [Introduction](#introduction)
- [Architecture](#architecture)
  - [Overview](#overview)
  - [Call Stack](#call-stack)
  - [Instruction Buffer](#instruction-buffer)
  - [Registers](#registers)
  - [Variable Pool](#variable-pool)
  - [Multi-threading](#multi-threading)
    - [Multithreading API](#multithreading-api)
  - [Block Handler](#block-handler)
  - [Dynamic Library Loading](#dynamic-library-loading)
  - [Error Handler](#error-handler)
  - [Exception Stack](#exception-stack)
- [Instruction Set](#instruction-set)
  - [Overview](#overview-1)
  - [Assembly](#assembly)
    - [Assembly format](#assembly-format)
  - [Opcode](#opcode)
    - [Opcode format](#opcode-format)
    - [Types](#types)
  - [Code Block](#code-block)
    - [Stack Management](#stack-management)
    - [Arithmetic, Bitwise and Logical Operations](#arithmetic-bitwise-and-logical-operations)
    - [Control Flow](#control-flow)
    - [Store/Load](#storeload)
    - [Type Conversion](#type-conversion)
    - [Subroutines](#subroutines)
    - [Arrays](#arrays)
    - [Structures](#structures)
  - [Data Block](#data-block)
    - [Constants](#constants)
    - [Variables](#variables)
    - [Structures](#structures-1)
    - [Arrays](#arrays-1)
  - [Metadata block](#metadata-block)
- [Code base](#code-base)
  - [Overview](#overview-2)
  - [rvm library](#rvm-library)
  - [rvm assembler](#rvm-assembler)
  - [rvm assembly generator](#rvm-assembly-generator)
  - [rvm cli](#rvm-cli)
    - [rvm cli commands](#rvm-cli-commands)
- [Assembly reference](#assembly-reference) 

# Introduction
RVM is a virtual machine designed to be a simplistic and easy to use virtual machine for programming languages. 
It is designed to be a simple stack-based virtual machine with a high-performance opcode and a high-level expressive assembly language.
This document will describe the architecture of the virtual machine, the instruction set, and the code base.

# Architecture
The architecture described in this document is the architecture of the virtual machine.
The virtual machine can be found in the rvm library (src/lib).

## Overview
The RVM's architecture is split into 6 main components: the call stack, the instruction buffer, the registers, the variable pool, the opcode stream, and the dynamic library loader.
The virtual machine only understands bytecode/opcodes, so the translation module is used to translate the human-readable bytecode (assembly) into the machine-readable bytecode.

## Call Stack
The call stack is a stack of call frames. Each call frame contains the instruction pointer, the base pointer, and the stack pointer.
The instruction pointer points to the next instruction to be executed. The base pointer points to the base of the stack frame.
The stack pointer points to the top of the stack frame. The call stack is used to keep track of the current state of the program.

## Instruction Buffer
The instruction buffer stores all the instructions in the program.
This makes it easy to jump to a specific instruction in the program.

## Registers
There are a total of 10 registers, all of which are 64-bit. The registers are used to store temporary values.
A call frame has its own set of registers, so registers are not shared between call frames.

Registers are directly accessible by the assembly language.
They are accessed using the load and store instructions.
```asm 
.code

push 10
store r0 ; 'r' prefix + register number (0-9)
```

Not all registers are general-purpose. Some registers have a specific purpose.
The registers are as follows:
- r0-r7: general-purpose registers
- r8: vm flag register - controls the behavior of the virtual machine
- r9: vm error register - stores the error code of the last error

Although you may use r8 and r9 as general-purpose registers, it is not recommended.
Values stored in r8 and r9 may be overwritten or manipulate the behavior of the virtual machine.

**r8 flags:**
- 0: no flags
- 1: halt - halts the virtual machine
- 2: error - sets the error code in r9
- 3: halt and error - halts the virtual machine and sets the error code in r9
- 4: return - returns from the current function

**r9 error codes:**
- 0: no error
- 1: stack overflow
- 2: stack underflow
- 3: invalid opcode
- 4: invalid memory address
- 5: invalid memory access
- 6: memory allocation failed
- 7: thread creation failed
- 8: thread join failed
- 9: thread detach failed
- 10: thread cancellation failed
- 11: thread exit failed
- 12: exception thrown
- 13: exception handler not found
- 14: exception handler failed

## Variable Pool
The variable pool is a pool of variables. Each variable has a name, a type, and a value.
The variable pool is used to store global variables and local variables.

Each call frame has its own variable pool. When a function is called, a new variable pool is created.
When a function returns, the variable pool is destroyed.

Each local variable pool has a pointer to the global variable pool.
This allows instructions in the current call frame to access global variables.

## Multi-threading
The virtual machine is multithreaded.
This allows the virtual machine to run multiple threads at the same time.
Each thread has its own call stack, registers, and variable pool.

The global variable pool is shared between all threads.
This allows threads to share data.

The instruction buffer is shared between all threads.
This allows threads to share code.

### Multithreading API
Multithreading is accessible through the virtual machine standard library.
The virtual machine standard library provides functions for creating, joining, detaching, and canceling threads.

## Block Handler
The block handler is used to read and categorise different blocks in the assembly.
This means it will read `.meta`, `.code`, and `.data` block headers and read the contents of the block.

The raw string data is then passed to the translation module to be translated into opcode instructions.
If the translation module encounters a `.extern` instruction (for static linking), it will pass the instruction back to the block handler.
In this case, the process will begin again, with the block handler reading the library and sending it back.

It is important to note that, when the block handler is sent to read a library, the translation module will give it all libraries that have already been processed.
This is to prevent infinite loops of reading the same library over and over again, or reading a library that has already been read.

## Dynamic Library Loading
The virtual machine supports dynamic library loading.
This allows the virtual machine to load libraries at runtime.
Dynamic library loading is usually used for calling C code from the virtual machine.

The virtual machine standard library (`ldx`) provides functions for loading dynamic libraries.
NOTE(hrs): The virtual machine standard library is not implemented yet. This is just an example. This code may be changed in the future.
```asm 
.meta
.extern <ldex> ldex ; load standard library for dynamic library loading

.data
.const lib "libtest.so" ; library name
.var handle [ldex]handle ; handle to library
.var function [ldex]function ; function pointer

.code
push "libtest.so"
push handle
call [ldex]load ; load library and get handle
push handle
push null
eq
jmpc error ; if handle is null, jump to error
push function
push handle
call [ldex]loadfunc 
push function
push null
eq
jmpc error ; if function is null, jump to error
push function
call [ldex]callfunc ; call function
push handle
call [ldex]unload ; dlclose(handle)
error:
halt
```

The ldex library utilies the `dlopen`, `dlsym`, and `dlclose` functions from the `dlfcn.h` header file.

## Error Handler
The error handler is used to handle errors that occur during the execution of the virtual machine.
The error handler will set the error flag in r8 and the error code in r9.
Depending on the error flag, the virtual machine will either halt or return from the current function.

If the virtual machine halts, it will return error information.
The `rvm cli` will print the error information to the console.

## Exception Stack
The exception stack is a stack of exception frames.
Each exception frame contains the origin call frame, the origin instruction pointer, and the exception handler.
The origin call frame is the call frame that threw the exception.

The exception stack is used to keep track of the current state of the program when an exception is thrown.
When an exception is thrown, the virtual machine will jump to the exception handler.
The exception handler will then handle the exception and return to the origin call frame.

The exception stack is only used when the virtual machine encounters an exception.

# Instruction Set
This section will describe the instruction set of the virtual machine and the assembly language.

## Overview
The virtual machine uses a stack-based architecture.
This means that most instructions operate on the stack.
There are two main blocks in the virtual machine: the code block and the data block.
The code block contains instructions and the data block contains data.

## Assembly
The assembly language is a human-readable bytecode.
It is used to write programs for the virtual machine.
It is designed to be high-level, expressive, and easy to use.
This means that assembly code may not directly translate to bytecode.
The translation module will translate the assembly code into bytecode.

### Assembly format
The format of the assembly language is as follows:
```asm
.meta ; metadata block

.data ; data block

.code ; code block

halt ; end of program (must be last instruction)
```

Assembly instructions (found in the code block) are written in the following format:
```asm
<instruction> [arg]

```
It is important to note that an instruction may have 0 or 1 arguments.
Instructions that require more than one argument will use the stack to get the other arguments.

Example:
```asm 
.code
push 1
push 2
add
halt
```

Instructions consume arguments. This means that the arguments will be popped off the stack when the instruction is executed.

## Opcode
The opcode is the machine-readable bytecode.
It is designed to be simple, lean, and fast.
This means it is not designed to be human-readable.
The translation module will translate the assembly code into bytecode.

### Opcode format
Opcode is written in a binary format.
The first byte is the opcode, the second byte is the argument type, and the following bytes are the arguments.
The number of arguments depends on the opcode. However, most opcodes have 0 or 1 arguments.
If an opcode requires more than one argument, the arguments will be pushed onto the stack.

Example:
```asm
6312345 ; push i32 12345 onto the stack
0 ; halt
```

Code blocks and labels are also written in a binary format.
The first byte is the label/code block byte, and the following bytes are a 64-bit integer representing the address of the label/code block.
This means that the real name of a label is the address of the label.

### Types
Types are used to represent the type of a value, or instruction.
The type byte comes directly after the instruction byte.

The virtual machine supports the following types:

| Type   | Description                  | Opcode byte value |
|--------|------------------------------|-------------------|
| void   | no type                      | 0                 |
| i8     | 8-bit signed integer         | 1                 |
| i16    | 16-bit signed integer        | 2                 |
| i32    | 32-bit signed integer        | 3                 |
| i64    | 64-bit signed integer        | 4                 |
| u8     | 8-bit unsigned integer       | 5                 |
| u16    | 16-bit unsigned integer      | 6                 |
| u32    | 32-bit unsigned integer      | 7                 |
| u64    | 64-bit unsigned integer      | 8                 |
| f32    | 32-bit floating point number | 9                 |
| f64    | 64-bit floating point number | 10                |
| char   | 8-bit character              | 11                |
| bool   | boolean                      | 12                |
| ptr    | pointer                      | 13                |

Arrays and structures are not types. They are just a collection of types.
Array/structure types are represented by a pointer to the first element in the array/structure.

Pointers are represented by a 64-bit integer.
When a pointer is pushed/loaded onto the stack, the address the pointer is pointing to is pushed/loaded onto the stack.
You must use the `deref` instruction to get the value of an address.


## Code Block
The code block contains instructions. The code block starts with a code block header (`.code`).

### Stack Management
The stack management instructions are used to manage the stack.

| Instruction    | Description                               |
|----------------|-------------------------------------------|
| push \<value\> | Pushes a value onto the stack             |
| pop            | Pops a value off the stack                |
| dup            | Duplicates the top value on the stack     |
| swap           | Swaps the top two values on the stack     |
| rot            | Rotates the top three values on the stack |

### Arithmetic, Bitwise and Logical Operations
The arithmetic, bitwise and logical operations are used to perform arithmetic, bitwise and logical operations.

| Instruction | Description                                                           |
|-------------|-----------------------------------------------------------------------|
| add         | Adds the top two values on the stack                                  |
| sub         | Subtracts the top two values on the stack                             |
| mul         | Multiplies the top two values on the stack                            |
| div         | Divides the top two values on the stack                               |
| mod         | Modulus the top two values on the stack                               |
| and         | Bitwise and the top two values on the stack                           |
| or          | Bitwise or the top two values on the stack                            |
| xor         | Bitwise xor the top two values on the stack                           |
| not         | Bitwise not the top value on the stack                                |
| shl         | Bitwise shift left the top two values on the stack                    |
| shr         | Bitwise shift right the top two values on the stack                   |
| eq          | Compares the top two values on the stack for equality                 |
| neq         | Compares the top two values on the stack for inequality               |
| gt          | Compares the top two values on the stack for greater than             |
| gte         | Compares the top two values on the stack for greater than or equal to |
| lt          | Compares the top two values on the stack for less than                |
| lte         | Compares the top two values on the stack for less than or equal to    |
| land        | Logical and the top two values on the stack                           |
| lor         | Logical or the top two values on the stack                            |
| lnot        | Logical not the top value on the stack                                |
| inc         | Increments the top value on the stack                                 |
| dec         | Decrements the top value on the stack                                 |
| neg         | Negates the top value on the stack                                    |

### Control Flow
The control flow instructions are used to control the flow of the program.

| Instruction    | Description                                            |
|----------------|--------------------------------------------------------|
| jmp \<label\>  | Jumps to a label                                       |
| jmpc \<label\> | Jumps to a label if the top value on the stack is true |

Labels are defined as `<label_name>:` (colon on the end).

### Store/Load
The store/load instructions are used to store and load values.

| Instruction | Description                                                                 |
|-------------|-----------------------------------------------------------------------------|
| store \<id\> | Stores the top value on the stack in a variable with the id \<id\>          |
| load \<id\>  | Loads the value of a variable with the id \<id\> onto the top of the stack |

### Type Conversion
The type conversion instructions are used to convert values from one type to another.

| Instruction | Description                                                                 |
|-------------|-----------------------------------------------------------------------------|
| itof        | Converts an integer to a float                                              |
| itos        | Converts an integer to a string                                             |
| itob        | Converts an integer to a boolean                                            |
| itoc        | Converts an integer to a character                                          |
| itop        | Converts an integer to a pointer                                            |
| ftoi        | Converts a float to an integer                                              |
| ftos        | Converts a float to a string                                                |
| ftob        | Converts a float to a boolean                                               |
| ftoc        | Converts a float to a character                                             |
| stoi        | Converts a string to an integer                                             |
| stof        | Converts a string to a float                                                |
| stob        | Converts a string to a boolean                                              |
| stoc        | Converts a string to a character                                            |
| ctos        | Converts a character to a string                                            |
| ctob        | Converts a character to a boolean                                           |
| ptoi        | Converts a pointer to an integer                                            |
| ptos        | Converts a pointer to a string                                              |
| ctof        | Converts a character to a float                                             |
| ctoi        | Converts a character to an integer                                          |

Example:
```asm
.code
push 1
itos
push "1"
eq
btos
call [io]print
halt
```

### Subroutines
The subroutine instructions are used to create and call subroutines.
Subroutines are always called, and created, in the code block.

It is best practice to create a subroutines at the top of the code block, and call them at the bottom of the code block.

| Instruction  | Description                            |
|--------------|----------------------------------------|
| call \<id\>  | Calls a subroutine with the id \<id\>  |
| ret          | Returns from the current subroutine    |
| begin \<id\> | Begins a subroutine with the id \<id\> |
| end          | Ends the current subroutine            |

When a subroutine is called, a new call frame is created.
Every call frame has its own variable pool.
This means that variables created in a subroutine are not accessible outside the subroutine.

Void type subroutines do not need a type annotation.

Example:
```asm
; begin <type> <id>
; // code
; end
.code
begin void main
push "Hello, World!"
call [io]print
end

call main
halt
```

### Arrays
Arrays are used to store a collection of values.
Arrays are stored in the variable pool.

Internally, arrays are stored as pointers to the first element in the array.
This means that arrays are passed by reference.

The array index can be incremented and decremented using the `inc` and `dec` instructions (or `add`/`sub`).
To get a value from an array, you must use `deref` to dereference the pointer.

```asm
.data
; Arrays stored in .data block are global arrays (accessible from all functions)
.var arr [i32:5]
.const arr2 [i32:5] 1 2 3 4 5

.code
load arr    ; load address to arr[0]
push 1      ; push value to store
store arr   ; store value at arr[0] 
load arr    ; load address to arr[0]
deref       ; dereference pointer (1)
pop         ; pop value off stack
load arr    ; load address to arr[0]
inc         ; increment address (arr[1])
push 2      ; push value to store
store arr   ; store value at arr[1]

push [i32:10] ; push array onto stack
store arr3

halt
```
If you increment the array index past the end of the array, the virtual machine will throw an exception.
To prevent this, you must check the array index before incrementing it.

The virtual machine will always check array bounds when using the `store` instruction.
This worsens performance, but it prevents the virtual machine from crashing.
You may disable array bounds by modifying the vm flag register (r8).

### Structures
Structures are used to store a collection of values.
Structures are stored in the variable pool.

Internally, structures are stored as pointers to the first element in the structure.
The index after the last element in the structure is a null pointer.

The structure index can be incremented and decremented using the `inc` and `dec` instructions (or `add`/`sub`).
To get a value from a structure, you must use `deref` to dereference the pointer.

```asm
.data
.struct Point i32 i32 string ; define structure
.var point Point 1 2 "Hello, World!" ; create structure

.code
load point ; load address to point.x
push 1 ; push value to store
store point ; store value at point.x
load point ; load address to point.x
deref ; dereference pointer (1)
pop ; pop value off stack
load point ; load address to point.x
inc
inc
inc ; DO NOT DEFERENCE THE POINTER
push 0
eq ; this will be true as null is 0
halt
```

## Data Block
The data block contains data. The data block starts with a data block header (`.data`).
All instructions in the data block a prefixed with a `.`.

### Constants
Constants are used to store constant values.
Constants are stored in the variable pool.

```asm 
.data
.const <id> <value> ; <id> is the id of the constant, <value> is the value of the constant

; Examples with type inference
.const x 100
.const msg "Hello, World!"

; Examples with explicit types
.const x i32 100
.const msg [char] "Hello, World!"
```

### Variables
Variables are used to store values.
Variables are stored in the variable pool.

```asm
.data
; Variables stored in .data block are global variables (accessible from all functions)

.var <id> <type> <value>; <id> is the id of the variable, <type> is the type of the variable, <value> is the value of the variable
.var x i32 100
.var msg [char] "Hello, World!"

; with type inference
.var x 100
.var msg "Hello, World!"

.code 
; Variables stored in .code block are local variables (accessible from the current function)
begin func
push 100
store y ; stored in local variable pool
end
func ; local variable pool is created when function is called
halt ; local variable pool is destroyed when function returns
```

## Metadata block

# Code base

## Overview
The code base is split into four main components: the rvm library, the rvm cli, the rvm assembler, and the rvm generator.

## rvm library
The rvm library is the core of the virtual machine.
It contains the call stack, the instruction buffer, the registers, the variable pool, the opcode stream, and the dynamic library loader.
This is what is used to actually run rvm programs.

More information about what is in the rvm library can be found in the [architecture](#architecture) section.

## rvm assembler
The rvm assembler is used to translate human-readable bytecode (assembly) into machine-readable bytecode.
It is used by the rvm cli to compile rvm assembly into bytecode.

More information about the rvm assembler can be found in the [Instruction Set](#instruction-set) section.

## rvm assembly generator
This is a library available to compiler developers to generate rvm assembly.

The generation API has not been decided yet.

## rvm cli
The rvm command line interface allows you to run rvm programs from the command line.
It also allows you to compile rvm assembly into bytecode/opcode.

### rvm cli commands
- `rvm run <file>`: run rvm program
- `rvm build <file>`: compile rvm assembly into bytecode/opcode (this may also conduct linking)
- `rvm help`: print help message

# Assembly reference
This section is a list of every instruction in the assembly language along with a description of what it does, its arguments, and its opcode.

| Instruction | Opcode | Arguments                      | Description                                                                |
|-------------|--------|--------------------------------|----------------------------------------------------------------------------|
| halt        | 0      |                                | Halts the virtual machine                                                  |
| noop        | 1      |                                | No operation                                                               |
| load        | 2      | \<id\>                         | Loads the value of a variable with the id \<id\> onto the top of the stack |
| store       | 3      | \<id\>                         | Stores the top value on the stack in a variable with the id \<id\>         |
| push        | 4      | \[type\] \<value\>             | Pushes a value onto the stack                                              |
| pop         | 5      |                                | Pops a value off the stack                                                 |
| dup         | 6      |                                | Duplicates the top value on the stack                                      |
| swap        | 7      |                                | Swaps the top two values on the stack                                      |
| rot         | 8      |                                | Rotates the top three values on the stack                                  |
| add         | 9      |                                | Adds the top two values on the stack                                       |
| sub         | 10     |                                | Subtracts the top two values on the stack                                  |
| mul         | 11     |                                | Multiplies the top two values on the stack                                 |
| div         | 12     |                                | Divides the top two values on the stack                                    |
| mod         | 13     |                                | Modulus the top two values on the stack                                    |
| and         | 14     |                                | Bitwise and the top two values on the stack                                |
| or          | 15     |                                | Bitwise or the top two values on the stack                                 |
| xor         | 16     |                                | Bitwise xor the top two values on the stack                                |
| not         | 17     |                                | Bitwise not the top value on the stack                                     |
| shl         | 18     |                                | Bitwise shift left the top two values on the stack                         |
| shr         | 19     |                                | Bitwise shift right the top two values on the stack                        |
| eq          | 20     |                                | Compares the top two values on the stack for equality                      |
| neq         | 21     |                                | Compares the top two values on the stack for inequality                    |
| gt          | 22     |                                | Compares the top two values on the stack for greater than                  |
| gte         | 23     |                                | Compares the top two values on the stack for greater than or equal to      |
| lt          | 24     |                                | Compares the top two values on the stack for less than                     |
| lte         | 25     |                                | Compares the top two values on the stack for less than or equal to         |
| land        | 26     |                                | Logical and the top two values on the stack                                |
| lor         | 27     |                                | Logical or the top two values on the stack                                 |
| lnot        | 28     |                                | Logical not the top value on the stack                                     |
| inc         | 29     |                                | Increments the top value on the stack                                      |
| dec         | 30     |                                | Decrements the top value on the stack                                      |
| neg         | 31     |                                | Negates the top value on the stack                                         |
| jmp         | 32     | \<label\>                      | Jumps to a label                                                           |
| jmpc        | 33     | \<label\>                      | Jumps to a label if the top value on the stack is true                     |
| call        | 34     | \<id\>                         | Calls a subroutine with the id \<id\>                                      |
| ret         | 35     |                                | Returns from the current subroutine                                        |
| begin       | 36     | \<type\>\ <id\>                | Begins a subroutine with the id \<id\>                                     |
| end         | 37     |                                | Ends the current subroutine                                                |
| typeof      | 38     |                                | Pushes the type of the top value on the stack onto the stack               |
| deref       | 39     |                                | Dereferences the top value on the stack                                    |
| itof        | 40     |                                | Converts an integer to a float                                             |
| itos        | 41     |                                | Converts an integer to a string                                            |
| itob        | 42     |                                | Converts an integer to a boolean                                           |
| itoc        | 43     |                                | Converts an integer to a character                                         |
| itop        | 44     |                                | Converts an integer to a pointer                                           |
| ftoi        | 45     |                                | Converts a float to an integer                                             |
| ftos        | 46     |                                | Converts a float to a string                                               |
| ftob        | 47     |                                | Converts a float to a boolean                                              |
| ftoc        | 48     |                                | Converts a float to a character                                            |
| stoi        | 49     |                                | Converts a string to an integer                                            |
| stof        | 50     |                                | Converts a string to a float                                               |
| stob        | 51     |                                | Converts a string to a boolean                                             |
| stoc        | 52     |                                | Converts a string to a character                                           |
| ctos        | 53     |                                | Converts a character to a string                                           |
| ctob        | 54     |                                | Converts a character to a boolean                                          |
| ptoi        | 55     |                                | Converts a pointer to an integer                                           |
| ptos        | 56     |                                | Converts a pointer to a string                                             |
| ctof        | 57     |                                | Converts a character to a float                                            |
| ctoi        | 58     |                                | Converts a character to an integer                                         |
| .const      | 59     | \<id\> \<type\> \<value\>      | Defines a constant with the id \<id\> and the value \<value\>              |
| .var        | 60     | \<id\> \<type\> \<value\>      | Defines a variable with the id \<id\> and the value \<value\>              |
| .struct     | 61     | \<id\> \<type\>                | Defines a structure with the id \<id\> and the type \<type\>               |
| .extern     | 62     | \<\"id\" \| \<id\>\>  \"name\" | Defines a link with an external library                                    |
| .code       | 63     |                                | Starts the code block                                                      |
| .data       | 64     |                                | Starts the data block                                                      |
| .meta       | 65     |                                | Starts the metadata block                                                  |


[Back to top](#specification-for-rvm)