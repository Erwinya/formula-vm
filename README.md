# formula-vm

Tiny expression language compiled to bytecode and executed on a stack VM (**C++17**).

Language sketch:

- `x = 1 + 2 * 3`
- `print x`
- comments with `#`

## Status

Public header with opcodes, `Program`, and `VmResult` is in place. Compiler, VM, CLI, and build scripts will land in follow-up commits.

## Library (so far)

```cpp
#include "formula_vm.hpp"

// formulavm::Op, Instruction, Program, VmResult
// formulavm::compile / formulavm::run (coming next)
```

## Requirements

- C++17 compiler

## License

MIT
