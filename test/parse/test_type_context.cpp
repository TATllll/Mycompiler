//
// Created by 13041 on 2026/1/6.
//
// test_type_context.cpp
#include <iostream>
#include <cassert>
#include "../../src/parse/TypeContext.h"

using namespace sys;

int main() {
    TypeContext ctx;

    // === 1. 基本类型 ===
    IntType* int1 = ctx.create<IntType>();
    IntType* int2 = ctx.create<IntType>();
    assert(int1 == int2);  // 应该是同一个对象
    std::cout << "✅ Basic types are canonicalized.\n";

    // === 2. 指针类型 ===
    PointerType* p1 = ctx.create<PointerType>(int1);
    PointerType* p2 = ctx.create<PointerType>(int1);
    assert(p1 == p2);
    std::cout << "✅ Pointer types: " << p1->toString() << "\n";

    // 多级指针
    PointerType* pp1 = ctx.create<PointerType>(p1);
    PointerType* pp2 = ctx.create<PointerType>(p1);
    assert(pp1 == pp2);
    std::cout << "✅ Double pointer: " << pp1->toString() << "\n";

    // === 3. 数组类型（注意维度顺序！）===
    std::vector<int> dims34 = {3, 4};
    std::vector<int> dims43 = {4, 3};

    ArrayType* arr34 = ctx.create<ArrayType>(int1, dims34);
    ArrayType* arr34_2 = ctx.create<ArrayType>(int1, dims34);
    ArrayType* arr43 = ctx.create<ArrayType>(int1, dims43);

    assert(arr34 == arr34_2);      // 相同维度 → 同一对象
    assert(arr34 != arr43);        // 不同维度顺序 → 不同对象！
    std::cout << "✅ Array [3][4]: " << arr34->toString() << "\n";
    std::cout << "✅ Array [4][3]: " << arr43->toString() << "\n";

//    // 验证哈希是否不同（可选）
//    assert(arr34->getHash() != arr43->getHash());
//    std::cout << "✅ Array hash distinguishes dimension order.\n";

    // === 4. 函数类型 ===
    std::vector<Type*> params1 = {int1, p1};
    FunctionType* fn1 = ctx.create<FunctionType>(int1, params1);
    FunctionType* fn2 = ctx.create<FunctionType>(int1, params1);

    assert(fn1 == fn2);
    std::cout << "✅ Function type: " << fn1->toString() << "\n";

    // 不同参数数量
    std::vector<Type*> params2 = {int1};
    FunctionType* fn3 = ctx.create<FunctionType>(int1, params2);
    assert(fn1 != fn3);
    std::cout << "✅ Different function signatures are distinct.\n";

    // === 5. 混合类型：数组 of 指针 ===
    ArrayType* arrPtr = ctx.create<ArrayType>(p1, std::vector<int>{5});
    ArrayType* arrPtr2 = ctx.create<ArrayType>(p1, std::vector<int>{5});
    assert(arrPtr == arrPtr2);
    std::cout << "✅ Array of pointers: " << arrPtr->toString() << "\n";

    // === 6. Void 类型 ===
    VoidType* v1 = ctx.create<VoidType>();
    VoidType* v2 = ctx.create<VoidType>();
    assert(v1 == v2);
    std::cout << "✅ Void type: " << v1->toString() << "\n";

    std::cout << "\n🎉 All tests passed!\n";
    return 0;
}