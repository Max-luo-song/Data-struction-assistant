/*
    程序简述：线性表——数组练习
             考察点：1.从文件中读入数据
                     2.顺序遍历数组
                     3.逆序遍历数组
                     4.数组去重
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>

#define MAXSIZE 100

// 数组结构
struct LinearList_array {
    int array[MAXSIZE];
    int length;
};

// fucntion:初始化建立线性数组
LinearList_array* Init_LinearList_array(LinearList_array *linearList_array) {
    linearList_array = (LinearList_array *)malloc(sizeof(LinearList_array));
    linearList_array->length = 0;
    return linearList_array;
}

// function:从文件中读取数据放入线性数组
void ReadFile_linearList_array(LinearList_array *linearList_array) {
    std::ifstream readFile;
    readFile.open("data.txt", std::ios_base::in);
    if (!readFile.is_open()) {
        std::cout << "data.txt fail to open!" << std::endl;
    }
    while (!readFile.eof()) {
        readFile >> linearList_array->array[linearList_array->length];
        linearList_array->length++;
        if (readFile.fail())
            break;
    }
    readFile.close(); // 文件打开记得关闭
}

// function:线性数组正序输出
void Print_positive_linearList_array(LinearList_array *linearList_array) {
    std::cout << "线性表数组形式——正向输出:\n";
    for (int i=0; i<linearList_array->length; i++) {
        std::cout << linearList_array->array[i];
        if (i != linearList_array->length-1)
            std::cout << " ";
    } 
    std::cout << std::endl;
}

// function:线性数组逆序输出
void Print_negitive_linearList_array(LinearList_array *linearList_array) {
    std::cout << "线性表数组形式——逆向输出:\n";
    for (int i=linearList_array->length-1; i>=0; i--) {
        std::cout << linearList_array->array[i];
        if (i != 0)
            std::cout << " ";
    } 
    std::cout << std::endl;
}

// function:线性数组删除重复元素
/*
    算法：两层循环，每次删除所有字符全部向前移动
*/
void Delete_the_repetion_linearList_array(LinearList_array *linearList_array) {
    for (int i=0; i<linearList_array->length; i++) {
        for (int j=i+1; j<linearList_array->length; j++) {
            if (linearList_array->array[i] == linearList_array->array[j]) {
                for (int k=j; k<linearList_array->length-1; k++) {
                    linearList_array->array[k] = linearList_array->array[k+1];
                }
                linearList_array->length--;
            }
        }
    }

    // 输出删除后的结果
    std::cout << "删除之后的结果是:\n";
    Print_positive_linearList_array(linearList_array);
}

// function:释放所有申请的空间
void Free_the_linearList_array(LinearList_array *linearList_array) {
    free(linearList_array);
    std::cout << "释放空间完成\n";
}

int main() {
    LinearList_array *linearList_array;
    linearList_array = Init_LinearList_array(linearList_array);
    ReadFile_linearList_array(linearList_array);
    Print_positive_linearList_array(linearList_array);
    Print_negitive_linearList_array(linearList_array);
    Delete_the_repetion_linearList_array(linearList_array);
    Free_the_linearList_array(linearList_array);
    system("pause");
    return 0;
}
