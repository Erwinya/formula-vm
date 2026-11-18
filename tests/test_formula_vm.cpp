#include "formula_vm.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

namespace {

int fails = 0;

void expect(bool cond, const std::string &msg) {
    if (!cond) {
        std::cerr << "FAIL: " << msg << '\n';
        ++fails;
    }
}

bool near(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

}  // namespace

int main() {
    {
        auto r = formulavm::evaluate("print 1 + 2 * 3\n");
        expect(r.printed.size() == 1 && near(r.printed[0], 7.0), "precedence 1+2*3");
    }
    {
        auto r = formulavm::evaluate("print (1 + 2) * 3\n");
        expect(r.printed.size() == 1 && near(r.printed[0], 9.0), "parentheses");
    }
    {
        auto r = formulavm::evaluate("print -2 * 3\n");
        expect(r.printed.size() == 1 && near(r.printed[0], -6.0), "unary minus");
    }
    {
        auto r = formulavm::evaluate("# comment\nx = 4\nprint x\n");
        expect(r.printed.size() == 1 && near(r.printed[0], 4.0), "assignment + comment");
        expect(near(r.vars["x"], 4.0), "var retained");
    }
    {
        formulavm::Variables seed{{"rate", 1.5}, {"qty", 10.0}};
        auto r = formulavm::evaluate("print rate * qty\n", seed);
        expect(r.printed.size() == 1 && near(r.printed[0], 15.0), "seeded variables");
    }
    {
        auto prog = formulavm::compile("print a + 1\n");
        formulavm::Variables seed{{"a", 41.0}};
        auto r = formulavm::run(prog, seed);
        expect(r.printed.size() == 1 && near(r.printed[0], 42.0), "run with seed");
    }
    {
        bool threw = false;
        try {
            formulavm::evaluate("print missing\n");
        } catch (const std::exception &) {
            threw = true;
        }
        expect(threw, "undefined variable throws");
    }
    {
        bool threw = false;
        try {
            formulavm::evaluate("print 1 / 0\n");
        } catch (const std::exception &) {
            threw = true;
        }
        expect(threw, "division by zero throws");
    }
    {
        bool threw = false;
        try {
            formulavm::evaluate("print (\n");
        } catch (const std::exception &) {
            threw = true;
        }
        expect(threw, "syntax error throws");
    }

    if (fails) {
        std::cerr << fails << " assertion(s) failed\n";
        return 1;
    }
    std::cout << "test_formula_vm: ok\n";
    return 0;
}
