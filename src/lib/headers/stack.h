//
// Created by hrs on 24/01/24.
//

#ifndef STACK_H
#define STACK_H

typedef struct {} Stack;

Stack* CreateStack();
void* PopStack();
void PushStack(Stack*);
void FreeStack(Stack*);

#endif //STACK_H
