#include "formula_vm.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace {

std::string read_all(std::istream &in) {
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

bool parse_var(const std::string &spec, std::string &name, double &value) {
    const auto eq = spec.find('=');
    if (eq == std::string::npos || eq == 0) return false;
    name = spec.substr(0, eq);
    const std::string raw = spec.substr(eq + 1);
    if (name.empty() || raw.empty()) return false;
    for (char c : name) {
        if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '_')) return false;
    }
    if (!std::isalpha(static_cast<unsigned char>(name[0])) && name[0] != '_') return false;
    try {
        size_t idx = 0;
        value = std::stod(raw, &idx);
        if (idx != raw.size()) return false;
    } catch (...) {
        return false;
    }
    return true;
}

}  // namespace

int main(int argc, char **argv) {
    const char *path = nullptr;
    formulavm::Variables vars;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            path = argv[++i];
        } else if (arg == "--var" && i + 1 < argc) {
            std::string name;
            double value = 0.0;
            if (!parse_var(argv[++i], name, value)) {
                std::cerr << "invalid --var (expected NAME=NUMBER)\n";
                return 2;
            }
            vars[name] = value;
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "Usage: formula-vm [--file path] [--var NAME=VALUE]...\n"
                      << "Tiny expression VM. Statements: x = expr; print expr\n"
                      << "Seed variables with repeatable --var flags.\n";
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

        formulavm::VmResult result = formulavm::evaluate(source, vars);
        for (double v : result.printed) {
            std::cout << v << '\n';
        }
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "error: " << ex.what() << '\n';
        return 1;
    }
}
