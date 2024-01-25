# Specification for RVM
RVM is a stack-based virtual machine.

# Architecture

## Stacks

### Value stack

### Call stack

## Instruction set
The instruction set will be 1 bytes large. This will be more than enough room for all the instructions we want.

The following are examples of instructions the VM may interpret:
``` 
halt            // Stop program
noop            // No operation

// Data operations
load            // Load data from local heap
gload           // Load data from global heap
store           // Store data onto local heap
gstore          // Store data onto global heap

push            // Push data onto stack
pop             // Pop data off stack
dup             // Duplicate top value on stack
swap            // Swap top two values on stack
const           // Push constant onto stack

// Arithmetric
// The following instructions pop two values off the stack and push the result onto the stack
add             // Add
sub             // Subtract
mul             // Multiply
div             // Divide
mod             // Modulo

// Bitwise
// The following instructions pop two values off the stack and push the result onto the stack
and             // Bitwise and
or              // Bitwise or
xor             // Bitwise xor
not             // Bitwise not
shl             // Bitwise shift left
shr             // Bitwise shift right

// Logicial
// The following instructions pop two values off the stack and push the result onto the stack
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
call <name>     // Call subroutine
ret             // Return from function

// I/O
out           // Print single value
in            // Read single value

// Subroutines
begin <name>    // Begin subroutine
end             // End subroutine

// Loading other rvm scripts
preload <path>  // Load rvm script, NOTE: the order of the preload instructions is important
```

# Resources
- https://dev.to/lexplt/understanding-bytecode-interpreters-eig
- https://dev.to/lexplt/parallelizing-a-bytecode-interpreter-58m8
- https://craftinginterpreters.com/