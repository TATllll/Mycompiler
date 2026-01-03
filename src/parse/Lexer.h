//
// Created by 13041 on 2025/12/25.
//

#ifndef MYCOMPILER_LEXER_H
#define MYCOMPILER_LEXER_H

#include <string>
#include <cstring>
#include <utility>
#include <vector>

namespace sys {

    // Token类，是一个 词法单元
    // 如果是具体值，需要把值存储起来，如果是标识符，把名称存储起来
    struct Token {
        enum Type {
            // 具体值 与 变量标识符
            LInt, LFloat, Ident,

            // 运算符号
            Plus, Minus, Mul, Div, Mod,
            PlusEq, MinusEq, MulEq, DivEq, ModEq,
            Le, Ge, Gt, Lt, Eq, Ne,                   // <= >= > < == !=
            And, Or, Semicolon, Assign, Not,          // && || ; = !
            LPar, RPar, LBrak, RBrak, LBrace, RBrace, // () [] {}
            Comma,                                    // ,

            // 关键字
            If, Else, For, While, Continue, Break, Return,
            Void, Int, Float, Const,

            // 结束符号
            End
        } type;

        union{
            int vi;
            float vf;
            char *vs;
        };

        Token(Type t) : type(t) {}
        Token(int i) : type(Type::LInt), vi(i){}
        Token(float f) : type(Type::LFloat), vf(f){}
        Token(const std::string &str) : type(Type::Ident) {
            std::strcpy(vs, str.c_str());
        }

    };

    class Lexer{
        std::string input;
        size_t loc; // 当前位置
        size_t locLine;//当前行数

    public:
        Lexer(std::string in) : input(std::move(in)){
            loc = 0, locLine = 1;
        }

        // 获取下一个token
        Token nextToken();
    };
}
#endif //MYCOMPILER_LEXER_H
