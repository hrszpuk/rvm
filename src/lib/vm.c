//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>

#include "../assembler/headers/translator.h"

// NOTE(hrs): default buffer is NULL and must be set before running the VM. (Temporary, see LoadBytecode).
VM* CreateVM(const int stackCapacity) {
    VM* vm = malloc(sizeof(VM));
    vm->stack = CreateStack(stackCapacity);
    vm->buffer = NULL;
    vm->ip = 0;
    vm->state = 0;
    vm->debug = 0;
    return vm;
}

// NOTE(hrs): bytecode buffer must contain TranslationResult data
void LoadBytecode(VM* vm, InstructionBuffer* bytecode) {
    vm->buffer = bytecode;
}

// NOTE(hrs) instruction buffer is not free'd in DestroyVM
void DestroyVM(VM* vm) {
    FreeStack(vm->stack);
    free(vm);
}

void RunVM(VM* vm) {
    vm->state = 0;

    while (vm->state == 0) {
        if (vm->ip >= vm->buffer->count) {
            StopVM(vm);
            return;
        }

        // Fetch instruction, apply it, and increment instruction pointer.
        Instruction wordbyte = GetBufferData(vm->buffer, vm->ip);
        switch (wordbyte.instruction) {
            case HALT: {
                vm->state = 2;
                break;
            }
            case NOOP: {
                break;
            }
            case PUSH: {
                StackValue value = (StackValue){wordbyte.type, wordbyte.arg};
                PushStack(vm->stack, value);
                break;
            }
            case POP: {
                PopStack(vm->stack);
                break;
            }
            case DUP: {
                PushStack(vm->stack, TopStack(vm->stack));
            }
            case SWAP: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                PushStack(vm->stack, b);
                PushStack(vm->stack, a);
            }
            case ADD: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a + *b;
                PushStack(vm->stack, a);
                //free(a);
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
                //free(a);
                free(b);
                break;
            }
            case MOD: {
                int* a = PopStack(vm->stack);
                int* b = PopStack(vm->stack);
                *a = *a % *b;
                PushStack(vm->stack, a);
                break;
            }
            default: {
                printf("Unknown instruction! %d\n", wordbyte.instruction);
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
    printf("InstructionBuffer dump:\n");
    for (int i = 0; i < vm->buffer->count; i++) {
        Instruction j = GetBufferData(vm->buffer, i);
        printf("%d: {%d, %d, %p}\n", i, j.instruction, j.type, j.arg);
    }
    printf("Instruction Pointer: %d\n", vm->ip);
    printf("State: %d\n", vm->state);
    printf("Debug: %d\n", vm->debug);
}

