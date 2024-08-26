
# C++11 常用新特性

## 1. 自动类型推导（auto）
`auto` 关键字允许编译器自动推导变量的类型，减少了显式类型声明的复杂性。
```cpp
auto x = 10;   // 自动推导为 int
auto y = 3.14; // 自动推导为 double
```

## 2. 范围 for 循环（Range-based for loop）
C++11 引入了一种新的 for 循环语法，用于遍历容器中的元素。
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};
for (auto& v : vec) {
    std::cout << v << std::endl;
}
```

## 3. 智能指针（Smart Pointers）
C++11 提供了 `std::unique_ptr` 和 `std::shared_ptr` 来进行自动内存管理，避免手动 `delete` 和内存泄漏。
```cpp
std::unique_ptr<int> p1(new int(10));
std::shared_ptr<int> p2 = std::make_shared<int>(20);
```

## 4. Lambda 表达式
Lambda 表达式提供了一种便捷的方式来定义匿名函数，并可以捕获外部变量。
```cpp
auto sum = [](int a, int b) { return a + b; };
std::cout << sum(3, 4) << std::endl; // 输出 7
```

## 5. 右值引用与移动语义（Rvalue References and Move Semantics）
C++11 引入了右值引用（`T&&`），允许开发者实现移动语义，优化资源管理。
```cpp
std::vector<int> vec1 = {1, 2, 3};
std::vector<int> vec2 = std::move(vec1); // vec1 的内容被移动到 vec2
```

## 6. `std::thread` 和并发支持
C++11 标准库提供了多线程支持，通过 `std::thread` 类可以轻松创建线程，配合 `std::mutex`、`std::condition_variable` 等同步机制使用。
```cpp
std::thread t([]{ std::cout << "Hello from thread!" << std::endl; });
t.join();
```

## 7. 初始化列表（Initializer List）
初始化列表语法使得初始化容器更加方便。
```cpp
std::vector<int> vec = {1, 2, 3, 4};
```

## 8. `nullptr` 关键字
C++11 引入了 `nullptr` 关键字，用来代替 C 语言中的 `NULL` 指针，避免类型不匹配问题。
```cpp
int* ptr = nullptr;
```

## 9. `constexpr` 关键字
`constexpr` 允许编译时计算常量表达式，优化运行时性能。
```cpp
constexpr int square(int x) { return x * x; }
const int result = square(5); // 在编译时计算
```

## 10. `enum class`
`enum class` 提供了强类型枚举，避免了普通枚举可能出现的命名冲突问题。
```cpp
enum class Color { Red, Green, Blue };
Color c = Color::Red;
```

## 11. 统一的初始化语法（Uniform Initialization Syntax）
统一初始化语法允许使用大括号初始化任何类型的对象，包括数组、容器、类等。
```cpp
int arr[] = {1, 2, 3};
std::vector<int> vec = {4, 5, 6};
```

## 12. `decltype` 关键字
`decltype` 可以获取表达式的类型，用于推导复杂类型。
```cpp
int x = 10;
decltype(x) y = 20; // y 的类型与 x 相同，即 int
```

## 13. 静态断言（`static_assert`）
`static_assert` 允许在编译期检查条件，增强编译期的类型安全。
```cpp
static_assert(sizeof(int) == 4, "Unexpected int size!");
```
