#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace formulavm {

enum class Op : uint8_t {
    LoadConst,
    LoadVar,
    StoreVar,
    Add,
    Sub,
    Mul,
    Div,
    Print,
    Halt
};

struct Instruction {
    Op op;
    double number = 0.0;   // LoadConst
    std::string name;      // LoadVar / StoreVar
};

struct Program {
    std::vector<Instruction> code;
};

struct VmResult {
    std::vector<double> printed;
    std::unordered_map<std::string, double> vars;
};

/// Compile source into bytecode (assignments, print, + - * /).
Program compile(const std::string &source);

/// Execute a compiled program. Implemented in a follow-up commit.
VmResult run(const Program &program);

}  // namespace formulavm
