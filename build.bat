@echo off
setlocal
where g++ >nul 2>&1
if errorlevel 1 (
  echo g++ not found. Install LLVM-MinGW or MSYS2, then re-run build.bat
  exit /b 1
)
if not exist build mkdir build
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude src\main.cpp src\formula_vm.cpp -o build\formula-vm.exe
if errorlevel 1 exit /b 1
echo Built build\formula-vm.exe

if /I "%~1"=="test" (
  g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude tests\test_formula_vm.cpp src\formula_vm.cpp -o build\test_formula_vm.exe
  if errorlevel 1 exit /b 1
  build\test_formula_vm.exe
  if errorlevel 1 exit /b 1
  echo Tests passed.
  goto :eof
)

echo Example: build\formula-vm.exe --file samples\demo.fvm
echo Test:    build.bat test
endlocal
