/*
    程序描述：建立带权值无向图，对每个节点选择权值最大的节点输出(权值相同，优先编号最小)
             选择邻接表为存储结构，输入m个点以及n组边
*/

#include<bits/stdc++.h>
#define MaxVexNum 30

struct ArcNode { // 表节点定义 
    int adjvex; // 代表另一边
    int weight; // 代表权值 
    struct ArcNode *nextarc;
};

struct VerNode { // 头节点定义
    ArcNode *firstarc;
};

struct ALGraph { // 图定义
    VerNode vertices[MaxVexNum];
    int vernum, arcnum;
};

// function:建立无向图(邻接表结构) 
/*
    算法：直接输入创建即可,头插法
*/
void Create_graph(ALGraph &graph, int vernum, int arcnum) {
    // 1.根据输入点数创建头节点
    for (int i=0; i<vernum; i++) {
        graph.vertices[i].firstarc = (ArcNode *)malloc(sizeof(ArcNode));
        if (graph.vertices[i].firstarc == NULL) {
            std::cout << "fail to malloc in Create_graph head" << std::endl;
            system("pause");
            exit(-1);
        }
        graph.vertices[i].firstarc->nextarc = NULL;
    }
    std::cout << "请按照节点1、节点2、边权值的结构输出输入边：" << std::endl;
    for (int i=0; i<arcnum; i++) {
        int node1, node2, weight;
        std::cin >> node1 >> node2 >> weight;
        ArcNode *temp1 = (ArcNode *)malloc(sizeof(ArcNode));
        if (temp1 == NULL) {
            std::cout << "fail to malloc in Create_graph temp1" << std::endl;
            system("pause");
            exit(-1);
        }
        temp1->adjvex = node1;
        temp1->weight = weight;
        ArcNode *temp2 = (ArcNode *)malloc(sizeof(ArcNode));
        if (temp2 == NULL) {
            std::cout << "fail to malloc in Create_graph temp2" << std::endl;
            system("pause");
            exit(-1);
        }
        temp2->adjvex = node2;
        temp2->weight = weight;
        temp2->nextarc = graph.vertices[node1].firstarc->nextarc;
        graph.vertices[node1].firstarc->nextarc = temp2;

        temp1->adjvex = node1;
        temp1->nextarc = graph.vertices[node2].firstarc->nextarc;
        graph.vertices[node2].firstarc->nextarc = temp1;
    }
}

// funciton:输出图中每个节点的最大通讯节点(最大权值边相关节点)，如果没有相关边输出"None"
/*
    算法思想：对每个节点进行遍历，节点相关的边进行比较。优先权值大，权值相同优先编号小
*/
void Find_max_communicate(ALGraph graph, int vernum, int arcnum) {
    for (int i=0; i<vernum; i++) {
        ArcNode *head = graph.vertices[i].firstarc;
        if (head->nextarc == NULL) { // 没有相关边
            std::cout << "Node" << std::endl;
            continue;
        }
        int max_point = INT_MIN;
        int max_weight = INT_MIN;
        ArcNode *p = head->nextarc;
        while (p != NULL) {
            if (p->weight > max_weight) { // 权值更大
                max_weight = p->weight;
                max_point = p->adjvex;
            }
            else if (p->weight == max_weight) { // 权值相同，索引更小
                if (p->adjvex < max_point) {
                    max_point = p->adjvex;
                }
            }
            p = p->nextarc;
        }
        std::cout << i << "的通信主要对象是：" << max_point << std::endl;
    }
}

// funtion:释放空间(头节点加链表)
void Free_space(ALGraph graph, int vernum) {
    // 释放每个链表
    for (int i=0; i<vernum; i++) {
        ArcNode *p = graph.vertices[i].firstarc->nextarc;
        while (p != NULL) {//
            ArcNode *temp = p->nextarc;
            free(p);
            p = temp;
        }
    }
    // 释放每个头节点
    for (int i=0; i<vernum; i++) {
        free(graph.vertices[i].firstarc);
    }
}

int main() {
    std::cout << "请输入图的顶点数以及相关边信息：";
    int vernum, arcnum;
    std::cin >> vernum >> arcnum;
    ALGraph graph;
    Create_graph(graph, vernum, arcnum);
    Find_max_communicate(graph, vernum, arcnum);
    Free_space(graph, vernum);
    system("pause");
    return 0;
}
