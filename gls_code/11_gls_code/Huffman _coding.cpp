/*
    程序描述：输入一段字符串，根据字符出现次数作为权值建立哈夫曼树(不区分大小写)
             两个输出：1.输出哈夫曼编码 2.根据哈夫曼编码反转回之前的字符串
*/

#include<bits/stdc++.h>

typedef struct HTNode {
    int weight;
    int parent, lchild, rchild;
}*HufTree;

// function:初始化霍夫曼树
void InitHT(int n, HufTree &HT, std::vector<int> w) {
    HT = (HufTree)malloc(2*n*sizeof(HTNode));
    if (HT == NULL) {
        std::cout << "fail to allocate HT" << std::endl;
        system("pause");
        exit(-1);
    }
    for (int i=1; i<=n; i++) {
        HT[i].weight = w[i-1];
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
    for (int i=n+1; i<2*n; i++) {
        HT[i].weight = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
    }
}

// function:从前面的序列中，选择两个没有父节点且权值小的索引，s1为较小值索引，s2为较大值索引。若值相同，保证s1<=s2即可
void select_two_small(HufTree &HT, int bound, int &s1, int &s2) {
    s1 = 0;
    s2 = 0;
    int small_one = INT_MAX; // 代表最小
    int small_two = INT_MAX; // 代表第二小
    for (int i=1; i<=bound; i++) {
        if (HT[i].parent == 0) { // 证明没有子节点
            if (HT[i].weight < small_one) {
                small_two = small_one;
                s2 = s1;
                small_one = HT[i].weight;
                s1 = i;
            }
            
            else if (HT[i].weight == small_one && HT[i].weight < small_two) { // 此处需要增加第二个限制条件，否则相等时会更新s2
                small_two = HT[i].weight;
                s2 = i;
            }
            else if (HT[i].weight > small_one && HT[i].weight < small_two) {
                small_two = HT[i].weight;
                s2 = i;
            }
        }
    }
}

// function:创建霍夫曼树
/*
    算法：选择在本节点之前的两个权值最小的没有父节点的两个几点填补新节点
*/
void CreateHT(HufTree &HT, int n) {
    for (int i=n+1; i<2*n; i++) {
        int s1, s2; // 认定s1<=s2
        select_two_small(HT, i-1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight+HT[s2].weight;
    }
}

// function:翻转字符串
void reverse(char *temp, int n) {
    for (int i=0; i<n/2; i++) {
        char t = temp[i];
        temp[i] = temp[n-2-i];
        temp[n-2-i] = t;
    }
}

// funciton:根据哈夫曼树获取哈夫曼编码
/*
    算法：从叶子节点出发逆序找到根节点，然后进行反转并存储
*/
void GetHTCode(HufTree &HT, char **HC, int n) {
    char *temp = (char *)malloc(sizeof(char)*n); // 树最高为n
    if (temp == NULL) {
        std::cout << "Fail to allocate temp *" << std::endl;
        system("pause");
        exit(-1);
    }
    for (int i=0; i<n; i++) {
        int start = 0;
        for (int c=i+1, f=HT[c].parent; f != 0; c=f, f=HT[f].parent) { // 从叶子节点向上找
            if (HT[f].lchild == c) {
                temp[start++] = '0';
            }
            else {
                temp[start++] = '1';
            }
        }
        temp[start++] = '\0';
        reverse(temp, start); // 翻转
        HC[i] = (char *)malloc(start*sizeof(char));
        if (HC[i] == NULL) {
            std::cout << "fail to allocate HC[i]" << std::endl;
            exit(-1);
        }
        strcpy(HC[i], temp);
    }
    free(temp);
}

// function:创建霍夫曼树，得到霍夫曼编码
/*
    算法：建立二维数组(2*n-1)个一维数组中，前n个存储原始数据，后n-1个存储非叶子节点
          最终将各字符编码结果存储在HC中
*/
void HufCode(int n, std::vector<int> w, HufTree &HT, char **HC) {
    if (n <= 1) // 只有一个节点返回
        return ;
    InitHT(n, HT, w);// 初始化霍夫曼树
    CreateHT(HT, n);// 创建霍夫曼树
    GetHTCode(HT, HC, n);// 获取霍夫曼编码
}

// function:寻找索引
int Find_index(std::string zimu, char target) {
    for (int i=0; i<zimu.length(); i++) {
        if (zimu[i] == target) {
            return i;
        }
    }
    return -1;
}

// function:输出哈夫曼编码
void Print_HufCode(char **HC, std::string zimu, int n, char *hufCode, std::string input) {
    for (int i=0; i<input.length(); i++) {
        int index = Find_index(zimu, input[i]);
        if (i == 0)
            strcpy(hufCode, HC[index]);
        else
            strcat(hufCode, HC[index]);
    }
    std::cout << hufCode << std::endl;
}

// function：根据哈夫曼编码输出原始字符
void Print_zimu(HufTree HT, char *hufCode, int n, std::string zimu) {
    int length = 0;
    for (int i=0; hufCode[i] != '\0'; i++) {
        length++;
    }
    int i = 0;
    int root_index = 2*n-1;
    int p = root_index;
    while (i < length) {
        if (HT[p].lchild == 0 && HT[p].rchild == 0) { // 到达叶子节点
            std::cout << zimu[p-1];
            if (i >= length)
                break;
            p = root_index;
        }
        if (hufCode[i] == '0') {
            p = HT[p].lchild;
        }
        else if (hufCode[i] == '1') {
            p = HT[p].rchild;
        }   
        i++;
    }
    std::cout << zimu[p-1];
    std::cout << std::endl;
}

// function:释放空间
void Free_space(HufTree HT, char **HC, int n) {
    free(HT);
    for (int i=0; i<n; i++) {
        free(HC[i]);
    }
    free(HC);
} 

int main() {
    std::cout << "请输入目标字符串：";
    std::string input;
    std::cin >> input;
    
    for (int i=0; i<input.length(); i++) { // 将所有字符转为小写
        input[i] = tolower(input[i]);
    }
    int count[26] = {0}; // 用于记录每个字母出现的个数
    for (int i=0; i<input.length(); i++) {
        count[input[i]-'a']++;
    }
    // 得到权值数组以及对应字母数组，索引一一对应
    std::string zimu;
    std::vector<int> zimu_weight;
    for (int i=0; i<26; i++) {
        if (count[i] != 0) {
            zimu += 'a'+i;
            zimu_weight.push_back(count[i]);
        }
    }
    int n = zimu.length(); 
    HufTree HT;
    char **HC;
    HC = (char **)malloc(n*sizeof(char *));
    if (HC == NULL) {
        std::cout << "Fail to allocate HC char **" << std::endl;
        system("pause");
        exit(-1);
    }
    HufCode(n, zimu_weight, HT, HC);
    char hufCode[100]; // 为了方便，静态设置为100
    std::cout << input << " 编码结果为:";
    Print_HufCode(HC, zimu, n, hufCode, input);
    std::cout << hufCode << " 解码结果为：";
    Print_zimu(HT, hufCode, n, zimu);
    Free_space(HT, HC, n);
    system("pause");
    return 0;
}