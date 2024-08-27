
# C++ `final` 关键字的作用

在 C++ 中，`final` 关键字用于防止类或虚函数被进一步继承或重写。它有两种主要用途：

## 1. 防止类被继承
如果你不希望某个类被继承，可以将该类声明为 `final`。当一个类被标记为 `final` 后，任何尝试继承该类的操作都会导致编译错误。

```cpp
class Base final {
    // Class implementation
};

// 下面的代码会导致编译错误
class Derived : public Base {
    // Derived class implementation
};
```

## 2. 防止虚函数被重写
如果你不希望子类重写某个虚函数，可以将该虚函数声明为 `final`。这样，当子类尝试重写该虚函数时，编译器会报错。

```cpp
class Base {
public:
    virtual void someFunction() final {
        // Function implementation
    }
};

class Derived : public Base {
public:
    // 下面的代码会导致编译错误，因为 someFunction 被标记为 final
    void someFunction() override {
        // Function implementation
    }
};
```

## 总结
- `final` 关键字用于防止类被继承或虚函数被重写。
- 使用 `final` 可以提高代码的安全性，防止不必要的继承和重写，从而避免潜在的错误。
