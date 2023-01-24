/*
    程序描述：依据高铁号的高铁座位位置的判断
        一等座   A(窗口) C(过道) D(过道) F(窗口)
        二等座  A(窗口) B(中间) C(过道) D(过道) F(窗口)
        输入无效时输出：输入错误     有效：1-17   不区分大小写
*/
# include<bits/stdc++.h>

struct String {
    char *s;
    int length;
};

// function:建立字符串
void Create_string(String &string, char input[100]) {
    string.s = (char *)malloc(sizeof(String));
    if (string.s == NULL) {
        std::cout << "[Create_string]fail to allocate" << std::endl;
        system("pause");
        exit(-1);
    }
    for (int i=0; input[i] != '\0'; i++) {
        string.s[string.length++] = input[i];
    }
}

// function:判断位置
/*
    算法：切割字符串，判断字符即可。
        无效的几种情况：
            1.数组不属于[1,17]
            2.字符非A B C D F
*/
void Judge(String string) {
    if (string.length > 3 || string.length <= 1) { // 字符超过3个或小于1个肯定错误
        std::cout<< "输入错误" << std::endl;
        return ;
    }
    for (int i=0; i<string.length; i++) { // 因为不区分大小写，所以统一变大写
        if (string.s[i]>='a' && string.s[i] <= 'z') {
            string.s[i] = 'A'+string.s[i]-'a';
        }
    }
    int num = 0;
    for (int i=0; i<string.length-1; i++) {
        if (string.s[i] >= '9' || string.s[i] <= '0') { // 前几个非数字
            std::cout << "输入错误" << std::endl;
            return ;
        }
        num = num*10+(string.s[i]-'0');
    }
    if (num < 1 || num > 17) { // 数字不在[1,17]
        std::cout << "输入错误" << std::endl;
        return ;
    }
    switch(string.s[string.length-1]) {
        case 'A':
            std::cout << "窗口" << std::endl;
            break;
        case 'B':
            std::cout << "中间" << std::endl;
            break;
        case 'C':
            std::cout << "过道" << std::endl;
            break;
        case 'D':
            std::cout << "过道" << std::endl;
            break;
        case 'F':
            std::cout << "窗口" << std::endl;
            break;
        default:
            std::cout << "输入错误" << std::endl;
            break;
    }
}

// function:释放空间
void Free_space(String string) {
    free(string.s);
    string.s = NULL;
    string.length = 0;
}

int main() {
    std::cout << "请输入座位号(数组1-17，字符包括ABCDF)：";
    char input[100]; // 此处申请静态，如果大于的话会被阶段。直接判定无效即可
    std::cin >> input;
    String string;
    Create_string(string, input);
    Judge(string);
    Free_space(string);
    system("pause");
    return 0;
}
