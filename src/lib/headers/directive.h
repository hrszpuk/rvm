//
// Created by hrs on 01/07/24.
//

#ifndef RVM_DIRECTIVE_H
#define RVM_DIRECTIVE_H

#include "buffer.h"

typedef enum {
    META,           // .meta
    DATA,           // .data
    PROGRAM,        // .program
    SYMBOL,         // .symbol <id> <type> <arg>
    NAME,           // .name <arg>
} DirectiveType;

typedef struct {
    DirectiveType type;
    InstructionType argument_type;
    InstructionArgumentValue argument_value;
} Directive;



#endif //RVM_DIRECTIVE_H
