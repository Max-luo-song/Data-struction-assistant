#ifndef BINODE_H
#define BINODE_H
typedef int ElemType;
typedef struct BiNode
{
    ElemType data;
    BiNode *firstchild, *nextsibling;
}*BiTree;

#endif