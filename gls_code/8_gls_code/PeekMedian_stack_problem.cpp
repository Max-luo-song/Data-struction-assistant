/*
    程序描述：使用栈结构，三种操作(入栈，出栈，取栈Key中值)
            入栈：“Push key”
            出栈：“Pop”
            取中值："PeekMedian"   N为偶(N/2)  N为奇((N+1)/2) 其中N为Key个数  Key的定义要求不同数
        无效输出：Invalid
        无效情况：栈空时出栈或取Key中值
                 输入命令非法时
*/
/*
    取中值实现思路：链表实现栈结构，整体链表放入数组中，对数组排序，再取中值
*/

#include<bits/stdc++.h>

typedef int Elemtype;
struct Node {
    Elemtype data;
    Node *next;
};

struct Stack {
    Node *head;
    int length;
};

// function:初始化栈的头节点
void Init_stack(Stack &stack) {
    stack.head = (Node *)malloc(sizeof(Node));
    if (stack.head == NULL) {
        std::cout << "[Init_stack]|fail to allocate head" << std::endl;
        system("pause");
        exit(-1);
    }
    stack.head->next = NULL;
    stack.length = 0;
}

// function:入栈，链表头插法
void Push(Stack &stack, Elemtype key_value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        std::cout << "[Push]|fail to allocate" << std::endl;
        system("pause");
        exit(-1);
    }
    new_node->data = key_value;
    new_node->next = NULL;
    Node *temp = stack.head;
    new_node->next = temp->next;
    temp->next = new_node;
    stack.length++;
}

// function:出栈，删除第一个节点。返回值
void Pop(Stack &stack, Elemtype &pop_data) {
    Node *temp = stack.head->next;
    stack.head->next = temp->next;
    pop_data = temp->data;
    free(temp);
    temp = NULL;
    stack.length--;
}

// function:返回栈元素中值
/*
    算法：读取栈中元素入数组，因为数值不超过105，直接静态声明，利用hash存储。
          从头遍历，有效的达到N/2为止
*/
void Get_mid(Stack stack, Elemtype &mid_data) {
    Elemtype array[106] = {0};
    Node *temp = stack.head->next;
    int key_num = 0;
    while (temp != NULL) {
        if (array[temp->data] == 0) {
            key_num++;
        }
        array[temp->data]++;
        temp = temp->next;
    }
    int target_seqence = 0;
    if (key_num % 2 == 0)
        target_seqence = key_num/2;
    else
        target_seqence = (key_num+1)/2;
    int count = 0;
    for (int i=0; i<106; i++) {
        if (array[i] != 0) {
            count += 1;
            if (count >= target_seqence) {
                mid_data = i;
                break;
            }
        }
    }
}

// function:把输入的字符串变成数字
int Get_num(char num[15]) {
    int result = 0;
    for (int i=0; num[i] != '\0'; i++) {
        result = result*10+(num[i]-'0');
    }
    return result;
}

// function:判断输入是否有效，有效返回key_value
bool Push_key_valid(char input[15], Elemtype &key_value) {
    char string[15] = ""; // 把input做切割，看是否满足两部分
    char num[15] = "";
    int i; // 需要保留位置
    int string_index = 0;
    int num_index = 0;
    for (i=0; input[i] != '\0' && input[i] != ' '; i++) {
        string[string_index++] = input[i];
    }
    string[string_index] = '\0'; // char *数组末尾要有\0
    if (input[i] != ' ') // 说明input中没有空格 
        return false;
    i++;
    if (strcmp(string, "Push") != 0) // 前面的命令不是Push
        return false;
    for (; input[i] != '\0'; i++) {
        if (input[i] >= '9' || input[i] <= '0') // 说明输入的数字格式不对 
            return false;
        num[num_index++] = input[i];
    }
    num[num_index] = '\0';
    key_value = Get_num(num);
    return true; 
}

// function:完成栈的操作功能
void Stack_opeartion(Stack &stack, int N) {
    std::cout << "请输入合法操作(Push key/Pop/PeekMedian)：" << std::endl;
    for (int i=0; i<N; i++) {
        char input[15];  // 在循环里定义局部变量，每轮刷新
        // std::cin >> input; 此处输入不能使用cin，cin是空格截取，要按一行输入
        fflush(stdin); // 刚才输入一个N了，要清空下缓存区
        std::cin.getline(input, 15);
        Elemtype key_value = 0; // 用于保存push的值
        if (strcmp(input, "Pop") == 0) { // 栈空违法
            if (stack.length == 0) {
                std::cout << "Invalid"; 
            }
            else {
                Elemtype pop_data;
                Pop(stack, pop_data);
                std::cout << pop_data;
            }
        }
        else if (strcmp(input, "PeekMedian") == 0) {
            if (stack.length == 0) { // 栈空违法
                std::cout << "Invalid"; 
            }
            else {
                Elemtype mid_data;
                Get_mid(stack, mid_data);
                std::cout << mid_data;
            }
        }
        else{
            if (Push_key_valid(input, key_value)) {
                Push(stack, key_value);
                //std::cout << "hello" << std::endl;
            }
            else {
                std::cout << "Invalid";
            }
        }
        if (i != N-1) {  // 对最后一行特殊处理，最后一行不需要换行
            std::cout << std::endl;
        }
    }
}

// function:释放空间
void Free_space(Stack &stack) {
    Node *temp = stack.head->next;
    while (temp != NULL) {
        Node *t = temp->next;
        free(temp);
        temp = t;
    }
    free(stack.head); // 释放头节点
    stack.length = 0;
}

int main() {
    Stack stack;
    Init_stack(stack);
    int N;
    std::cout << "请输入要进行的操作数：";
    std::cin >> N;
    Stack_opeartion(stack, N);
    Free_space(stack);
    system("pause");
}