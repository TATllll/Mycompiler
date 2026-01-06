cmake_minimum_required(VERSION 3.30)
project(myCompiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(myCompiler
        src/parse/Lexer.h
        src/parse/ASTNode.h
        src/parse/Parser.h
        src/parse/Type.h
        src/parse/TypeContext.h
        src/parse/Type.cpp
        src/parse/Lexer.cpp
        src/parse/Parser.cpp
        test/parse/lexer_test.cpp)
