/*
    程序描述：N个节点的树(非二叉树)，输出根节点到所有叶子节点的路径
*/
#include<bits/stdc++.h>

// function:按要求格式输出栈内元素
void Print_stack(std::stack<int> &stack) {
    int num;
    while (!stack.empty()) {
        num = stack.top();
        stack.pop();
        std::cout << num;
        if (!stack.empty())
            std::cout << "-";
    }
    std::cout << std::endl;
}

// funciton:实现树根节点到叶子节点每条路径的输出
/*
    算法：不建树，寻找叶子节点，依次向上，直到根节点。全部放入栈中最后输出栈
*/
void Print_track(int *father_num, int N) {
    int judge_leaf[N+1] = {0}; // 用于判断叶子节点，数值为0的为叶子节点
    for (int i=1; i<=N; i++) {
        if (father_num[i] != 0) {
            judge_leaf[father_num[i]]++;
        }
    }
    std::stack<int> stack;   // 因为之前的stack数据类型是BiTree，这次是int。实在是不想写了。偷懒非我本意，非我本意
    for (int i=1; i<=N; i++) {
        if (judge_leaf[i] == 0) {
            stack.push(i);
            int father = father_num[i];
            while (father != 0) {
                stack.push(father);
                father = father_num[father];
            }
            Print_stack(stack);
        }
    }
}

int main() {
    int N;
    std::cout << "请输入树的节点个数N:";
    std::cin >> N;
    std::cout << "请输入各节点的父亲节点编号(根节点为0)，共" << N << "个节点：";
    int father_num[N+1]; // 静态声明
    for (int i=1; i<=N; i++) {
        std::cin >> father_num[i];
    }
    std::cout << "根节点到叶子结点的路径如下：" << std::endl;
    Print_track(father_num, N);
    system("pause");
    return 0;
}
