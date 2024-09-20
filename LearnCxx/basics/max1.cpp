#include <iostream>

// 通用模板函数
template <typename T>
void func(T t);

// 完全特化：针对 int 类型
template <>
void func<int>(int t) {
    std::cout << "Specialized for int: " << t << std::endl;
}

// 完全特化：针对 double 类型
template <>
void func<double>(double t) {
    std::cout << "Specialized for double: " << t << std::endl;
}

// 完全特化：针对 const char * 类型
template <>
void func<const char *>(const char *t) {
    std::cout << "Specialized for const char *: " << t << std::endl;
}

int main() {
    func(10);
    func(10.5);
    func("Hello");
}
