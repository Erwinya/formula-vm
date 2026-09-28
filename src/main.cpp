#include "formula_vm.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace {

std::string read_all(std::istream &in) {
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

}  // namespace

int main(int argc, char **argv) {
    const char *path = nullptr;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            path = argv[++i];
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: formula-vm [--file path]\n"
                      << "Tiny expression VM. Statements: x = expr; print expr\n";
            return 0;
        } else {
            std::cerr << "unknown argument: " << arg << '\n';
            return 2;
        }
    }

    try {
        std::string source;
        if (path) {
            std::ifstream in(path);
            if (!in) {
                std::cerr << "cannot open " << path << '\n';
                return 2;
            }
            source = read_all(in);
        } else {
            source = read_all(std::cin);
        }

        formulavm::Program prog = formulavm::compile(source);
        formulavm::VmResult result = formulavm::run(prog);
        for (double v : result.printed) {
            std::cout << v << '\n';
        }
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "error: " << ex.what() << '\n';
        return 1;
    }
}
