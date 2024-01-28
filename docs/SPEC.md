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

## Error Handler

# Instruction Set

## Overview

## Human-readable bytecode (Assembly)

### Bytecode format

## Opcode

### Opcode format

## Code Block

### Stack Management

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

