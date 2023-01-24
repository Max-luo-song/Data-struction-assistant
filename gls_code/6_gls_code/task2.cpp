/*
    分蛋糕问题，使用队列结构解决
*/
#include<bits/stdc++.h>
#define INITSIZE 100
#define INCREASESIZE 50

typedef int ElemType;

struct Queue {
    ElemType *base; // 队列的空间上的起点，使用动态分配
    int top; // 队头
    int bottom; // 队尾
    int length; // 队列实时长度
    int size;  // 队列总长度
};

// function:初始化队列
void Init_queue(Queue &queue) {
    queue.base = (ElemType *)malloc(sizeof(ElemType)*INITSIZE);
    if (queue.base == NULL) {
        std::cout << "[Init_queue]|申请空间失败" << std::endl;
        exit(0);
    }
    queue.top = 0;
    queue.bottom = 0;
    queue.length = 0;
    queue.size = INITSIZE;
}

// function:元素入队列
void Queue_push(Queue &queue, int val) {
    if (queue.length ==  queue.size-1) {  // 队列满判断(循环队列放入元素最多queue.size-1)：也可以使用if ((queue.top+1)%queue.size == queue.bottem)
        // 扩容方式：申请新大小空间，将原序列复制后，释放原序列
        std::cout << "队列发生扩容！" << std::endl;
        ElemType *new_base = (ElemType *)malloc(sizeof(ElemType)*(queue.size+INCREASESIZE));
        if (new_base == NULL) {
            std::cout << "[Queue_push]|申请空间失败" << std::endl;
            exit(0);
        }
        int i = 0; // 用于作为new_base的索引
        while (queue.top != queue.bottom) {
            new_base[i] = queue.base[queue.bottom];
            queue.bottom = (queue.bottom+1) % queue.size;
            i++;
        }
        free(queue.base);
        queue.base = new_base;
        new_base = NULL;
        queue.bottom = 0; // 队列尾部重新对齐
        queue.top = queue.length; // top的值始终等于队列元素数
        queue.size = queue.length + INCREASESIZE;
    }
    queue.base[queue.top] = val;
    queue.top = (queue.top+1)%queue.size; // 向前移位
    queue.length++; 
}

// function:判断队列是否为空，空返回true
bool Queue_empty(Queue queue) {
    if (queue.length == 0)
        return true;
    else
        return false;
}

// function:元素出队列，并用val保存
void Queue_pop(Queue &queue, int &val) {
    if (Queue_empty(queue)) {
        std::cout << "队列为空，不可出队列" << std::endl;
        system("pause");
        exit(0);
    }
    val = queue.base[queue.bottom];
    queue.bottom = (queue.bottom+1) % queue.size;
    queue.length--;
}

void Queue_print(Queue queue) {
    int t = queue.bottom;
    std::cout << "下面输出队列" << std::endl;
    while (t != queue.top) {
        std::cout << queue.base[t] << std::endl;
        t = (t+1) % queue.size;
    }
    return ;
}

// function:释放队列所分配的空间
void Freespace_queue(Queue &queue) {
    free(queue.base);
    queue.base = NULL;
    std::cout << "队列空间成功释放!" << std::endl;
}

/*
    完成功能：分蛋糕，顺序遍历，满足要求后计数并清零累加值
*/
void Give_cakes(Queue &queue) {
    std::cout << "请输入朋友数目n和蛋糕范围k:";
    int n, k;
    std::cin >> n >> k;
    std::cout << "请输入各块蛋糕的重量(上限为n):";
    for (int i=0; i<n; i++) {
        int temp;
        std::cin >> temp;
        Queue_push(queue,temp);
    }
    int sum = 0;
    int result = 0;
    for (int i=0; i<n; i++) {
        int temp;
        Queue_pop(queue, temp);
        sum += temp;
        if (sum >= k) {
            result++;
            sum = 0;
        }
    }
    if (sum > 0) { // 最后需要额外判断一下，题中要求是分到蛋糕的小朋友数
        result++;
    }
    std::cout << "结果为：" << result << std::endl;
}

int main() {
    Queue queue;
    Init_queue(queue);
    Give_cakes(queue);
    Freespace_queue(queue);
    system("pause");
    return 0;
}