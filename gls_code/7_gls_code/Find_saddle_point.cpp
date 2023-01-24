/*
    程序描述：寻找马鞍点
            马鞍点定义：mxn矩阵中a(ij)是i行最小值，j列最大值
            多个位置满足，输出多个坐标。没有输出"None"
*/

#include<bits/stdc++.h>
typedef int ElemType;
struct Matrix
{
    ElemType **matrix; // 这里选择动态分配原因是无法确认m,n多大，选择动态分配适配大空间
    int row;
    int col;
};
// function:建立矩阵
void Create_matrix(Matrix &matrix, int m, int n) {
    matrix.matrix = (ElemType **)malloc(sizeof(ElemType *)*m);
    if (matrix.matrix == NULL) {
        std::cout << "[Create_matrix]|ElemType ** 空间分配失败" << std::endl;
        system("pause");
        exit(-1);
    } 
    for (int i=0; i<m; i++) {
        matrix.matrix[i] = (ElemType *)malloc(sizeof(ElemType)*n);
        if (matrix.matrix[i] == NULL) {
            std::cout << "[Create_matrix]|ElemType * 空间分配失败" << std::endl;
            system("pause");
            exit(-1);
        }
    }
    matrix.row = m;
    matrix.col = n;
    // 下面输入矩阵数据
    std::cout << "请输入m行n列数据：" << std::endl;
    for (int i=0; i<matrix.row; i++) {
        for (int j=0; j<matrix.col; j++) {
            std::cin >> matrix.matrix[i][j];
        }
    }
}

// function:寻找马鞍点
/*
    算法：首次遍历，保存各行最小值，各列最大值。再次遍历比较
    时间复杂度：O(n^2)
*/
void Find_saddle_point(Matrix matrix) {
    ElemType row_smallest[matrix.row];
    ElemType col_biggest[matrix.col];
    for (int i=0; i<matrix.row; i++) { // 保存各行最小值
        int small_one = INT_MAX;
        for (int j=0; j<matrix.col; j++) {
            if (matrix.matrix[i][j] < small_one)
                small_one = matrix.matrix[i][j];
        }
        row_smallest[i] = small_one;
    }
    for (int i=0; i<matrix.col; i++) { // 保存各列最小值
        int big_one = INT_MIN;
        for (int j=0; j<matrix.row; j++) {
            if (matrix.matrix[j][i] > big_one)
                big_one = matrix.matrix[j][i];
        }
        col_biggest[i] = big_one;
    }
    int tag = 0; // 用于判断是否没有结果
    for (int i=0; i<matrix.row; i++) { // 遍历，看每个值是否满足行等于该行最大值，列等于该列最大值
        for (int j=0; j<matrix.col; j++) {
            if (matrix.matrix[i][j] == row_smallest[i] && matrix.matrix[i][j] == col_biggest[j]) {
                tag = 1;
                // std::cout << "有效坐标为：(" << i+1 << "," << j+1 << ")" << std::endl; 正常交互
                std::cout << i << " " << j << " " << matrix.matrix[i][j] << std::endl;
            }
        }
    }
    if (tag == 0)
        std::cout << "None";
}

// function:释放空间
void Free_space(Matrix &matrix) {
    for (int i=0; i<matrix.row; i++) {
        free(matrix.matrix[i]);
    }
    free(matrix.matrix);
    matrix.matrix = NULL;
}

int main() {
    Matrix matrix;
    int m, n;
    std::cout << "请输入矩阵的行和列(先行后列)：";
    std::cin >> m >> n;
    Create_matrix(matrix, m, n);
    Find_saddle_point(matrix);
    Free_space(matrix);
    system("pause");
    return 0;
}