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

