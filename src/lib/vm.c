//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>

#include "headers/translator.h"

VM* CreateVM(const int stackCapacity, const int bufferCapacity) {
    VM* vm = malloc(sizeof(VM));
    vm->stack = CreateStack(stackCapacity);
    vm->buffer = CreateBuffer(bufferCapacity);
    vm->ip = 0;
    vm->state = 0;
    vm->debug = 0;
    return vm;
}

// NOTE(hrs): bytecode buffer must contain TranslationResult data
void LoadBytecode(VM* vm, Buffer* bytecode) {
    DestroyBuffer(vm->buffer);
    vm->buffer = bytecode;
}

void DestroyVM(VM* vm) {
    DestroyBuffer(vm->buffer);
    FreeStack(vm->stack);
    free(vm);
}

void RunVM(VM* vm) {
    vm->state = 0;

    while (vm->state == 0) {
        if (vm->ip >= vm->buffer->count) {
            vm->state = 2;
            break;
        }

        // Fetch instruction, apply it, and increment instruction pointer.
        Instruction* instruction = GetBufferData(vm->buffer, vm->ip);
        switch (instruction->opcode) {
            case HALT: {
                vm->state = 2;
                break;
            }
            case NOOP: {
                break;
            }
            case PUSH: {
                // TODO: support other types
                int value = atoi(instruction->arg);
                PushStack(vm->stack, &value);
                break;
            }
            case POP: {
                PopStack(vm->stack);
                break;
            }
            case ADD: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a + *b;
                PushStack(vm->stack, a);
                free(a);
                free(b);
                break;
            }
            case SUB: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a - *b;
                PushStack(vm->stack, a);
                free(a);
                free(b);
                break;
            }
            case DIV: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a / *b;
                PushStack(vm->stack, a);
                free(a);
                free(b);
                break;
            }
            case MUL: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a * *b;
                PushStack(vm->stack, a);
                free(a);
                free(b);
                break;
            }
            case MOD: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a % *b;
                PushStack(vm->stack, a);
                free(a);
                free(b);
                break;
            }
            default: {
                printf("Unknown instruction!\n");
                break;
            }
        }
        vm->ip++;
    }
}

void PauseVM(VM* vm) {
    vm->state = 1;
}

void StopVM(VM* vm) {
    vm->state = 2;
    ClearStack(vm->stack);
    ClearBufferData(vm->buffer);
}

void DumpVM(VM* vm) {
    PrintStack(vm->stack);
    printf("Buffer dump:\n");
    for (int i = 0; i < vm->buffer->count; i++) {
        printf("%d: %p\n", i, GetBufferData(vm->buffer, i));
    }
    printf("Instruction Pointer: %d\n", vm->ip);
    printf("State: %d\n", vm->state);
    printf("Debug: %d\n", vm->debug);
}

