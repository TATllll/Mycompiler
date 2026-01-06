//
// Created by 13041 on 2025/12/25.
//

#ifndef MYCOMPILER_ASTNODE_H
#define MYCOMPILER_ASTNODE_H

#include "Type.h"

namespace sys {

class ASTNode {
protected:
    const int id;
public:
    Type * type = nullptr;

    int getID(){return id;}

    ASTNode(int id) : id(id){}
    virtual ~ASTNode(){}
};

template<class T, int NodeId>
class ASTNodeImpl : ASTNode{
public:
    //检查两个节点类型是否相同
    static bool classof(ASTNode *node){
        return node->getID() == NodeId;
    }
    ASTNodeImpl() : ASTNode(NodeId){}
};

class IntNode : ASTNodeImpl<IntNode, 0>{
    int value;
    IntNode(int value) : value(value){}
};

class FloatNode : ASTNodeImpl<FloatNode, 1>{
    float value;
    FloatNode(float value) : value(value){}
};




};
#endif //MYCOMPILER_ASTNODE_H
