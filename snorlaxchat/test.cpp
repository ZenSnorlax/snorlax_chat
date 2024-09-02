#include <iostream>
#include <memory>

void test_close1(int *fd1) {
    std::cout << "test_close1" << std::endl;
    delete fd1; // 确保释放资源
}

void test_close2(int *fd2) {
    std::cout << "test_close2" << std::endl;
    delete fd2; // 确保释放资源
}
class A {
  public:
    ~A() { std::cout << "A" << std::endl; }
};
class Test {
  public:
    Test()
        : p(new int(10)), Fd1(new int(1), &test_close1),
          Fd2(new int(2), &test_close2), a() {
        std::cout << "construct" << std::endl;
    }

    ~Test() {
        std::cout << "destruct" << std::endl;
        delete p;
        std::cout << "delete p" << std::endl;
    }

  private:
    int *p;
    A a;
    std::unique_ptr<int, decltype(&test_close1)> Fd1;
    std::unique_ptr<int, decltype(&test_close2)> Fd2;
    
};

int main() {
    Test t;
    return 0;
}
