//
// Created by hrs on 27/06/24.
//

#ifndef RVM_PARSE_H
#define RVM_PARSE_H

#include <stdlib.h>
#include "buffer.h"
#include "directive.h"

typedef struct {
    int index;
    unsigned char* buffer;
    int buffer_size;
    DirectiveBuffer* directives;
    InstructionBuffer* instructions;
    int error;
} Parser;

Parser* create_parser(unsigned char* buffer, int buffer_size);
void destroy_parser(Parser* p);
void parse(Parser* p);
void parse_line(Parser* p);


#endif //RVM_PARSE_H
