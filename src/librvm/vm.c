//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VM *vm_init(size_t stack_size, size_t heap_size) {
    VM *vm = malloc(sizeof(VM));
    if (vm == NULL) {
        fprintf(stderr, "Failed to allocate memory for VM.\n");
        exit(1);
    }

    vm->memory_size = stack_size + heap_size;
    vm->memory = malloc(vm->memory_size);
    if (vm->memory == NULL) {
        fprintf(stderr, "Failed to allocate memory for VM memory.\n");
        free(vm);
        exit(1);
    }

    // Program is stored before the stack btw
    size_t program_size = vm->memory_size - stack_size - heap_size;

    // Stack starts at (program_size + stack_size - 1) and grows downward
    vm->stack_size = stack_size;
    vm->stack_base = vm->memory + program_size + stack_size - 1;
    vm->sp = vm->stack_base;

    // Heap starts at program_size and grows upward
    vm->heap_size = heap_size;
    vm->heap_base = vm->memory + program_size;

    memset(vm->reg, 0, sizeof(Register)*NUM_GP_REGS);
    vm->pc = vm->memory;

    return vm;
}


void vm_free(VM *vm) {
    if(vm) {
        if(vm->memory) free(vm->memory);
        free(vm);
    }
}


void vm_load(VM *vm, InstructionBuffer *buffer) {

}


void vm_run(VM *vm) {
    while (vm->pc < vm->memory + (vm->memory_size - vm->stack_size - vm->heap_size)) {
        switch (*vm->pc) {
            case HALT: return;
            case NOOP: printf("No operation."); break;
            default: break;
        }
        vm->pc++;
    }
}
