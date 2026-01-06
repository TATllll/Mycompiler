//
// Created by 13041 on 2026/1/6.
//

// main.cpp
#include "../../src/parse/Lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace sys;

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// 辅助函数：打印 Token
void printToken(const sys::Token& tok) {
    using T = sys::Token::Type;
    switch (tok.type) {
        case T::LInt:
            std::cout << "LInt(" << tok.vi << ")";
            break;
        case T::LFloat:
            std::cout << "LFloat(" << tok.vf << ")";
            break;
        case T::Ident:
            std::cout << "Ident(" << tok.vs << ")";
            break;

            // 运算符
        case T::Plus:       std::cout << "'+'"; break;
        case T::Minus:      std::cout << "'-'"; break;
        case T::Mul:        std::cout << "'*'"; break;
        case T::Div:        std::cout << "'/'"; break;
        case T::Mod:        std::cout << "'%'"; break;
        case T::PlusEq:     std::cout << "'+='"; break;
        case T::MinusEq:    std::cout << "'-='"; break;
        case T::MulEq:      std::cout << "'*='"; break;
        case T::DivEq:      std::cout << "'/='"; break;
        case T::ModEq:      std::cout << "'%='"; break;
        case T::Le:         std::cout << "'<='"; break;
        case T::Ge:         std::cout << "'>='"; break;
        case T::Gt:         std::cout << "'>'"; break;
        case T::Lt:         std::cout << "'<'"; break;
        case T::Eq:         std::cout << "'=='"; break;
        case T::Ne:         std::cout << "'!='"; break;
        case T::And:        std::cout << "'&&'"; break;
        case T::Or:         std::cout << "'||'"; break;
        case T::Semicolon:  std::cout << "';'"; break;
        case T::Assign:     std::cout << "'='"; break;
        case T::Not:        std::cout << "'!'"; break;
        case T::LPar:       std::cout << "'('"; break;
        case T::RPar:       std::cout << "')'"; break;
        case T::LBrak:      std::cout << "'['"; break;
        case T::RBrak:      std::cout << "']'"; break;
        case T::LBrace:     std::cout << "'{'"; break;
        case T::RBrace:     std::cout << "'}'"; break;
        case T::Comma:      std::cout << "','"; break;

            // 关键字
        case T::If:       std::cout << "if"; break;
        case T::Else:     std::cout << "else"; break;
        case T::For:      std::cout << "for"; break;
        case T::While:    std::cout << "while"; break;
        case T::Continue: std::cout << "continue"; break;
        case T::Break:    std::cout << "break"; break;
        case T::Return:   std::cout << "return"; break;
        case T::Void:     std::cout << "void"; break;
        case T::Int:      std::cout << "int"; break;
        case T::Float:    std::cout << "float"; break;
        case T::Const:    std::cout << "const"; break;

        case T::End:
            std::cout << "End";
            break;

        default:
            std::cout << "Unknown";
    }
}

int main() {
    try {
        std::string source = readFile("D:\\desktop\\bc\\Compiler\\myCompiler\\test\\c_file\\sum.txt");
        sys::lexer_test lexer(std::move(source));

        std::cout << "Lexing file: test/c_file/sum.txt\n";
        std::cout << "----------------------------------------\n";

        while (true) {
            sys::Token tok = lexer.nextToken();
            printToken(tok);
            std::cout << "\n";

            if (tok.type == sys::Token::Type::End) {
                break;
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}