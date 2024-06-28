//
// Created by hrs on 24/01/24.
//

#include "headers/stack.h"

#include <stdio.h>
#include <stdlib.h>

Stack* CreateStack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    stack->data = malloc(sizeof(StackValue) * capacity);
    stack->capacity = capacity;
    stack->count = 0;
    stack->growthFactor = 2;
    return stack;
}

StackValue PopStack(Stack* stack) {
    StackValue data = TopStack(stack);
    stack->count--;
    return data;
}

void PushStack(Stack* stack, StackValue data) {
    if (stack->count == stack->capacity) {
        GrowStack(stack);
    }
    stack->data[stack->count] = data;
    stack->count++;
}

void FreeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

void PrintStack(Stack* stack) {
    printf("Stack dump:\n");
    for (int i = 0; i < stack->count; i++) {
        printf("%d: %p %d\n", i, stack->data + i, stack->data[i].value.i32);
    }
    printf("Total stack size: %d (capacity %d)\n", stack->count, stack->capacity);
}

void GrowStack(Stack* stack) {
    stack->capacity *= stack->growthFactor;
    stack->data = realloc(stack->data, sizeof(StackValue) * stack->capacity);
}

void ClearStack(Stack* stack) {
    stack->count = 0;
}

bool IsEmptyStack(Stack* stack) {
    return stack->count == 0;
}

StackValue TopStack(Stack* stack) {
    if (stack->count == 0) {
        return (StackValue){IT_void, {.i32 = 0}};
    }
    return stack->data[stack->count - 1];
}
