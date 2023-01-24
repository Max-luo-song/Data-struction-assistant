/*
    程序描述：先序序列建树，空孩子用# 中序遍历(非递归)  二叉树删除  求父节点  求兄弟节点
*/

#include<bits/stdc++.h>
// 此处为节省篇幅，使用外部文件，模块化栈和队列结构
#include"BiNode.h"
#include"stack.cpp"

// function:根据前序序列建立二叉树(递归)
void CreateTree(BiTree &T) {
    char ch;
    std::cin >> ch;
    //fflush(stdin);
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

// function:中序遍历-非递归形式
void Inorder_traverse_unrecursion(BiTree tree) {
    Stack stack;
    Init_stack(stack);
    BiTree p = tree;
    while (!Empty_stack(stack) || p != NULL) {
        if (p != NULL) {
            Stack_push(stack, p);
            p = p->lchild;
        }
        else {
            stack_pop(stack, p);
            std::cout << p->data;
            p = p->rchild;
        }
    }
    Free_space_stack(stack);
}

// function:返回父节点指针
/*
    算法：先序非递归遍历，看每个节点的子节点是否等于target，满足则返回
*/
BiTree Get_parent(BiTree tree, ElemType target) {
    if (tree->data == target)  {// 根节点特殊情况判断 
        std::cout << "输入元素为根节点，无父节点！" << std::endl;
        return NULL;
    }
    Stack stack;
    Init_stack(stack);
    BiTree p = tree;
    while (!Empty_stack(stack) || p != NULL) {
        if (p != NULL) {
            // 保证左右节点有的情况下判断左右节点
            if ((p->lchild != NULL && p->lchild->data == target) || (p->rchild != NULL && p->rchild->data == target) ) {
                Free_space_stack(stack);
                return p;
            }
            Stack_push(stack, p);
            p = p->lchild;

        }
        else {
            stack_pop(stack, p);
            p = p->rchild;
        }
    }
    Free_space_stack(stack);
    std::cout << "树中并无该元素，无法找到该元素的父节点" << std::endl;
    return NULL;
}

// funciton:获取兄弟节点
/*
    算法：先获取父节点，然后判断该节点为左右节点，再看另外一个有没有
*/
BiTree Get_sibling(BiTree tree, ElemType target) {
    BiTree parent = Get_parent(tree, target);
    if (parent == NULL) {
        std::cout << "该节点没有兄弟节点" << std::endl;
        return NULL;
    }
    if (parent->lchild->data == target) { // 该节点为左节点，返回右节点兄弟
        if (parent->rchild != NULL)
            return parent->rchild;
        else {
            std::cout << "该节点为左节点，但无右节点兄弟" << std::endl;
            return NULL;
        }
    }
    else { // 该节点为右节点，返回左节点兄弟
        if (parent->lchild != NULL) 
            return parent->lchild;
        else {
            std::cout << "该节点为右节点，但无左节点兄弟" << std::endl;
            return NULL;
        }
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

// function:删除某个节点及其子树
/*
    算法：找到父节点，修改父节点指向为NULL，再释放整体子树空间
*/
void Delete_target(BiTree &tree, ElemType target) {
    if (tree->data == target) {
        std::cout << "删除节点为根节点，全部删除" << std::endl;
        Destory_tree(tree);
        return ;
    }
    BiTree parent = Get_parent(tree, target);
    if (parent != NULL) {
        BiTree temp = NULL;
        if (parent->lchild->data == target) {
            temp = parent->lchild;
            parent->lchild = NULL;
            
        }
        else {
            temp = parent->rchild;
            parent->rchild = NULL;
        }
        Destory_tree(temp);
    }
    else {
        std::cout << "删除失败！" << std::endl;
    }
}


int main() {
    BiTree tree = NULL;
    std::cout << "请输入树的前序序列，孩子为空为#:";
    CreateTree(tree);
    std::cout << "\n中序遍历-非递归结果为：";
    Inorder_traverse_unrecursion(tree);

    BiTree target_node;
    ElemType target;
    std::cout << "\n下面进行查询测试——查询父节点：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; 
    target_node = Get_parent(tree, target);
    if (target_node != NULL)
        std::cout << "查询成功！该父节点值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行查询测试——查询兄弟：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    target_node = Get_sibling(tree, target);
    if (target_node != NULL)
        std::cout << "查询成功！兄弟值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行删除操作：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    Delete_target(tree, target);
    std::cout << "删除之后的结果为：";
    Inorder_traverse_unrecursion(tree);
    Destory_tree(tree);
    system("pause");
    return 0;
}