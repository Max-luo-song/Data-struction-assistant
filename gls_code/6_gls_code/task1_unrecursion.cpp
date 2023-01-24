/*
    简要描述：N皇后问题，栈非递归解决，栈底层使用链表完成
*/
#include<bits/stdc++.h>
typedef int Elemtype;

struct Node {
    Elemtype x;
    Elemtype y;
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
void Push(Stack &stack, Elemtype x, Elemtype y) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        std::cout << "[Push]|生成新节点失败" << std::endl;
        system("pause");
        exit(-1);
    }
    node->x = x;
    node->y = y;
    node->next = NULL;
    Node *temp = stack.head->next;
    node->next = temp;
    stack.head->next = node;
    stack.length++;
}

// function:出栈(删第一个) 
void Pop(Stack &stack, Elemtype &x, Elemtype &y) {
    if (stack.length == 0) {
        std::cout << "栈中没有元素，出栈失败!" << std::endl;
        system("pause");
        exit(-1);
    }
    Node *temp = stack.head->next;
    x = temp->x;
    y = temp->y;
    stack.head->next = temp->next;
    free(temp);
    temp = NULL;
    stack.length--;
}

// function:查看栈顶元素
void Top(Stack stack, Elemtype &x, Elemtype &y) {
    if (Empty_stack(stack)) {
        std::cout << "栈空，无法查看元素" << std::endl;
        system("pause");
        exit(-1);
    }
    x = stack.head->next->x;
    y = stack.head->next->y;
}


// function:具体判断合法条件，合法返回truem 不合法返回false
/*
    合法条件：不一行(但不需要判断)、不一列、不斜向
*/

bool Judge(Node *temp, int x, int y) {
    // 列判断
    if (y == temp->y)
        return false;
    // 斜向判断
    if (abs(x-temp->x) == abs(y-temp->y)) { // 用斜率判断
        return false;
    }
    return true;
}

// function:输出皇后形状，其中‘Q’代表皇后
void Print_queen(Stack stack, int n, int total_num) {
    char **matrix = (char **)malloc(sizeof(char *)*n); // 动态申请二维数组，防止N过大
    for (int i=0; i<n; i++) {
        matrix[i] = (char *)malloc(sizeof(char)*n);
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            matrix[i][j] = '.';
        }
    }
    Node *temp = stack.head->next;
    while (temp != NULL) {
        matrix[temp->x][temp->y] = 'Q';
        temp = temp->next;
    }
    std::cout << "第" << total_num << "种情况" << std::endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
    // 输出后释放二维空间
    for (int i=0; i<n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// function:判断是否是有效位置，栈空时直接进入，栈不空的时候要和所有的比较
bool isValid(Stack stack, int x, int y) {
    if (Empty_stack(stack))
        return true;
    Node *temp = stack.head->next;
    while (temp != NULL) {
        if (!Judge(temp, x, y))
            return false;
        temp = temp->next;
    }
    return true;
}

// function:N皇后功能
void N_queen_uncursion(Stack &stack, int n, int &total_num) {
    int x = 0, y = 0;
    Push(stack, x, y);
    bool flag = false;
    x = 1; // 准备进行测试
    y = 0;
    while(!Empty_stack(stack) || (x == 0 && y != n)) {
        while (y < n) { // 测试本行是否有满足条件的
            flag = isValid(stack, x, y);
            if (flag == true)
                break;
            y++;
        }
        if (flag == true) {  // 本行找到了合适的
            Push(stack, x, y);
            x++; //进入下一行
            if (x == n) {
                total_num++;
                Print_queen(stack, n, total_num);
                //system("pause");
                Pop(stack, x, y); // 重新返回上一行的下一个
                y++;  // 也要注意要返回到有效位置
                while (y == n && !Empty_stack(stack)) {
                    Pop(stack, x, y);
                    y++;
                }
            }
            else {
                y = 0; // 从新一行的第一个开始试探
            }
        }
        else { // 本行没有，需要查看上一行
//            if (!Empty_stack(stack))
            Pop(stack, x, y);
            y++; // 尝试下一个位置
            while (y == n && !Empty_stack(stack)) { // 如果一行中没有合适的，向上找，直到找到合适的
                Pop(stack, x, y);
                y++;
            }
        }
    }
}

// function:释放空间
void Free_space_stack(Stack &stack) {
    int x, y;
    while (!Empty_stack(stack)) {
        Pop(stack, x, y);
    }
    free(stack.head); // 不要忘记删掉头节点
    std::cout << "释放空间成功！" << std::endl;
}

int main() {
    Stack stack;
    Init_stack(stack);
    int n;
    std::cout << "请输入N:";
    std::cin >> n;
    int total_num = 0;
    N_queen_uncursion(stack, n, total_num);
    std::cout << "总共有" << total_num << "种" << std::endl;
    system("pause");
    Free_space_stack(stack);
    return 0;
}