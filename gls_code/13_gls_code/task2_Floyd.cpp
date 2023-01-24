/*
    程序描述：寻找仓库中到其他节点距离之和最小的节点，使用邻接矩阵建立带权无向图
            算法思想：使用弗洛伊德算法求出矩阵，判断和最小即可
*/
#include<bits/stdc++.h>
#define INFINITY 10000
#define MAX_V 20 // 最大顶点数目

typedef struct {
    int code; // 本题只需要保存顶点编号即可
}VertexType;

typedef struct {
    int arcs[MAX_V][MAX_V];
    int vernum, arcnum;
    VertexType vexs[MAX_V];
    // 本题默认为有向图
}MGraph;

//function:初始化图的邻接矩阵，值全赋为最大值
void Init_graph(MGraph &graph) {
    for (int i=0; i<MAX_V; i++) {
        for (int j=0; j<MAX_V; j++) {
            if (i == j)
                graph.arcs[i][j] = 0;
            else
                graph.arcs[i][j] = INFINITY;
        }
    }
}

// function:使用邻接矩阵建图
/*
    注意是单向图，u指向v
*/
void Create_graph(MGraph &graph) {
    Init_graph(graph);
    std::cout << "请输入图的顶点数:";
    std::cin >> graph.vernum;
    std::cout << "请输入图的边数:";
    std::cin >> graph.arcnum;
    std::cout << "请输入各边及其权值:\n";
    for (int i=0; i<graph.arcnum; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.arcs[u][v] = w;
        graph.arcs[v][u] = w;
    } 
    for (int i=0; i<graph.vernum; i++) {
        graph.vexs[i].code = i;
    }
}

// funciton:完成floyd算法，求出二维距离矩阵
void Floyd(MGraph graph, std::vector<std::vector<int>> &dis) {
    for (int i=0; i<graph.vernum; i++) {
        for (int j=0; j<graph.vernum; j++) {
            dis[i][j] = graph.arcs[i][j];
        }
    }
    for (int k=0; k<graph.vernum; k++) {
        for (int i=0; i<graph.vernum; i++) {
            for (int j=0; j<graph.vernum; j++) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

// function:寻找到其他点距离和最小的点，输出该点及最小路径
/*
    算法思想：使用弗洛伊德算法获取各点之间的最短路径，再对没一个点求和，选其中最小的即可
*/
void Find_target(MGraph graph) {
    std::vector<std::vector<int>> dis(MAX_V, std::vector<int>(MAX_V, 0));
    Floyd(graph, dis);
    int min_one = INT_MAX;
    int min_index;
    for (int i=0; i<graph.vernum; i++) {
        int sum = 0;
        for (int j=0; j<graph.vernum; j++) {
            sum += dis[i][j];
        }
        if (sum < min_one) {
            min_one = sum;
            min_index = i;
        }
    }
    std::cout << "最短路径和为:" << min_one << std::endl;
    std::cout << "起点仓库编号为：" << min_index << std::endl;
}

int main() {
    MGraph graph;
    Create_graph(graph);
    Find_target(graph);
    system("pause");
    return 0;
}