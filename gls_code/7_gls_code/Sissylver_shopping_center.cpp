/*
    程序描述：西西艾弗岛的购物中心问题
            输入array数组(n个数)，和N值，求sun(A),sum(A)的定义是从0到N-1小于数组array的索引
*/
#include<bits/stdc++.h>

struct A {
    int *array;
    int array_length;
};

// function:创建数组
void Create_array(A &a, int n) {
    a.array = (int *)malloc(sizeof(int)*(n+1));
    if (a.array == NULL) {
        std::cout << "内存分配失败" << std::endl;
        system("pause");
        exit(-1);
    }
    a.array_length = n;
    a.array[0] = 0; // 为了满足题意
    std::cout << "请输入n个数：";
    for (int i=1; i<=n; i++) {
        std::cin >> a.array[i];
    }
}

// function:进行主要逻辑计算
/*
    算法：将元素N按照array进行切分，可分为如下几种情况：
        1.N-1 大于 array的最大值
        2.N-1 小于 array的最大值，但大于部分值
        3.N-1 小于所有值
        每切割一次，索引要加一
    时间复杂度：O(n)
*/
int Sum(A a, int N) {
    int result = 0;
    int index = 0; // 代表索引
    if (a.array_length == 1) { // 只有一个元素的特殊情况处理
        if (N-a.array[1] > 0)
            return N-a.array[1];
        else
            return 0;
    }
    for (int i=1; i<=a.array_length; i++) {
        if (N-1 >= a.array[i]) { // N-1比这个大，这一段要累加
            result += (a.array[i]-a.array[i-1])*index;
        }
        else if (a.array[i] > N-1){  // N-1比这个小，但比上一个大，之间的累加
            result += (N-1-a.array[i]+1)*index;
            break;
        }
        index++;
    }
    if (a.array[a.array_length] <= N-1) { // 处理最后一个（之前处理的是最后一段）
        result += index*(N-a.array[a.array_length]);
    }
    return result;
}

// function:释放空间
void Free_space(A &a) {
    free(a.array);
    a.array_length = 0;
    a.array = NULL;
}

int main() {
    int n, N;
    std::cout << "请输入n和N：";
    std::cin >> n >> N;
    A a;
    Create_array(a, n);
    int result = Sum(a, N);
    std::cout << "结果为：" << result << std::endl;
    Free_space(a);
    system("pause");
    return 0;
}