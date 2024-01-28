# Specification for RVM

### Table of Contents
- [Table of Contents](#table-of-contents)
- [Introduction](#introduction)
- [Architecture](#architecture)
  - [Overview](#overview)
  - [Call Stack](#call-stack)
  - [Instruction Buffer](#instruction-buffer)
  - [Registers](#registers)
  - [Variable Pool](#variable-pool)
  - [Multi-threading](#multi-threading)
  - [Opcode Stream](#opcode-stream)
  - [Dynamic Library Loading](#dynamic-library-loading)
  - [Error Handler](#error-handler)
- [Instruction Set](#instruction-set)
  - [Overview](#overview-1)
  - [Human-readable bytecode (Assembly)](#human-readable-bytecode-assembly)
    - [Bytecode format](#bytecode-format)
  - [Opcode](#opcode)
    - [Opcode format](#opcode-format)
  - [Code Block](#code-block)
    - [Stack Management](#stack-management)
    - [Arithmetic, Bitwise and Logical Operations](#arithmetic-bitwise-and-logical-operations)
    - [Control Flow](#control-flow)
    - [Store/Load](#storeload)
    - [Type Conversion](#type-conversion)
    - [Subroutines](#subroutines)
  - [Data Block](#data-block)
    - [Constants](#constants)
    - [Variables](#variables)
    - [Structures](#structures)
  - [Metadata block](#metadata-block)

# Introduction
RVM is a virtual machine designed to be a simplistic and easy to use virtual machine for programming languages. 
It is designed to be a simple stack-based virtual machine with a high-performance opcode and a high-level expressive assembly language.
This document will describe the architecture of the virtual machine, the instruction set, and the code base.

# Architecture
The architecture described in this document is the architecture of the virtual machine.
The virtual machine can be found in the rvm library (src/lib).

## Overview

## Call Stack

## Instruction Buffer

## Registers

## Variable Pool

## Multi-threading

## Opcode Stream

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

