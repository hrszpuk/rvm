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

Stack* CreateStack(int capacity);   // Create a stack with a given capacity
StackValue PopStack(Stack*);             // Pop the top element from the stack
void PushStack(Stack*, StackValue);      // Push an element to the stack
void FreeStack(Stack*);             // Free the stack
void PrintStack(Stack*);            // Print the stack
void GrowStack(Stack*);             // Grow the stack
void ClearStack(Stack*);            // Clear the stack
bool IsEmptyStack(Stack*);          // Check if the stack is empty
StackValue TopStack(Stack*);             // Get the top element of the stack (without popping)

#endif //STACK_H
