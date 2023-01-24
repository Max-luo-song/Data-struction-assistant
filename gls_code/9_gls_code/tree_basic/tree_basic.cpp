/*
    程序描述：二叉树的基本操作：1.初始化、销毁、清空 2.访问类 3.加工类
*/
#include<bits/stdc++.h>
// 此处为节省篇幅，使用外部文件，模块化栈和队列结构
#include"BiNode.h"
#include"stack.cpp"
#include"queue.cpp"

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

// function:先序遍历-递归形式
void Preorder_traverse_recursion(BiTree tree) {
    if (tree != NULL) {
        std::cout << tree->data;
        Preorder_traverse_recursion(tree->lchild);
        Preorder_traverse_recursion(tree->rchild);
    }
}

// function:先序遍历-非递归形式
void Preorder_traverse_unrecursion(BiTree tree) {
    Stack stack;
    Init_stack(stack);
    BiTree p = tree;
    BiTree rondom;
    while (p != NULL || !Empty_stack(stack)) {
        if (p != NULL) {
            Stack_push(stack, p);   
            std::cout << p->data;  // 中
            p = p->lchild; // 左
        }
        else {
            stack_pop(stack, p);
            p = p->rchild; // 右
        }
    }
    Free_space_stack(stack);
}

// function:中序遍历-递归形式
void Inorder_traverse_recursion(BiTree tree) {
    if (tree != NULL) {
        Inorder_traverse_recursion(tree->lchild);
        std::cout << tree->data;
        Inorder_traverse_recursion(tree->rchild);
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
            p = p->lchild;   // 左
        }
        else {
            stack_pop(stack, p); 
            std::cout << p->data; // 中
            p = p->rchild; // 右
        }
    }
    Free_space_stack(stack);
}

