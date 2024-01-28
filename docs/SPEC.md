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
6312345 ; push 12345 onto the stack
0 ; halt
```

Code blocks and labels are also written in a binary format.
The first byte is the label/code block byte, and the following bytes are a 64-bit integer representing the address of the label/code block.
This means that the real name of a label is the address of the label.

## Types
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
You must use the `deref` instruction to get the value of the pointer.

Pointers are special. When the virtual machine encounters a pointer, it will push the address of the pointer onto the stack.
To get the value of a pointer, you must use the `load` instruction.
To get the type of pointer, you must use the `typeof` instruction.
The `typeof` instruction will push the type of the pointer onto the stack (i.e. i32 would be 3).
Null pointers are represented by the value 0.
The standard library includes a macro for null pointers (`null`).

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

### Control Flow

### Store/Load

### Type Conversion

### Subroutines

## Data Block

### Constants

### Variables

### Structures

## Metadata block

# Code base

## Overview

## rvm library

### Translation Module

### Generation Module

### VM Module

### Common Data Structures

## rvm cli

