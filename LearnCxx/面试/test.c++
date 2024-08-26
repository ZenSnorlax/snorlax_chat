#include <iostream>

// 抽象类定义了纯虚函数
class Shape {
  public:
    virtual void draw() const = 0; // 纯虚函数
    virtual ~Shape() = default;    // 虚析构函数
};

// 派生类实现纯虚函数
class Circle : public Shape {
  public:
    void draw() const override { std::cout << "Drawing a circle" << std::endl; }
};

// 另一个派生类实现纯虚函数
class Square : public Shape {
  public:
    void draw() const override { std::cout << "Drawing a square" << std::endl; }
};

int main() {
    Shape *shape1 = new Circle();
    Shape *shape2 = new Square();

    shape1->draw(); // 输出: Drawing a circle
    shape2->draw(); // 输出: Drawing a square

    delete shape1;
    delete shape2;

    return 0;
}
