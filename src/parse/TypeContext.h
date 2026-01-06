//
// Created by 13041 on 2025/12/25.
//

#ifndef MYCOMPILER_TYPECONTEXT_H
#define MYCOMPILER_TYPECONTEXT_H
#include <unordered_set>

#include "Type.h"
#include "unordered_set"

namespace sys{
    //这部分需要做到维护一个 已有类型 的哈希表，能够创建一个类型，如果表中有，则返回唯一的那一个，否则才会新建。
    class TypeContext{
        struct Hash {
            size_t operator()(Type *ty) const {
                return ty->getHash();
            }
        };
        struct Eq {
            bool operator()(Type *a, Type *b) const {
                return a && b && a->equals(b);
            }
        };


    public:
        std::unordered_set<Type *, Hash, Eq> content;

        template<class T, class... Args>
        T* create(Args&&... args) {  // Args&& 是转发引用
            auto ptr = new T(std::forward<Args>(args)...);
            if (auto [it, absent] = content.insert(ptr); !absent) {
                delete ptr;
                return static_cast<T*>(*it);  // 或 cast<T>(*it)，如果你保留 cast
            }
            return ptr;
        }
        // 安全删除
        ~TypeContext() {
            for (auto x: content)
                delete x;
        }
    };
}


#endif //MYCOMPILER_TYPECONTEXT_H
