/*
    程序描述：邻接表结构的无向图进行BFS，计算图的联通分量个数及边的个数
             访问要求：同时多个待访问节点，优先编号最小，0为遍历起点 
*/
#include<bits/stdc++.h>
#define MaxVexNum 30

struct ArcNode { // 表节点定义 
    int adjvex;
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
    算法：根据输入特性(各边按第一个顶点编号升序输入，第一个顶点相同时按第二个顶点降序输入)，创建链表节点，头插法插入
          注意无向图每次要建立两个点
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
    std::cout << "请两个一组输入边：" << std::endl;
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

// function:普通联通分量的BFS
/*
    算法思想：使用队列，从头开始访问，标记数组没有被访问到的，整行进队列(非递归实现)
*/
void BFS(ALGraph graph, int vernum, std::vector<int> &visited, int start) {
    std::queue<int> que;
    que.push(start);
    visited[start] = 1;
    while (!que.empty()) {
        int temp = que.front();
        que.pop();
        std::cout << temp << " ";
        ArcNode *p = graph.vertices[temp].firstarc->nextarc;
        while (p != NULL) {
            if (visited[p->adjvex] == 0) {
                que.push(p->adjvex);
                visited[p->adjvex] = 1;
            }
            p = p->nextarc;
        }
    }
}

// function:对图用BFS，输出遍历顺序以及连通分量数
/*
    算法思想：
    联通分量数用外层循环嵌套一个BFS
    输出边数(1.直接输出 2.遍历所有的有效边数除以2 此处选用1)
*/
void BFS_function(ALGraph graph, int vernum, int arcnum) {
    std::vector<int> visited(vernum, 0); // 标记数组，为1代表访问过
    int link_component = 0;
    std::cout << "访问结果为：";
    for (int i=0; i<vernum; i++) {
        if (visited[i] == 0) {
            BFS(graph, vernum, visited, i);
            link_component++;
        }
    }
    std::cout << "\n联通分量数为：" << link_component << std::endl;
    std::cout << "边数为：" << arcnum << std::endl;
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
    std::cout << "请输入图的顶点数和边数：";
    int vernum, arcnum;
    std::cin >> vernum >> arcnum;
    ALGraph graph;
    Create_graph(graph, vernum, arcnum);
    BFS_function(graph, vernum, arcnum);
    Free_space(graph, vernum);
    system("pause");
    return 0;
}

