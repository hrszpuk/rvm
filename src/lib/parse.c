//
// Created by hrs on 27/06/24.
//

#include "parse.h"

Parser* create_parser(unsigned char* buffer, int buffer_size) {
    Parser* p = malloc(sizeof(Parser));
    p->index = 0;
    p->buffer = buffer;
    p->buffer_size = buffer_size;
    p->instructions = CreateBuffer(20);
    p->error = 0;
    return p;
}

void destroy_parser(Parser* p) {
    free(p);
}

void parse(Parser* p) {
    while (p->index < p->buffer_size) {
        Instruction instr;

        if (HALT <= p->buffer[p->index] && p->buffer[p->index] < NUMBER_OF_OPCODE) {
            // Handle instruction
            instr.instruction = (Opcode) p->buffer[p->index];
            p->index++;
            if(p->index >= p->buffer_size) {
                instr.type = IT_void;
                AddBufferData(p->instructions, instr);
                continue;
            }
            instr.type = p->buffer[p->index] % NUMBER_OF_INSTRUCTION_TYPES;
            p->index++;
            if(p->index >= p->buffer_size || p->buffer[p->index] == '\n') {
                AddBufferData(p->instructions, instr);
                continue;
            }
            instr.arg = parse_arg(p, instr.type);
            AddBufferData(p->instructions, instr);
        } else if (p->buffer[p->index] == 255) {
            if(p->index >= p->buffer_size) {
                printf("Empty directive found during parsing! Terminating.");
                p->error = 1;
                return;
            }

        }
    }
}