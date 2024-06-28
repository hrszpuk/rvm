//
// Created by hrs on 27/06/24.
//

#ifndef RVM_PARSE_H
#define RVM_PARSE_H

#include <stdlib.h>
#include "buffer.h"

typedef struct {
    int index;
    unsigned char* buffer;
    int buffer_size;
    InstructionBuffer* instructions;
} Parser;

Parser* create_parser(unsigned char* buffer, int buffer_size);
void destroy_parser(Parser* p);
void parse(Parser* p);
void parseLine(Parser* p);


#endif //RVM_PARSE_H
