# formula-vm

Tiny expression language compiled to bytecode and executed on a stack VM (**C++17**).

Language sketch:

- `x = 1 + 2 * 3`
- `print x`
- comments with `#`

## Status

Ready for use: library, CLI, and build scripts (`Makefile`, `build.bat`).

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

Or pipe source on stdin:

```powershell
"x = 2 + 3`nprint x" | .\build\formula-vm.exe
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
