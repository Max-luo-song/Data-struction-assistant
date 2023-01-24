/*
    程序描述：建树，并输出树的深度和宽度
             孩子兄弟链表法  输入数据为父节点编号(0为根节点，共N个)  
*/
#include<bits/stdc++.h>
#include"BiNode.h"
#include"stack.cpp"

// function:遍历寻找父节点  递归先序遍历
void Find_father(BiTree tree, BiTree &father, ElemType father_num) {
    if (tree != NULL) {
        if (tree->data == father_num) {
            father = tree;
            return ;
        }
        Find_father(tree->firstchild, father, father_num);
        Find_father(tree->nextsibling, father, father_num);
    }
}

// funciton:交换数值
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// funciton:排序 按照父节点大小排序
void Sort(int **input_data, int N) {
    for (int i=1; i<N+1; i++) {
        for (int j=1; j<N+1-1-i; j++) {
            if (input_data[j][0] > input_data[j+1][0]) {
                swap(input_data[j][0], input_data[j+1][0]);
                swap(input_data[j][1], input_data[j+1][1]);
            }
        }
    }
}

// function:释放排序数组所用的空间
void Free_space(int **input_data, int N) {
    for (int i=0; i<=N; i++) {
        free(input_data[i]);
    }
    free(input_data);
}

// function:建树，孩子兄弟表示法
/*
    算法：对输入序列进行二维排序，保证父节点先创建，然后挂上子节点
*/
void Create_tree(BiTree &tree, int N) {
    std::cout << "请输入N个节点的父节点：";
    int **input_data; // 每一行第一列存储父节点索引，第二类存储节点编号
    input_data = (int **)malloc(sizeof(int *)*(N+1));
    if (input_data == NULL) {
        std::cout << "fail to allocate1";
        system("pause");
        exit(-1);
    }
    for (int i=0; i<N+1; i++) {
        input_data[i] = (int *)malloc(sizeof(int)*2);
        if (input_data[i] == NULL) {
            std::cout << "fail to allocate2";
            system("pause");
            exit(-1);
        }
    }
    for (int i=1; i<N+1; i++) {
        ElemType father_num = -1;
        std::cin >> father_num;
        input_data[i][0] = father_num;
        input_data[i][1] = i;
    }
    Sort(input_data, N);
    for (int i=1; i<=N; i++) {
        ElemType father_num = -1;
        father_num = input_data[i][0];
        BiTree new_node = (BiNode *)malloc(sizeof(BiNode));
        if (new_node == NULL) {
            std::cout << "fail to allocate!" << std::endl;
            system("pause");
            exit(-1);
        }
        new_node->data = input_data[i][1];
        new_node->firstchild = NULL;
        new_node->nextsibling = NULL;
        if (father_num == 0) { 
            tree = new_node;
            continue;
        }
        BiTree father = NULL;
        Find_father(tree, father, father_num);
        if (father->firstchild == NULL) {  // 暂时没有孩子
            father->firstchild  = new_node;
        }
        else {  // 有孩子，寻找最后一个孩子A，挂到A的右节点(关于孩子节点挂载，也可以用头插法思想，挂在第一个，原孩子列表挂在第一个孩子的右兄弟链表)
            BiTree temp = father->firstchild;
            while (temp->nextsibling != NULL) {
                temp = temp->nextsibling;
            }
            temp->nextsibling = new_node;
        }
    }
    Free_space(input_data, N);
}

// function:树的深度
/*
    递归：选取叶子节点+1和兄弟节点的最大值
*/
int Depth(BiTree tree) {
    if (tree == NULL)
        return 0;
    int child_depth = Depth(tree->firstchild);
    int brother_depth = Depth(tree->nextsibling);
    if (child_depth+1 > brother_depth)
        return child_depth+1;
    else
        return brother_depth;
}

// function:先序递归遍历树，对每个节点求深度并记录在数组中
void Traverse_get_depth(BiTree tree, int *same_depth_num) {
    if (tree != NULL) {
        int node_depth = Depth(tree);
        same_depth_num[node_depth]++;
        Traverse_get_depth(tree->firstchild, same_depth_num);
        Traverse_get_depth(tree->nextsibling, same_depth_num);
    }
}

// function:求树的宽度(同一层下最多节点数)
/*
    算法：求每一个节点的深度，最后遍历节点，统计相同深度的最大数目
*/
int Width(BiTree tree, int N) {
    if (tree == NULL)
        return 0;
    int same_depth_num[N+1] = {0}; // N个节点最多N+1层
    Traverse_get_depth(tree, same_depth_num);
    int width = INT_MIN;
    for (int i=1; i<=N; i++) {
        if (same_depth_num[i] > width)
            width = same_depth_num[i];
    }
    return width;
}

// function:销毁树
void Destroy(BiTree tree) {
    if (tree != NULL) {
        Destroy(tree->firstchild);
        Destroy(tree->nextsibling);
        free(tree);
    }
}

int main() {
    std::cout << "请输入节点个数N：";
    int N; 
    std::cin >> N;
    BiTree tree;
    Create_tree(tree, N);
    int depth = Depth(tree);
    std::cout << "树的深度是:" << depth << std::endl;
    // Destory_tree(tree);
    int width = Width(tree, N);
    std::cout << "树的宽度是：" << width << std::endl;
    Destroy(tree);
    system("pause");
    return 0;
}