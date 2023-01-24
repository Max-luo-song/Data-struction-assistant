#ifndef BINODE_H
#define BINODE_H
typedef char ElemType;
typedef struct BiNode
{
    ElemType data;
    BiNode *lchild, *rchild;
}*BiTree;

#endif