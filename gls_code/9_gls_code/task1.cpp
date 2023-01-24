/*
    程序描述：先序序列建树，空孩子用#，输出中序序列(递归)，层序遍历，二叉树深度
*/

#include<bits/stdc++.h>
// 此处为节省篇幅，使用外部文件，模块化栈和队列结构
#include"BiNode.h"
#include"queue.cpp"

// function:根据前序序列建立二叉树(递归)
void CreateTree(BiTree &T) {
    char ch;
    std::cin >> ch;
    if (ch == '#') {
        T = NULL;
    }
    else if (ch == '\n')
        return ;
    else {
        T = (BiTree)malloc(sizeof(BiNode));
        if (T == NULL) {
            std::cout << "create tree node fail" << std::endl;
            system("pause");
            exit(-1);
        }
        T->data = ch;
        CreateTree(T->lchild);
        CreateTree(T->rchild);
    }
}

// function:中序遍历-递归形式
void Inorder_traverse_recursion(BiTree tree) {
    if (tree != NULL) {
        Inorder_traverse_recursion(tree->lchild);
        std::cout << tree->data;
        Inorder_traverse_recursion(tree->rchild);
    }
}

// function:层次遍历
void Level_traverse(BiTree tree) {
    Queue queue;
    Init_queue(queue);
    BiTree p = tree;
    Queue_push(queue, p);
    while (!Queue_empty(queue)) {
        int size = queue.length;
        while (size--) {
            Queue_pop(queue, p);
            std::cout << p->data;
            if (p->lchild)
                Queue_push(queue, p->lchild);
            if (p->rchild)
                Queue_push(queue, p->rchild);
        }
        std::cout << std::endl;
    }
    Freespace_queue(queue);
}

// funciton:返回树的深度——递归法
int Depth(BiTree tree) {
    if (tree == NULL)
        return 0;
    int left = Depth(tree->lchild);
    int right = Depth(tree->rchild);
    if (left > right)
        return left+1;
    else
        return right+1;
}

// function:输出叶子节点
/*
    算法：要求从左往右输出，使用前序遍历方式-递归实现
          叶子节点含义为左右子节点为空
*/
void Print_leafnode(BiTree tree) {
    if (tree != NULL) {
        if (tree->lchild == NULL && tree->rchild == NULL) {
            std::cout << tree->data;
        }
        Print_leafnode(tree->lchild);
        Print_leafnode(tree->rchild);
    }
}

// function:销毁二叉树，释放二叉树空间
/*
    算法：递归思路，一定要选择后序进行销毁。否则只是部分销毁
*/
void Destory_tree(BiTree &tree) {
    if (tree != NULL) {
        Destory_tree(tree->lchild);
        Destory_tree(tree->rchild);
        free(tree);
        tree = NULL;
    }
}

int main() {
    BiTree tree = NULL;
    std::cout << "请输入树的前序序列，孩子为空为#:";
    CreateTree(tree);
    std::cout << "\n中序遍历-递归结果为：";
    Inorder_traverse_recursion(tree);
    std::cout << "\n层次遍历-结果为：\n";
    Level_traverse(tree);
    std::cout << "\n该树的深度是：";
    int depth = Depth(tree);
    std::cout << depth;
    std::cout << "\n叶子节点从左到右为:";
    Print_leafnode(tree);
    Destory_tree(tree);
    system("pause");
    return 0;
}