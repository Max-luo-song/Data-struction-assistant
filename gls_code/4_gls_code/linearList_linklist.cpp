/*
    程序简述：线性表——链表练习
             考察点：1.从文件中读入数据，并建立链表
                     2.链表的遍历
                     3.链表的反转
                     4.链表去重
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>

struct Node {
    Node *next;
    int val;
};

struct LinearList_linklist {
    Node *head;
    Node *tail; // 加入尾指针，便于插入
    int length;
};

// function:初始化线性链表
LinearList_linklist *Init_LinearList_linklist(LinearList_linklist *linearList_linklist) {
    linearList_linklist = (LinearList_linklist *)malloc(sizeof(LinearList_linklist));
    linearList_linklist->length = 0;
    linearList_linklist->head = (Node *)malloc(sizeof(Node));
    linearList_linklist->head->next = NULL;
    linearList_linklist->tail = linearList_linklist->head;
    return linearList_linklist;
}

// function:从文件读取数据到线性链表
void ReadFile_LinearList_linklist(LinearList_linklist *linearList_linklist) {
    std::ifstream readFile;
    readFile.open("data.txt", std::ios_base::in);
    if (!readFile.is_open()) {
        std::cout << "data.txt fail to open!" << std::endl;
    }
    while (!readFile.eof()) {
        Node *temp = (Node *)malloc(sizeof(Node));
        readFile >> temp->val;
        temp->next = NULL; 
        linearList_linklist->tail->next = temp;
        linearList_linklist->tail = linearList_linklist->tail->next; // 尾指针保持末尾
        linearList_linklist->length++;
        if (readFile.fail())
            break;
    }
    readFile.close(); // 文件打开记得关闭
}

// function:正序输出线性链表
void Print_positive_LinearList_linklist(LinearList_linklist *linearList_linklist) {
    std::cout << "正序输出线性链表结果为：\n";
    Node *temp = linearList_linklist->head->next;
    while (temp != NULL) {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
}

// function:逆转链表并输出
/*
    方法：三指针法逆转链表
*/
void Reverse_linearList_linklist(LinearList_linklist *linearList_linklist) {
    Node *cur = linearList_linklist->head->next;
    Node *pre = NULL;
    Node *temp;
    while (cur != NULL) {
        // 1,2两步反转，3，4两步后移
        temp = cur->next; // 1
        cur->next = pre; // 2
        pre = cur; // 3
        cur = temp; // 4
    }
    linearList_linklist->head->next = pre;
    // tail本来需要移到末尾，但此处不作为重点，掠过
    std::cout << std::endl << "经过反转后输出结果如下:\n";
    Print_positive_LinearList_linklist(linearList_linklist);
}

// function:将线性链表内相同的元素删除
/*
    方法：双重循环
*/
void Delete_repetition_linearList_linklist(LinearList_linklist *linearList_linklist) {
    Node *base = linearList_linklist->head->next;
    while (base != NULL) {
        Node *p = base; // p始终是q前面的元素
        Node *q = base->next;
        while (q != NULL) {
            if (q->val == base->val) {
                Node *temp = q;
                q = q->next;
                free(temp);
                temp = NULL;
                p->next = q;
                linearList_linklist->length--;
            }
            else {
                p = p->next;
                q = q->next;
            }
        }
        base = base->next;
    }
    std::cout << std:: endl <<  "线性链表去重后结果为：\n";
    Print_positive_LinearList_linklist(linearList_linklist);
    std::cout << std::endl;
}

//function:释放所有malloc的空间
void Free_linearList_linklist(LinearList_linklist *linearList_linklist) {
    Node *temp = linearList_linklist->head;
    while (temp != NULL) {
        Node *p = temp->next;
        free(temp);
        temp = p;
    }
    free(linearList_linklist);
    std::cout << "释放空间完成!\n";
}

int main() {
    LinearList_linklist *linearList_linklist;
    linearList_linklist = Init_LinearList_linklist(linearList_linklist);
    ReadFile_LinearList_linklist(linearList_linklist);
    Print_positive_LinearList_linklist(linearList_linklist);
    Reverse_linearList_linklist(linearList_linklist);
    Delete_repetition_linearList_linklist(linearList_linklist);
    Free_linearList_linklist(linearList_linklist);
    system("pause");
    return 0;
}