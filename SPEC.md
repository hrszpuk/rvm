# Specification for RVM
RVM is a stack-based virtual machine.

# Architecture

## Stacks

### Value stack

### Call stack

## Instruction set
The instruction set will be 2 bytes large. This will be more than enough room for all the instructions we want.

The following are examples of instructions the VM may interpret:
``` 
halt            // Stop program

// Data operations
load            // Load data onto stack
store           // Store data onto heap

// Arithmetric
add             // Add top two values on the stack
mul             // Multiply top two values on the stack
sub             // Subtract top two values on the stack
div             // Divide top two values on the stack
mod             // Modulo top two values on the stack
```

# Resources
- https://dev.to/lexplt/understanding-bytecode-interpreters-eig
- https://dev.to/lexplt/parallelizing-a-bytecode-interpreter-58m8
- https://craftinginterpreters.com/