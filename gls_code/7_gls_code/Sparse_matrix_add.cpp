/*
    程序描述：稀疏矩阵加法，A+B
*/

#include<bits/stdc++.h>
struct Triple {
    int row;
    int col;
    int data;
    Triple *next;
};

struct SparseMatrix {
    Triple *head;
    int num;
};

// function:创建矩阵，并输入信息
void Create_matrix(SparseMatrix &A, SparseMatrix &B, int t1, int t2) {
    A.head = (Triple *)malloc(sizeof(Triple));
    if (A.head == NULL) {
        std::cout << "[Create_matrix]|A.head fail to allocate";
        system("pause");
        exit(-1);
    }
    A.num = 0;
    A.head->next = NULL;
    B.head = (Triple *)malloc(sizeof(Triple));
    if (B.head == NULL) {
        std::cout << "[Create_matrix]|B.head fail to allocate";
        system("pause");
        exit(-1);
    }
    B.num = 0;
    B.head->next = NULL;
    std::cout << "请输入矩阵A：" << std::endl;
    for (int i=0; i<t1; i++) { // 输入矩阵A
        Triple *temp = (Triple *)malloc(sizeof(Triple));
        if (temp == NULL) {
            std::cout << "[Create_matrix]|A input fail to allocate";
            system("pause");
            exit(-1);
        }
        std::cin >> temp->row;
        std::cin >> temp->col;
        std::cin >> temp->data;
        temp->next = NULL;
        temp->next = A.head->next; // 头插法插入
        A.head->next = temp;
        A.num++;
    }
    std::cout << "请输入矩阵B：" << std::endl;
    for (int i=0; i<t2; i++) { // 输入矩阵A
        Triple *temp = (Triple *)malloc(sizeof(Triple));
        if (temp == NULL) {
            std::cout << "[Create_matrix]|B input fail to allocate";
            system("pause");
            exit(-1);
        }
        std::cin >> temp->row;
        std::cin >> temp->col;
        std::cin >> temp->data;
        temp->next = NULL;
        temp->next = B.head->next; // 头插法插入
        B.head->next = temp;
        B.num++;
    }
}
// function:矩阵相加
/*
    算法：将B中每一个元素加入A中，最后对A进行清洗，删除为0
    该算法复杂度为O(n^2)，若利用有序性可降低为O(n)
*/
void Sum(SparseMatrix &A, SparseMatrix B) {
    Triple *temp = B.head->next;
    while (temp != NULL) { 
        Triple *p = A.head->next;
        while (p != NULL) {
            if (p->row == temp->row && p->col == temp->col) { // A中存在相同行列
                p->data += temp->data;
                break;
            }
            p = p->next;
        }
        if (p == NULL) { // A中不存在相同行列
            Triple *new_Triple = (Triple *)malloc(sizeof(Triple));
            if (new_Triple == NULL) {
                std::cout << "[Sum]|A insert fail";
                system("pause");
                exit(-1);
            }
            new_Triple->row = temp->row;
            new_Triple->col = temp->col;
            new_Triple->data = temp->data;
            new_Triple->next = NULL;
            new_Triple->next = A.head->next;
            A.head->next = new_Triple;
            A.num++;
        }   
        temp = temp->next;
    }

    // 对A进行清洗，删除为0的元素
    temp = A.head;
    while (temp->next != NULL) {
        if (temp->next->data == 0) {
            Triple *p = temp->next;
            temp->next = p->next;
            free(p);
            p = NULL;
            A.num--;
        }
        temp = temp->next;
    }
}

// function:输出矩阵
void Print(SparseMatrix A, int M, int N) {
    std::cout << M << " " << N << " " << A.num << std::endl;
    Triple *temp = A.head->next;
    while (temp != NULL) {
        std::cout << temp->row << " " << temp->col << " " << temp->data << std::endl;
        temp = temp->next;
    }
}

// function:释放空间
void Free_space(SparseMatrix &A) {
    Triple *temp = A.head->next;
    while (temp != NULL) {
        Triple *p = temp->next;
        free(temp);
        temp = p;
    }
    A.num = 0;
    free(A.head); // 释放头节点
    
}

int main() {
    std::cout << "请分别输入：矩阵行、矩阵列、矩阵A非零元素、矩阵B非零元素:";
    int M, N, t1, t2;
    std::cin >> M >> N >> t1 >> t2;
    SparseMatrix A;
    SparseMatrix B;
    Create_matrix(A, B, t1, t2);
    Sum(A, B);
    Print(A, M, N);
    Free_space(A);
    Free_space(B);
    system("pause");
    return 0;
}
