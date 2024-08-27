
# C++ 中虚函数的原理

C++ 中虚函数的原理涉及到虚函数表（Virtual Table，简称 vtable）和虚指针（Virtual Pointer，简称 vptr）的机制。虚函数使得 C++ 能够实现运行时多态，即在运行时根据对象的实际类型来决定调用哪个函数。

## 虚函数的工作原理

### 1. 虚函数表（vtable）
- 当一个类包含虚函数时，编译器为该类创建一个虚函数表（vtable）。虚函数表是一个函数指针的数组，其中每个元素指向类中的一个虚函数。
- 如果一个类继承自另一个类，并且重写了基类中的虚函数，那么派生类的虚函数表中相应的条目会指向派生类的函数，而不是基类的函数。

### 2. 虚指针（vptr）
- 每个包含虚函数的对象实例都有一个隐藏的指针，称为虚指针（vptr）。这个指针指向该对象所属类的虚函数表。
- 当对象被创建时，编译器负责将 vptr 初始化为指向该对象所属类的 vtable。

### 3. 调用虚函数
- 当通过基类指针或引用调用虚函数时，程序会使用对象的 vptr 查找对应的 vtable，然后通过 vtable 调用正确的函数。
- 由于这种查找是在运行时进行的，所以虚函数支持运行时多态。

## 示例及解释

```cpp
#include <iostream>

class Base {
public:
    virtual void show() {
        std::cout << "Base show" << std::endl;
    }
    virtual ~Base() = default; // 虚析构函数
};

class Derived : public Base {
public:
    void show() override {
        std::cout << "Derived show" << std::endl;
    }
};

int main() {
    Base* basePtr = new Derived();
    basePtr->show();  // 调用的是 Derived::show()
    delete basePtr;
    return 0;
}
```

### 解释：
- `Base` 类有一个虚函数 `show()`，因此编译器会为 `Base` 类创建一个 vtable，其中存储指向 `Base::show()` 的指针。
- `Derived` 类继承自 `Base`，并重写了 `show()`。因此，`Derived` 类也有一个 vtable，其中相应条目指向 `Derived::show()`。
- 在 `main()` 函数中，`basePtr` 指向一个 `Derived` 对象。当调用 `basePtr->show()` 时，程序会使用 `basePtr` 的 vptr 指向的 vtable，并调用 `Derived::show()`，实现了运行时多态。

## 重要性和细节

- **虚函数表是类级别的**：所有相同类型的对象共享同一个 vtable。
- **虚指针是对象级别的**：每个对象都有自己的 vptr，但指向相同类型对象的同一 vtable。
- **虚析构函数**：当一个类有虚函数时，通常也会定义虚析构函数，这样可以确保通过基类指针删除派生类对象时，调用到派生类的析构函数，避免内存泄漏。

通过虚函数表和虚指针，C++ 实现了运行时多态，使得在运行时根据对象的实际类型调用合适的函数成为可能。
