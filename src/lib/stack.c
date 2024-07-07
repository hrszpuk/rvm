//
// Created by hrs on 24/01/24.
//

#include "headers/stack.h"

#include <stdio.h>
#include <stdlib.h>

Stack* create_stack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    stack->data = malloc(sizeof(StackValue) * capacity);
    stack->capacity = capacity;
    stack->count = 0;
    stack->growthFactor = 2;
    return stack;
}

StackValue pop_stack(Stack* stack) {
    StackValue data = top_stack(stack);
    stack->count--;
    return data;
}

void push_stack(Stack* stack, StackValue) {
    if (stack->count == stack->capacity) {
        grow_stack(stack);
    }
    stack->data[stack->count] = data;
    stack->count++;
}

void free_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

void print_stack(Stack* stack) {
    printf("Stack dump:\n");
    for (int i = 0; i < stack->count; i++) {
        printf("%d: %p %d\n", i, stack->data + i, stack->data[i].value.i32);
    }
    printf("Total stack size: %d (capacity %d)\n", stack->count, stack->capacity);
}

void grow_stack(Stack* stack) {
    stack->capacity *= stack->growthFactor;
    stack->data = realloc(stack->data, sizeof(StackValue) * stack->capacity);
}

void clear_stack(Stack* stack) {
    stack->count = 0;
}

bool is_empty_stack(Stack* stack) {
    return stack->count == 0;
}

StackValue top_stack(Stack* stack) {
    if (stack->count == 0) {
        return (StackValue){IT_void, {.i32 = 0}};
    }
    return stack->data[stack->count - 1];
}
