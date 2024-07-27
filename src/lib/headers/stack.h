//
// Created by hrs on 24/01/24.
//

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "buffer.h"

typedef struct {
    InstructionType type;
    InstructionArgumentValue value;
} StackValue;

typedef struct {
    StackValue* data;
    int capacity;
    int count;
    int growthFactor;     // Default to 2 (NOTE: growth rate is always 1 * growthFactor)
} Stack;

Stack* create_stack(int capacity);              // Create a stack with a given capacity
StackValue pop_stack(Stack* stack);             // Pop the top element from the stack
void push_stack(Stack* stack, StackValue);      // Push an element to the stack
void free_stack(Stack* stack);                  // Free the stack
void print_stack(Stack* stack);                 // Print the stack
void grow_stack(Stack* stack);                  // Grow the stack
void clear_stack(Stack* stack);                 // Clear the stack
bool is_empty_stack(Stack* stack);              // Check if the stack is empty
StackValue top_stack(Stack* stack);             // Get the top element of the stack (without popping)

#endif //STACK_H
