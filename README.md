# formula-vm

Tiny expression language compiled to bytecode and executed on a stack VM (**C++17**).

Language sketch:

- `x = 1 + 2 * 3`
- `print x`
- comments with `#`

## Status

Library (`compile` / `run`) and CLI entrypoint are in place. Makefile / `build.bat` will land in a follow-up commit.

## Build (manual)

```powershell
g++ -std=c++17 -I include -o formula-vm.exe src\formula_vm.cpp src\main.cpp
.\formula-vm.exe --file samples\demo.fvm
```

Or pipe source on stdin:

```powershell
"x = 2 + 3`nprint x" | .\formula-vm.exe
```

## Library

```cpp
#include "formula_vm.hpp"

auto program = formulavm::compile("x = 1 + 2 * 3\nprint x\n");
auto result = formulavm::run(program);
```

## Requirements

- C++17 compiler

## License

MIT
