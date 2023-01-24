/*
    程序描述：K个窗口(队列)，N个顾客，给出N个顾客的到达时间和持续业务时间
    输出结构：平均等待时间(小数点后一位)、最长等待时间、最后完成时间
             按编号递增输出每个窗口服务人数
    思路：顾客组成一个队列，每个窗口结构体(结束时间，状态，服务人数)
        统计顾客最开始时间+最终结束时间
        for (最开始：最终) 每一秒更新状态
        最长处理时间60分钟
*/

#include<bits/stdc++.h>
#include <iomanip>

#define INITSIZE 100
#define INCREASESIZE 50

struct Customer {
    int arrive_time; // 到达时间
    int thing_time; // 事务处理时间
};

struct Queue {
    Customer *base; // 队列的空间上的起点，使用动态分配
    int top; // 队头
    int bottom; // 队尾
    int length; // 队列实时长度
    int size;  // 队列总长度
};

// function:初始化队列
void Init_queue(Queue &queue) {
    queue.base = (Customer *)malloc(sizeof(Customer)*INITSIZE);
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
void Queue_push(Queue &queue, Customer customer) {
    if (queue.length ==  queue.size-1) {  // 队列满判断(循环队列放入元素最多queue.size-1)：也可以使用if ((queue.top+1)%queue.size == queue.bottem)
        // 扩容方式：申请新大小空间，将原序列复制后，释放原序列
        std::cout << "队列发生扩容！" << std::endl;
        Customer *new_base = (Customer *)malloc(sizeof(Customer)*(queue.size+INCREASESIZE));
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
    queue.base[queue.top] = customer;
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
void Queue_pop(Queue &queue, Customer &customer) {
    if (Queue_empty(queue)) {
        std::cout << "队列为空，不可出队列" << std::endl;
        system("pause");
        exit(0);
    }
    customer = queue.base[queue.bottom];
    queue.bottom = (queue.bottom+1) % queue.size;
    queue.length--;
}

// function:释放队列所分配的空间
void Freespace_queue(Queue &queue) {
    free(queue.base);
    queue.base = NULL;
}

// function:将数据输入队列中
void Create_queue(Queue &queue, int N) {
    int a_time = 0, t_time = 0; // a_time代表arrive_time，t_time代表thing_time
    for (int i=0; i<N; i++) {
        std::cin >> a_time >> t_time;
        if (t_time > 60) // 最长处理时间为60
            t_time = 60;
        Customer new_customer;
        new_customer.arrive_time = a_time;
        new_customer.thing_time = t_time;
        Queue_push(queue, new_customer);
    }
}

// function:具体进行银行服务的逻辑
/*
    重点：多个窗口选择时，优先最小
        输出N位顾客的平均等待时间，最长等待时间，最后完成时间，统计每个窗口服务顾客数
*/
/*
    算法：以时间循环，判断每秒时间的情况，存储顾客的结束时间，到达结束时间时状态更新。
         同时对每秒进行循环判断，防止同一秒多个人到达
*/
void Bank_service(Queue &queue, int M, int N) {
    // 为了精简代码，便于大家观看，此处均使用静态分配
    int window_endtime[M] = {0}; // 代表每个窗口当前任务结束时间
    int window_customer_num[M] = {0};
    int start_time = queue.base[queue.bottom].arrive_time; // 开始时间，根据题中条件默认输入数据已经按照到达时间排序(第一位的到达时间一定最早)
    int now_time = start_time; // 当前时间
    int longest_time = INT_MIN;
    double average_waittime = 0.0;
    Customer cur_customer; // 当前顾客等待分配顾客
    Queue_pop(queue, cur_customer);
    int last_data = -1;
    while (!Queue_empty(queue)) { // 栈不空进行逻辑
        int tag = 0; // tag等于0代表当前无效
        int window_index = -1; // 代表有效窗口序号
        for (int i=0; i<M; i++) { // 判断是否顾客的到达时间大于每个窗口的结束时间
            if (now_time >= window_endtime[i]) {
                tag = 1;
                window_index = i;
                break;
            }
        }
        if (tag == 1 && cur_customer.arrive_time <= now_time) { // 窗口空缺+有人等候
            last_data = cur_customer.arrive_time;
            window_endtime[window_index] = now_time + cur_customer.thing_time;
            window_customer_num[window_index]++;
            if (now_time - cur_customer.arrive_time > longest_time) { // 计算最长等待时间
                longest_time = now_time - cur_customer.arrive_time;
            }
            average_waittime += (double)(now_time - cur_customer.arrive_time);
            if (!Queue_empty(queue)) {
                Queue_pop(queue, cur_customer); // 下一位准备
                
            }
            else {
                continue;
            }
        }
        // now_time增加的三种情况：第一次/前后两个不是同一时间/前后是同一时间但是没有空位置
        if (last_data == -1 || last_data != cur_customer.arrive_time || tag == 0)
            now_time++;
    }
    // 安排最后一位
    int index = 0;
    int t = INT_MAX; // 寻找最早结束的
    for (int i= 0; i<M; i++) {
        if (window_endtime[i] < t) {
            t = window_endtime[i];
            index = i;
        }
    }
    // 边界情况处理——针对一个人
    if (cur_customer.arrive_time < window_endtime[index])
        average_waittime += window_endtime[index] - cur_customer.arrive_time;
    if (cur_customer.arrive_time < window_endtime[index] && window_endtime[index] - cur_customer.arrive_time > longest_time)
        longest_time = window_endtime[index] - cur_customer.arrive_time;
    if (window_endtime[index] < cur_customer.arrive_time)
        window_endtime[index] += cur_customer.arrive_time;
    if (longest_time == INT_MIN)
        longest_time = 0;
    window_endtime[index] += cur_customer.thing_time;
    window_customer_num[index]++;
    int end_time = INT_MIN;
    // 栈空时特殊处理可能现存的至多M位顾客，为了统计最终时间
    for (int i=0; i<M; i++) { // 寻找最大的即可
        if (window_endtime[i] > end_time) {
            end_time = window_endtime[i]; 
        }
    }
    // 题目要求：平均时间输出1位小数(std::setiosflags(std::ios::fixed) << std::setprecision(1))
    std::cout << "平均等待时间，最长等待时间，最后完成时间分别为：" << std::setiosflags(std::ios::fixed) << std::setprecision(1) << average_waittime/N << " " << longest_time << " " << end_time << std::endl;
    std::cout << "每个窗口服务的人数为:"; 
    for (int i=0; i<M; i++) {
        std::cout << window_customer_num[i];
        if (i != M-1) {
            std::cout << " ";
        }
    }
}

int main() {
    Queue queue;
    Init_queue(queue);
    int N = 0, M = 0;
    std::cout << "请输入顾客数N：";
    std::cin >> N;
    Create_queue(queue, N);
    std::cout << "请输入窗口数：";
    std::cin >> M;
    Bank_service(queue, M, N);
    Freespace_queue(queue);
    system("pause");
    return 0;
}