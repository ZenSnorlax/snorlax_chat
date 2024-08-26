#include <iostream>
#include <cstring> // 推荐使用 <cstring> 而不是 <string.h>

class MyString {
  private:
    char *data;

  public:
    // 构造函数
    explicit MyString(const char *str = "") : data(nullptr) {
        if (str) {
            data = new char[strlen(str) + 1];
            std::strcpy(data, str);
            std::cout << "Construct: " << data << std::endl;
        }
    }

    // 移动构造函数
    MyString(MyString &&other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Move Construct" << std::endl;
    }

    // 移动赋值运算符
    MyString& operator=(MyString &&other) noexcept {
        if (this != &other) {
            delete[] data;  // 释放当前对象的资源
            data = other.data;
            other.data = nullptr;
            std::cout << "Move Assign" << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~MyString() {
        delete[] data;
        std::cout << "Destruct" << std::endl;
    }

    // 禁用复制构造函数和复制赋值运算符
    MyString(const MyString &) = delete;
    MyString& operator=(const MyString &) = delete;
};

int main() {
    MyString a("Hello");
    MyString b(std::move(a));  // 调用移动构造函数
    MyString c;
    c = std::move(b);          // 调用移动赋值运算符
    return 0;
}
