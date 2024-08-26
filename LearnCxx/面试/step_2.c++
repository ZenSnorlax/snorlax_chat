#include <iostream>
#include <utility> // std::forward

void process(int &x) { std::cout << "Lvalue reference: " << x << std::endl; }

void process(int &&x) { std::cout << "Rvalue reference: " << x << std::endl; }

template <typename T> void forwarder(T &&arg) {
    process(std::forward<T>(arg)); // 完美转发
}

int main() {
    int a = 5;
    forwarder(std::move(a));
    forwarder(a);  // 调用 process(int&)，传递左值引用
    forwarder(10); // 调用 process(int&&)，传递右值引用
    return 0;
}
