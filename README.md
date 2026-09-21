# formula-vm

Tiny expression language compiled to bytecode and executed on a stack VM (**C++17**).

Language sketch:

- `x = 1 + 2 * 3`
- `print x`
- comments with `#`

## Status

Project scaffolding is in place. Compiler, VM, CLI, and build scripts will land in follow-up commits.

## Planned usage

```powershell
.\build.bat
.\build\formula-vm.exe --file samples\demo.fvm
```

## Requirements

- C++17 compiler

## License

MIT
