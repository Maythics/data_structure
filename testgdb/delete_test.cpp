#include <iostream>
#include <cstring>

class ShallowCopy {
public:
    char* data;

    ShallowCopy(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // 拷贝构造函数（浅复制）
    ShallowCopy(const ShallowCopy& other) {
        data = other.data; // 直接复制指针
    }

    ~ShallowCopy() {
        delete[] data; // 释放内存
    }
};

int main() {
    ShallowCopy obj1("Hello");
    ShallowCopy obj2 = obj1; // 使用拷贝构造函数进行浅复制

    std::cout << "obj1.data: " << obj1.data << std::endl;
    std::cout << "obj2.data: " << obj2.data << std::endl;

    // 当 obj1 和 obj2 的析构函数被调用时，会出现双重释放的情况
    return 0;
}


