# formula-vm

Tiny expression language compiled to bytecode and executed on a stack VM (**C++17**).

Language sketch:

- `x = 1 + 2 * 3`
- `print x`
- comments with `#`

## Status

Public header and `compile()` bytecode compiler are in place. VM `run()`, CLI, and build scripts will land in follow-up commits.

## Library (so far)

```cpp
#include "formula_vm.hpp"

auto program = formulavm::compile("x = 1 + 2 * 3\nprint x\n");
// formulavm::run(program) coming next
```

## Requirements

- C++17 compiler

## License

MIT
