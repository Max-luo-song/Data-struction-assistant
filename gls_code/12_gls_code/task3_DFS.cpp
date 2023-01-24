/*
    程序描述：建立无权无向图(邻接表为存储结构)，进行DFS
*/

#include<bits/stdc++.h>
#define MaxVexNum 30

struct ArcNode { // 表节点定义 
    int adjvex; // 代表另一边
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
    std::cout << "请按照节点1、节点2的结构输出输入边：" << std::endl;
    for (int i=0; i<arcnum; i++) {
        int node1, node2;
        std::cin >> node1 >> node2;
        ArcNode *temp1 = (ArcNode *)malloc(sizeof(ArcNode));
        if (temp1 == NULL) {
            std::cout << "fail to malloc in Create_graph temp1" << std::endl;
            system("pause");
            exit(-1);
        }
        temp1->adjvex = node1;
        ArcNode *temp2 = (ArcNode *)malloc(sizeof(ArcNode));
        if (temp2 == NULL) {
            std::cout << "fail to malloc in Create_graph temp2" << std::endl;
            system("pause");
            exit(-1);
        }
        temp2->adjvex = node2;
        temp2->nextarc = graph.vertices[node1].firstarc->nextarc;
        graph.vertices[node1].firstarc->nextarc = temp2;

        temp1->adjvex = node1;
        temp1->nextarc = graph.vertices[node2].firstarc->nextarc;
        graph.vertices[node2].firstarc->nextarc = temp1;
    }
}

// function:判断点是否完全访问，完全访问返回true,否则返回false
bool Visit_all(std::vector<int> &visited) {
    for (int i=0; i<visited.size(); i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}


// function:对图进行DFS
/*
    算法思想：递归实现，使用visited数组标记访问点
*/

void DFS(ALGraph graph, int start, std::vector<int> &visited) {
    if (Visit_all(visited)) {
        return ;
    }
    visited[start] = 1;
    std::cout << start << " ";
    for (ArcNode *p = graph.vertices[start].firstarc->nextarc; p != NULL; p = p->nextarc) {
        if (visited[p->adjvex] == 0) {
            DFS(graph, p->adjvex, visited);
        }
    }
}

// function:控制整体DFS(为了防止多联通)
void DFS_function(ALGraph graph, int vernum, std::vector<int> &visited) {
    for (int i=0; i<vernum; i++) {
        if (visited[i] == 0) {
            DFS(graph, i, visited);
        }
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
    std::vector<int> visited(vernum, 0);
    DFS_function(graph, vernum, visited);
    Free_space(graph, vernum);
    system("pause");
    return 0;
}
