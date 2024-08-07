//
// Created by hrs on 27/01/24.
//

#ifndef VM_H
#define VM_H

#include "stack.h"
#include "buffer.h"

// The VM is the main data structure of the interpreter.
typedef struct {
    Stack* stack;       // The stack is used to store values and perform operations on them.
    InstructionBuffer* buffer;     // The buffer is used to store the instructions.
    int ip;             // The instruction pointer is used to keep track of the current instruction.
    int state;          // States: 0 = Running, 1 = Paused, 2 = Stopped
    int debug;          // Debug mode: 0 = Off, 1 = On
} VM;

VM* create_vm(int capacity);    // Create a new VM with the specified stack and buffer capacity.
void destroy_vm(VM* vm);     // Destroy the VM and free all memory associated with it.
void run_vm(VM* vm);         // Set the VM's state to running. (NOTE: This is the default state)
void stop_vm(VM* vm);        // Stop VM interpretation. (NOTE: This will also clear the stack and buffer)
void dump_vm(VM* vm);        // Dump the VM's state. (NOTE: This will display the stack, buffer, instruction pointer, state, and debug mode)
void load_bytecode(VM* vm, InstructionBuffer* bytecode);    // Load bytecode into the VM's buffer.

#endif //VM_H
