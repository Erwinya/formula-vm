#include "formula_vm.hpp"

#include <cctype>
#include <stdexcept>

namespace formulavm {
namespace {

enum class TokKind {
    End, Number, Ident, Plus, Minus, Star, Slash, Equal, Semi, LParen, RParen, PrintKw
};

struct Token {
    TokKind kind;
    std::string text;
    double number = 0.0;
};

class Lexer {
public:
    explicit Lexer(const std::string &src) : src_(src) {}

    Token next() {
        skip();
        if (pos_ >= src_.size()) return {TokKind::End, ""};
        char c = src_[pos_];
        if (std::isdigit(static_cast<unsigned char>(c)) ||
            (c == '.' && pos_ + 1 < src_.size() &&
             std::isdigit(static_cast<unsigned char>(src_[pos_ + 1])))) {
            return number();
        }
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') return ident();
        ++pos_;
        switch (c) {
            case '+': return {TokKind::Plus, "+"};
            case '-': return {TokKind::Minus, "-"};
            case '*': return {TokKind::Star, "*"};
            case '/': return {TokKind::Slash, "/"};
            case '=': return {TokKind::Equal, "="};
            case ';': return {TokKind::Semi, ";"};
            case '(': return {TokKind::LParen, "("};
            case ')': return {TokKind::RParen, ")"};
            default: throw std::runtime_error(std::string("unexpected character: ") + c);
        }
    }

private:
    const std::string &src_;
    std::size_t pos_ = 0;

    void skip() {
        while (pos_ < src_.size()) {
            char c = src_[pos_];
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
                ++pos_;
                continue;
            }
            if (c == '#') {
                while (pos_ < src_.size() && src_[pos_] != '\n') ++pos_;
                continue;
            }
            break;
        }
    }

    Token number() {
        std::size_t start = pos_;
        while (pos_ < src_.size() &&
               (std::isdigit(static_cast<unsigned char>(src_[pos_])) || src_[pos_] == '.')) {
            ++pos_;
        }
        std::string text = src_.substr(start, pos_ - start);
        return {TokKind::Number, text, std::stod(text)};
    }

    Token ident() {
        std::size_t start = pos_;
        while (pos_ < src_.size() &&
               (std::isalnum(static_cast<unsigned char>(src_[pos_])) || src_[pos_] == '_')) {
            ++pos_;
        }
        std::string text = src_.substr(start, pos_ - start);
        if (text == "print") return {TokKind::PrintKw, text};
        return {TokKind::Ident, text};
    }
};

class Compiler {
public:
    explicit Compiler(const std::string &src) : lex_(src) { advance(); }

    Program compile() {
        Program p;
        while (cur_.kind != TokKind::End) {
            statement(p);
            while (cur_.kind == TokKind::Semi) advance();
        }
        p.code.push_back({Op::Halt, 0.0, ""});
        return p;
    }

private:
    Lexer lex_;
    Token cur_;

    void advance() { cur_ = lex_.next(); }

    void expect(TokKind k) {
        if (cur_.kind != k) throw std::runtime_error("unexpected token: " + cur_.text);
        advance();
    }

    void statement(Program &p) {
        if (cur_.kind == TokKind::PrintKw) {
            advance();
            expression(p);
            p.code.push_back({Op::Print, 0.0, ""});
            return;
        }
        if (cur_.kind == TokKind::Ident) {
            std::string name = cur_.text;
            advance();
            expect(TokKind::Equal);
            expression(p);
            p.code.push_back({Op::StoreVar, 0.0, name});
            return;
        }
        throw std::runtime_error("expected statement");
    }

    void expression(Program &p) {
        term(p);
        while (cur_.kind == TokKind::Plus || cur_.kind == TokKind::Minus) {
            TokKind op = cur_.kind;
            advance();
            term(p);
            p.code.push_back({op == TokKind::Plus ? Op::Add : Op::Sub, 0.0, ""});
        }
    }

    void term(Program &p) {
        factor(p);
        while (cur_.kind == TokKind::Star || cur_.kind == TokKind::Slash) {
            TokKind op = cur_.kind;
            advance();
            factor(p);
            p.code.push_back({op == TokKind::Star ? Op::Mul : Op::Div, 0.0, ""});
        }
    }

    void factor(Program &p) {
        if (cur_.kind == TokKind::Number) {
            p.code.push_back({Op::LoadConst, cur_.number, ""});
            advance();
            return;
        }
        if (cur_.kind == TokKind::Ident) {
            p.code.push_back({Op::LoadVar, 0.0, cur_.text});
            advance();
            return;
        }
        if (cur_.kind == TokKind::LParen) {
            advance();
            expression(p);
            expect(TokKind::RParen);
            return;
        }
        if (cur_.kind == TokKind::Minus) {
            advance();
            factor(p);
            p.code.push_back({Op::LoadConst, -1.0, ""});
            p.code.push_back({Op::Mul, 0.0, ""});
            return;
        }
        throw std::runtime_error("expected expression");
    }
};

}  // namespace

Program compile(const std::string &source) {
    return Compiler(source).compile();
}

VmResult run(const Program & /*program*/) {
    throw std::runtime_error("run() not implemented yet");
}

}  // namespace formulavm
