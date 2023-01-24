#include<bits/stdc++.h>
#include"BiNode.h"
typedef char Elemtype;


struct Node {
    BiTree tree;
    Node *next;    
};

struct Stack { // 使用带头节点的链表实现
    Node *head;
    int length;
};

// function:初始化栈
void Init_stack(Stack &stack) {
    stack.head = (Node *)malloc(sizeof(Node));
    if (stack.head == NULL) {
        std::cout << "[Init_stack]|初始化失败" << std::endl;
        system("pause");
        exit(-1);
    }
    stack.head->next = NULL;
    stack.length = 0;
}

// function:判断是否栈空，栈空返回true
bool Empty_stack(Stack &stack) {
    if (stack.length == 0)
        return true;
    else
        return false;
}

// function:进栈(链表头插)
void Stack_push(Stack &stack, BiTree tree) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        std::cout << "[Push]|生成新节点失败" << std::endl;
        system("pause");
        exit(-1);
    }
    node->tree = tree;
    node->next = NULL;
    Node *temp = stack.head->next;
    node->next = temp;
    stack.head->next = node;
    stack.length++;
}

// function:出栈(删第一个) 
void stack_pop(Stack &stack, BiTree &tree) {
    if (stack.length == 0) {
        std::cout << "栈中没有元素，出栈失败!" << std::endl;
        system("pause");
        exit(-1);
    }
    Node *temp = stack.head->next;
    tree = temp->tree;
    stack.head->next = temp->next;
    free(temp);
    temp = NULL;
    stack.length--;
}

// function:查看栈顶元素
void stack_top(Stack stack, BiTree &top_element) {
    if (Empty_stack(stack)) {
        std::cout << "栈空，无法查看元素" << std::endl;
        system("pause");
        exit(-1);
    }
    top_element = stack.head->next->tree;
}

// function:释放空间
void Free_space_stack(Stack &stack) {
    BiTree temp;
    while (!Empty_stack(stack)) {
        stack_pop(stack, temp);
    }
    free(stack.head); // 不要忘记删掉头节点
    // std::cout << "释放空间成功！" << std::endl;
}