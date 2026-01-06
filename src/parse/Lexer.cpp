//
// Created by 13041 on 2025/12/25.
//
#include <map>
#include <cassert>
#include "Lexer.h"
using namespace sys;

std::map<std::string, Token::Type> keywords = {
        { "if", Token::If },
        { "else", Token::Else },
        { "while", Token::While },
        { "for", Token::For },
        { "return", Token::Return },
        { "int", Token::Int },
        { "float", Token::Float },
        { "void", Token::Void },
        { "const", Token::Const },
        { "break", Token::Break },
        { "continue", Token::Continue },
};

Token lexer_test::nextToken() {
    assert(loc < input.size());

    // 跳过空格
    while (loc < input.size() && std::isspace(input[loc])) {
        if (input[loc] == '\n')
            locLine++;
        loc++;
    }

    // 遇到结尾
    if (loc >= input.size())
        return Token::End;

    char c = input[loc];

    // 标识符与关键字
    if (std::isalpha(c) || c == '_') {
        std::string name;
        while (loc < input.size() && (std::isalnum(input[loc]) || input[loc] == '_'))
            name += input[loc++];

        if (keywords.count(name))
            return keywords[name];

        return Token(name);
    }

    // 数字
    if (std::isdigit(c) || c == '.') {
        int start = loc;
        bool isFloat = false;

        if (c == '0') {
            if (input[loc + 1] == 'x' || input[loc + 1] == 'X') {
                loc += 2;
                while (std::isxdigit(input[loc]) || input[loc] == '.') {
                    if (input[loc] == '.') {
                        if (isFloat)
                            break;
                        isFloat = true;
                    }
                    loc++;
                }
                if (input[loc] == 'p' || input[loc] == 'P') {
                    isFloat = true;
                    loc++;

                    if (input[loc] == '+' || input[loc] == '-')
                        loc++;

                    while (std::isdigit(input[loc]))
                        loc++;
                }

                std::string raw = input.substr(start, loc - start);
                return isFloat ? Token(strtof(raw.c_str(), nullptr)) : std::stoi(raw, nullptr, /*base = autodetect*/0);
            }
        }

        while (std::isdigit(input[loc]) || input[loc] == '.') {
            if (input[loc] == '.') {
                if (isFloat)
                    break;
                isFloat = true;
            }
            loc++;
        }

        if (input[loc] == 'e' || input[loc] == 'E') {
            isFloat = true;
            loc++;

            if (input[loc] == '+' || input[loc] == '-')
                loc++;

            while (std::isdigit(input[loc]))
                loc++;
        }

        std::string raw = input.substr(start, loc - start);
        return isFloat ? Token(strtof(raw.c_str(), nullptr)) : std::stoi(raw, nullptr, /*base = autodetect*/0);
    }

    // 双字节token
    if (loc + 1 < input.size()) {
        switch (c) {
            case '=':
                if (input[loc + 1] == '=') { loc += 2; return Token::Eq; }
                break;
            case '>':
                if (input[loc + 1] == '=') { loc += 2; return Token::Ge; }
                break;
            case '<':
                if (input[loc + 1] == '=') { loc += 2; return Token::Le; }
                break;
            case '!':
                if (input[loc + 1] == '=') { loc += 2; return Token::Ne; }
                break;
            case '+':
                if (input[loc + 1] == '=') { loc += 2; return Token::PlusEq; }
                break;
            case '-':
                if (input[loc + 1] == '=') { loc += 2; return Token::MinusEq; }
                break;
            case '*':
                if (input[loc + 1] == '=') { loc += 2; return Token::MulEq; }
                break;
            case '/':
                if (input[loc + 1] == '=') { loc += 2; return Token::DivEq; }
                // 注释处理1
                if (input[loc + 1] == '/') {
                    for (; loc < input.size(); loc++) {
                        if (input[loc] == '\n')
                            return nextToken();
                    }
                }
                // 注释处理2 跳过/**/之间的所有注释
                if (input[loc + 1] == '*') {
                    loc += 2;
                    for (; loc < input.size(); loc++) {
                        if (input[loc] == '*' && input[loc + 1] == '/') {
                            loc += 2;
                            return nextToken();
                        }
                    }
                }
                break;
            case '%':
                if (input[loc + 1] == '=') { loc += 2; return Token::ModEq; }
                break;
            case '&':
                if (input[loc + 1] == '&') { loc += 2; return Token::And; }
                break;
            case '|':
                if (input[loc + 1] == '|') { loc += 2; return Token::Or; }
                break;
            default:
                break;
        }
    }

    // 单字符token
    switch (c) {
        case '+': loc++; return Token::Plus;
        case '-': loc++; return Token::Minus;
        case '*': loc++; return Token::Mul;
        case '/': loc++; return Token::Div;
        case '%': loc++; return Token::Mod;
        case ';': loc++; return Token::Semicolon;
        case '=': loc++; return Token::Assign;
        case '!': loc++; return Token::Not;
        case '(': loc++; return Token::LPar;
        case ')': loc++; return Token::RPar;
        case '[': loc++; return Token::LBrak;
        case ']': loc++; return Token::RBrak;
        case '<': loc++; return Token::Lt;
        case '>': loc++; return Token::Gt;
        case ',': loc++; return Token::Comma;
        case '{': loc++; return Token::LBrace;
        case '}': loc++; return Token::RBrace;
        default:
            assert(false);
    }
}
