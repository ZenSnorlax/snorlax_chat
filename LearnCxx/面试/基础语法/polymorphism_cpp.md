
# C++ 中的多态

多态（Polymorphism）是面向对象编程中的一个核心概念，它允许对象以不同的形式出现，特别是在同一类型的对象中表现出不同的行为。C++ 中的多态性主要分为**编译时多态**（静态多态）和**运行时多态**（动态多态）两种形式。

## 编译时多态（静态多态）

编译时多态通常通过函数重载（Function Overloading）和运算符重载（Operator Overloading）来实现。编译器在编译时就可以确定调用哪个函数。

**示例：**

```cpp
#include <iostream>

class Print {
public:
    void show(int i) {
        std::cout << "Integer: " << i << std::endl;
    }

    void show(double d) {
        std::cout << "Double: " << d << std::endl;
    }

    void show(const std::string& s) {
        std::cout << "String: " << s << std::endl;
    }
};

int main() {
    Print printer;
    printer.show(10);
    printer.show(3.14);
    printer.show("Hello, world!");
    return 0;
}
```

在这个例子中，`show` 函数被重载了三次，分别接受 `int`、`double` 和 `std::string` 参数。编译器在编译时会根据传递的参数类型选择合适的函数。

## 运行时多态（动态多态）

运行时多态是通过**虚函数**（virtual functions）和**继承**来实现的。在这种情况下，编译器无法在编译时确定调用哪个函数，而是在程序运行时根据对象的实际类型决定调用哪个函数。这种多态性允许不同的子类以不同的方式实现基类中的虚函数。

**示例：**

```cpp
#include <iostream>

class Base {
public:
    virtual void display() const {
        std::cout << "Display from Base" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() const override {
        std::cout << "Display from Derived" << std::endl;
    }
};

void show(const Base& obj) {
    obj.display();
}

int main() {
    Base base;
    Derived derived;

    show(base);      // 调用 Base::display()
    show(derived);   // 调用 Derived::display()
    
    return 0;
}
```

**解释：**

- `Base` 类有一个虚函数 `display`。
- `Derived` 类继承了 `Base` 类，并重写了 `display` 函数。
- 在 `show` 函数中，我们接受一个 `Base` 类型的引用，并调用 `display` 函数。
- 由于 `display` 是虚函数，实际调用的是对象运行时的类型对应的函数，这就是运行时多态的体现。

**注意：**

- 为了实现运行时多态，基类中的函数必须声明为 `virtual`，并且要确保使用指针或引用来调用这些函数。
- 如果子类中的函数需要覆盖基类中的虚函数，推荐使用 `override` 关键字以确保函数正确重写。

多态的优势在于可以使用统一的接口处理不同类型的对象，从而提高代码的灵活性和可扩展性。
