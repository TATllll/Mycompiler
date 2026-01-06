//
// Created by 13041 on 2025/12/25.
//

#ifndef MYCOMPILER_TYPE_H
#define MYCOMPILER_TYPE_H

#include <string>
#include <vector>

namespace sys{
    // Type要求记录所有的类型，有int float void pointer array
    // 基类
    class Type{
    private:
        size_t id;
    public:
        size_t getId() const {return id;}
        explicit Type(int id) : id(id){}
        virtual ~Type() = default;

        virtual std::string toString() const = 0;
        virtual size_t getHash() const = 0;
        virtual bool equals(const Type* other) const = 0;
    };

    template<class T, int typeId>
    class TypeImpl : public Type{
    public:
        static bool classof(Type *ty) {
            return ty->getId() == typeId;
        }
        virtual size_t getHash() const override{
            return typeId;
        }
        bool equals(const Type* other) const override {
            return this->getId() == other->getId(); // 对于 IntType/FloatType 足够
        }

        TypeImpl() : Type(typeId){}
    };

    class IntType : public TypeImpl<IntType, 0>{
    public:
        std::string toString() const override{
            return "int";
        }
    };

    class VoidType : public TypeImpl<VoidType, 1>{
    public:
        std::string toString() const override{
            return "void";
        }
    };

    class FloatType : public TypeImpl<FloatType, 2>{
    public:
        std::string toString() const override{
            return "float";
        }
    };

    class PointerType : public TypeImpl<PointerType, 3> {
    public:
        Type *pointee;
        std::string toString() const override{
            return pointee->toString() + "*";
        }
        size_t getHash() const override{
            return (getId() << 4) + pointee->getHash();
        }
        bool equals(const Type* other) const{
            auto o = dynamic_cast<const PointerType*>(other);
            return o != nullptr && o->pointee->equals(this->pointee);
        }
        PointerType(Type *pointee) : pointee(pointee){}
    };

    class ArrayType : public TypeImpl<ArrayType, 4>{
    public:
        Type *type;
        std::vector<int> dim;
        std::string toString() const override{
            std::string res = type->toString();
            for(int i : dim){
                res += "[" + std::to_string(i) + "]";
            }
            return res;
        }
        size_t getHash() const override{
            assert(type != nullptr); // 防御性编程
            assert(!dim.empty());    // 如果允许空维度，去掉这行
            size_t hash = type->getHash() << 4;
            for(int i : dim){
                hash *= i;
            }
            return hash;
        }
        bool equals(const Type* other) const{
            //换成动态转换
            auto o = dynamic_cast<const ArrayType*>(other);
            if(o == nullptr || !type->equals(o->type) || dim.size() != o->dim.size())
                return false;
            for(int i = 0; i < dim.size(); i++)
                if(dim[i] != o->dim[i])
                    return false;
            return true;
        }
        //? 需要按值接受维度
        ArrayType(Type * type, std::vector<int> dim) : type(type), dim(std::move(dim)){}
    };

    class FunctionType : public TypeImpl<FunctionType, 5>{
    public:
        Type *returnType;
        std::vector<Type*> params;

        std::string toString() const override{
            std::string res = returnType->toString();
            res += "(";
            for(auto param : params){
                if(param != params[0])
                    res += ", ";
                res += param->toString();
            }
            res += ")";
            return res;
        }
        size_t getHash() const override{
            size_t hash = returnType->getHash();
            for(auto param : params){
                hash = (hash << 1) + param->getHash();
            }
            return hash;
        }
        bool equals(const Type* other) const{
            auto o = dynamic_cast<const FunctionType*>(other);
            if(o == nullptr || !returnType->equals(o->returnType) || o->params.size() != params.size())
                return false;
            for(int i = 0; i < params.size(); i++){
                if(!params[i]->equals(o->params[i]))
                    return false;
            }
            return true;
        }

        FunctionType(Type *returnType, std::vector<Type*>& params) : returnType(returnType), params(params){}
    };
}
#endif //MYCOMPILER_TYPE_H
