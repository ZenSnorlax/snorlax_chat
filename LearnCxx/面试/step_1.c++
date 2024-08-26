#include <iostream>
#include <string>
#include <utility>

class MyString {
  public:
    // 普通构造函数
    MyString(const char *str) : data(new std::string(str)) {
        std::cout << "Constructed: " << *data << std::endl;
    }

    // 移动构造函数
    MyString(MyString &&other) noexcept : data(other.data) {
        other.data = nullptr; // 确保原对象不再拥有该资源
        std::cout << "Moved" << std::endl;
    }

    // 移动赋值运算符
    MyString &operator=(MyString &&other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
            std::cout << "Move Assigned" << std::endl;
        }
        return *this;
    }

    ~MyString() {
        delete data;
        std::cout << "Destroyed" << std::endl;
    }

  private:
    std::string *data;
};

int main() {
    MyString a("Hello");
    MyString b = std::move(a); // 触发移动构造函数
    a = std::move(b);          // 移动赋值运算符
    return 0;
}
