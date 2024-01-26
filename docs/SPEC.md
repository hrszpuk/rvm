# Specification for RVM
RVM is a stack-based virtual machine.

# Architecture

## Stacks

### Value stack

### Call stack

## Instruction set
The instruction set will be 1 byte large. This will be more than enough room for all the instructions we want.

The following are examples of instructions the VM may interpret:
``` 
halt            // Stop program
noop            // No operation

// Data operations
// Loading using an index is faster than loading using an id
load <index>    // Load data from heap
store <index>   // Store data in heap

// Loading using an id is more convenient than loading using an index
// The id is a string that is mapped to an index
// This is better for debugging
vload <id>      // Load data from heap
vstore <id>     // Store data in heap

// The local heap is a stack that is local to the current subroutine
// The global heap is a stack that is global to the entire program
local           // Switch to local heap
global          // Switch to global heap

push            // Push data onto stack
pop             // Pop data off stack
dup             // Duplicate top value on stack
swap            // Swap top two values on stack

// Arithmetric
// The following instructions pop two values off the stack and push the result onto the stack 
add             // Add
sub             // Subtract
mul             // Multiply
div             // Divide
mod             // Modulo

// Bitwise
// The following instructions pop two values off the stack and push the result onto the stack (except not)
and             // Bitwise and
or              // Bitwise or
xor             // Bitwise xor
not             // Bitwise not
shl             // Bitwise shift left
shr             // Bitwise shift right

// Logicial
// The following instructions pop two values off the stack and push the result onto the stack (except lnot)
land            // Logical and
lor             // Logical or
lnot            // Logical not

// Comparisons
// The following instructions pop two values off the stack and push the result onto the stack
eq              // Equal
ne              // Not equal
lt              // Less than
le              // Less than or equal
gt              // Greater than
ge              // Greater than or equal

// Control flow
jmp             // Jump
jmpc            // Jump if condition (top of stack) is true or 1

// I/O
out           // Print single value
in            // Read single value

// Subroutines
begin <name>    // Begin subroutine
end             // End subroutine
call <name>     // Call subroutine
ret             // Return from subroutine
```

### Idioms

**Idiom 1: loops**
```
// for i in range(0, 10):
//     print(i)
push 0
store i
push 10
store n
loop:
    load i
    load n
    lt
    jmpc end
    load i
    out
    push 1
    load i
    add
    store i
    jmp loop
end:
```

**Idiom 2: subroutines**
```
// def foo():
//     print("foo")
//     x = bar()
//     if x: return
//     print("foo")
begin foo
    push 'f'
    out
    push 'o'
    out
    push 'o'
    out
    call bar
    jmpc end
    push 'f'
    out
    push 'o'
    out
    push 'o'
    out
end
```

### Instruction Value Consumptions
Some instructions consume values from the stack.
The values consumed are no longer available on the stack after the instruction is executed.
Some instructions consume values from the stack and push a result onto the stack.

The following is a list of instructions, the number of values they consume from the stack and the number of values they push onto the stack:
```
halt            // 0, 0
noop            // 0, 0
load            // 0, 1
store           // 1, 0
vload           // 0, 1
vstore          // 1, 0
local           // 0, 0
global          // 0, 0
push            // 0, 1
pop             // 1, 0
dup             // 1, 2
swap            // 2, 2
add             // 2, 1
sub             // 2, 1
mul             // 2, 1
div             // 2, 1
mod             // 2, 1
and             // 2, 1
or              // 2, 1
xor             // 2, 1
not             // 1, 1
shl             // 2, 1
shr             // 2, 1
land            // 2, 1
lor             // 2, 1
lnot            // 1, 1
eq              // 2, 1
ne              // 2, 1
lt              // 2, 1
le              // 2, 1
gt              // 2, 1
ge              // 2, 1
jmp             // 0, 0
jmpc            // 1, 0
out             // 1, 0
in              // 0, 1
begin           // 0, 0
end             // 0, 0
call            // 0, 0
ret             // 0, 0
```

# Resources
- https://dev.to/lexplt/understanding-bytecode-interpreters-eig
- https://dev.to/lexplt/parallelizing-a-bytecode-interpreter-58m8
- https://craftinginterpreters.com/