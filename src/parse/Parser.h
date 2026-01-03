//
// Created by 13041 on 2025/12/25.
//

#ifndef MYCOMPILER_PARSER_H
#define MYCOMPILER_PARSER_H

#include <string>
#include <utility>

namespace sys{

    class Parser{
    std::string in;
    TypeContext ctx;
    size_t loc;

    public:
        Parser(std::string input, TypeContext &_ctx) : in(std::move(input)), ctx(_ctx){}
        void parse();
    };

}

#endif //MYCOMPILER_PARSER_H