// function:后序遍历-递归形式
void Postorder_traverse_recursion(BiTree tree) {
    if (tree != NULL) {
        Postorder_traverse_recursion(tree->lchild);
        Postorder_traverse_recursion(tree->rchild);
        std::cout << tree->data;
    }
}
// function:后序遍历-非递归形式
// 后序遍历思想，目的是左右中，先变成中右左，再反转得到目的。因为是栈，所以先左进后右进
void Postorder_traverse_unrecursion(BiTree tree) {
    Stack stack1;
    Stack stack2;
    Init_stack(stack1);
    Init_stack(stack2);
    BiTree p = tree;
    Stack_push(stack1, p);
    while (!Empty_stack(stack1)) {
        stack_pop(stack1, p); // 中
        Stack_push(stack2, p); 
        if (p->lchild)
            Stack_push(stack1, p->lchild); // 左
        if (p->rchild)
            Stack_push(stack1, p->rchild); // 右
    }
    while (!Empty_stack(stack2)) {
        stack_pop(stack2, p);
        std::cout << p->data;
    }
    Free_space_stack(stack1);
    Free_space_stack(stack2);
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

// function:将树置空
/*
    算法：任意一种方法遍历，将每个元素值改为空值代表即可。此处选择递归先序
*/
void Clear_tree(BiTree &tree) {
    if (tree != NULL) {
        tree->data = ' ';
        Clear_tree(tree->lchild);
        Clear_tree(tree->rchild);
    }
}

// function：判断树是否空
bool Empty_tree(BiTree tree) {
    if (tree == NULL || tree->data == ' ')
        return true;
    else
        return false;
}
// function：返回树的根节点
BiTree Root_tree(BiTree tree) {
    return tree;
}

// function:返回指向某个值的指针，没有的话返回NULL
/*
    算法：非递归先序遍历，相等时返回
*/
BiTree Get_value(BiTree tree, ElemType target) {
    Stack stack;
    Init_stack(stack);
    BiTree p = tree;
    while (!Empty_stack(stack) || p != NULL) {
        if (p != NULL) {
            if (p->data == target) {
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
    return NULL;
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

// function:返回左子节点
/*
    算法：先序递归遍历，找到该节点再判断其子节点情况
*/
void Get_leftchild(BiTree tree, ElemType parent_data, BiTree &left_child) {
    if (tree != NULL) {
        if (tree->data == parent_data) {
            if (tree->lchild != NULL) {
                left_child = tree->lchild;
            }
            return ;
        }
        Get_leftchild(tree->lchild, parent_data, left_child);
        Get_leftchild(tree->rchild, parent_data, left_child);
    }
}

// function:返回右子节点
/*
    算法：先序递归遍历，找到该节点再判断其子节点情况
*/
void Get_rightchild(BiTree tree, ElemType parent_data, BiTree &right_child) {
    if (tree != NULL) {
        if (tree->data == parent_data) {
            if (tree->rchild != NULL) {
                right_child = tree->rchild;
            }
            return ;
        }
        Get_rightchild(tree->lchild, parent_data, right_child);
        Get_rightchild(tree->rchild, parent_data, right_child);
    }
}

// function:返回节点左兄弟
/*
    算法：前序非递归遍历，以父节点为准，先找到父节点，然后判断左兄弟
*/
BiTree Get_leftsibling(BiTree tree, ElemType target) {
    BiTree parent = Get_parent(tree, target);
    if (parent != NULL) {
        if (parent->lchild != NULL && parent->lchild->data == target) {
            std::cout << "自己本身就是左节点，无左兄弟" << std::endl;
            return NULL;
        }
        else {
            if (parent->lchild == NULL) {
                std::cout << "该节点无左兄弟" << std::endl;
                return NULL;
            }
            else
                return parent->lchild;
        }
    }
    else {
        std::cout << "节点寻找出现问题！" << std::endl;
        return NULL;
    }
}

// function:返回节点右兄弟
/*
    算法：前序非递归遍历，以父节点为准，先找到父节点，然后判断右兄弟
*/
BiTree Get_rightsibling(BiTree tree, ElemType target) {
    BiTree parent = Get_parent(tree, target);
    if (parent != NULL) {
        if (parent->rchild != NULL && parent->rchild->data == target) {
            std::cout << "自己本身就是右节点，无右兄弟" << std::endl;
            return NULL;
        }
        else {
            if (parent->rchild == NULL) {
                std::cout << "该节点无右兄弟" << std::endl;
                return NULL;
            }
            else
                return parent->rchild;
        }
    }
    else {
        std::cout << "节点寻找出现问题！" << std::endl;
        return NULL;
    }
}

int main() {
    BiTree tree = NULL;
    std::cout << "请输入树的前序序列，孩子为空为#:";
    CreateTree(tree);
    std::cout << "\n先序遍历-递归结果为："; 
    Preorder_traverse_recursion(tree);
    std::cout << "\n先序遍历-非递归结果为："; 
    Preorder_traverse_unrecursion(tree);
    std::cout << "\n中序遍历-递归结果为：";
    Inorder_traverse_recursion(tree);
    std::cout << "\n中序遍历-非递归结果为：";
    Inorder_traverse_unrecursion(tree);
    std::cout << "\n后序遍历-递归结果为：";
    Postorder_traverse_recursion(tree);
    std::cout << "\n后序遍历-非递归结果为：";
    Postorder_traverse_unrecursion(tree);
    std::cout << "\n层次遍历-结果为：";
    Level_traverse(tree);
    std::cout << "\n该树的深度是：";
    int depth = Depth(tree);
    std::cout << depth;

    std::cout << "\n下面进行查询测试——判断树是否为空：";
    if (Empty_tree(tree)) 
        std::cout << "树空" << std::endl;
    else    
        std::cout << "非空" << std::endl;

    std::cout << "\n下面进行查询测试——查询根节点：";
    BiTree tree_node = Root_tree(tree);
    if (tree_node != NULL)
        std::cout << "根节点为：" << tree_node->data << std::endl;
    else
        std::cout << "树为空" << std::endl;
    
    std::cout << "\n下面进行查询测试——查询指定值：" << std::endl;
    std::cout << "请输入目标值:";
    ElemType target;
    std::cin >> target;
    BiTree target_node = Get_value(tree, target);
    if (target_node != NULL)
        std::cout << "查询成功！该值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行查询测试——查询父节点：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    target_node = Get_parent(tree, target);
    if (target_node != NULL)
        std::cout << "查询成功！该父节点值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行查询测试——查询左孩子：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    Get_leftchild(tree, target, target_node);
    if (target_node != NULL)
        std::cout << "查询成功！该左孩子值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行查询测试——查询右孩子：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    Get_rightchild(tree, target, target_node);
    if (target_node != NULL)
        std::cout << "查询成功！该右孩子值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行查询测试——查询左兄弟：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    target_node =  Get_leftsibling(tree, target);
    if (target_node != NULL)
        std::cout << "查询成功！该左兄弟值为:" << target_node->data << std::endl;

    std::cout << "\n下面进行查询测试——查询右兄弟：" << std::endl;
    std::cout << "请输入目标值:";
    std::cin >> target; // 沿用上面的变量
    target_node =  Get_rightsibling(tree, target);
    if (target_node != NULL)
        std::cout << "查询成功！该右兄弟值为:" << target_node->data << std::endl;

    std::cout << "\n下面测试树空和树清空操作:" << std::endl;
    if (!Empty_tree(tree))
        std::cout << "当前树不为空" << std::endl;
    std::cout << "下面进行树清空操作...." << std::endl;
    Clear_tree(tree);
    if (Empty_tree(tree))
        std::cout << "当前树空" << std::endl;
    Destory_tree(tree);
    system("pause");
    return 0;
}