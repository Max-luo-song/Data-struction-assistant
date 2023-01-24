/*
    程序描述：建立正权有向图，以编号0为源点，输出源点到所有节点的最短路径。
             多条最短路径(权值相同)，输出经过点个数最少那个
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
    } 
    for (int i=0; i<graph.vernum; i++) {
        graph.vexs[i].code = i;
    }
}

// function:在dist数组中寻找flag为0的最小值，返回索引(最小值不唯一选索引最小的)
int Find_min(std::vector<int> dist, std::vector<int> flag) {
    int min_data = INFINITY;
    int min_index = -1;
    for (int i=0; i<dist.size(); i++) {
        if (flag[i] == 0 && dist[i] < min_data) {
            min_data = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

// function:迪杰特斯拉算法，得到单源最短路径值dis,得到经过路径path
void Dijkstra(MGraph graph, std::vector<int> &dist, std::vector<int> &path, std::vector<int> &flag, std::vector<int> &length, int start) {
    length[start] = 1;
    // 辅助数组初始化
    for (int i=0; i<graph.vernum; i++) {
        flag[i] = 0;
        dist[i] = graph.arcs[start][i];
        if (i != start)
            length[i] = INFINITY;
        if (dist[i] != INFINITY) {
            path[i] = start;
            length[i] = length[start] + 1;
        }
            
        else
            path[i] = -1;
    }
    flag[start] = 1;
    for (int i=0; i<graph.vernum-1; i++) {
        int k = Find_min(dist, flag); // 在dist中寻找flag为0的最小值
        flag[k] = 1;
        int min_dist = dist[k];
        if (min_dist < INFINITY) {
            for (int j=0; j<graph.vernum; j++) {
                if (flag[j] == 0 && dist[j]>min_dist+graph.arcs[k][j]) {  // 长度小，正常Dijkstra
                    dist[j] = min_dist+graph.arcs[k][j];
                    path[j] = k;
                }
                else if (flag[j] == 0 && dist[j] == min_dist+graph.arcs[k][j]) { // 长度相等，使用length数组判断是否替换
                    if (length[j] > length[k]+1) {
                        path[j] = k;
                        length[j] = length[k]+1;
                    }
                }
            }
        }
    }
}

// function:以指定格式输出路径
void Print(std::stack<int> stack) {
    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();
        std::cout << top;
        if (!stack.empty())
            std::cout << "->";
    }
    std::cout << std::endl;
}

// function:输出源点0到所有节点的最短路径
/*
    算法思想：最短路径的寻找使用迪杰特斯拉算法，把路径保存在path数组中，根据path数组反向寻找路径
*/
void Print_all_path(MGraph graph) {
    std::vector<int> dist(graph.vernum, 0); // 距离数组：存储到start的最短距离
    std::vector<int> path(graph.vernum, 0); // 路径数组：存储到当前节点的上一路径
    std::vector<int> flag(graph.vernum, 0);
    std::vector<int> length(graph.vernum, 0); // 长度数组：存储从start到当前节点的最小路径长度
    Dijkstra(graph, dist, path, flag, length, 0);
    std::cout << "\n\n从源点出发路径如下：" << std::endl;
    for (int i=1; i<graph.vernum; i++) {
        if (path[i] == -1) {
            std::cout << "源点0无法到达点" << i << std::endl;
            continue;
        }
        std::stack<int> stack;
        int start = i;
        while (path[start] != -1) {
            stack.push(start);
            start = path[start];
        }
        stack.push(0);
        Print(stack);
    }
}

int main() {
    MGraph graph;
    Create_graph(graph);
    Print_all_path(graph);
    system("pause");
    return 0;
}

