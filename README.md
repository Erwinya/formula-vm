# formula-vm

Tiny expression language compiled to bytecode and executed on a stack VM (**C++17**).

Language sketch:

- `x = 1 + 2 * 3`
- `print x`
- comments with `#`
- operator precedence: `* /` over `+ -`, unary `-`, parentheses

## Status

Library, CLI (`--file`, `--var`), unit tests, and CI.

## Build

```bash
make
./formula-vm --file samples/demo.fvm
```

Windows (MinGW / LLVM):

```bat
build.bat
build\formula-vm.exe --file samples\demo.fvm
```

Seed host variables:

```powershell
.\build\formula-vm.exe --var rate=1.5 --var qty=10
# then type: print rate * qty
```

## Test

```bash
make test
```

```bat
build.bat test
```

## Library

```cpp
#include "formula_vm.hpp"

auto program = formulavm::compile("print rate * qty\n");
formulavm::Variables vars{{"rate", 1.5}, {"qty", 10.0}};
auto result = formulavm::run(program, vars);
// or: auto result = formulavm::evaluate("print rate * qty\n", vars);
```

Exit codes: `0` ok, `1` runtime/compile error, `2` usage/IO.

## Requirements

- C++17 compiler

## License

MIT
