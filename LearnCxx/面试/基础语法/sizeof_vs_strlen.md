# C++中 `sizeof`和`strlen`的区别
### 1. 功能

- **`sizeof`**：`sizeof` 是一个运算符，用于返回一个对象或类型在内存中占用的字节数。它在编译时计算，不依赖于对象的内容，只依赖于其类型。

  ```cpp
  int arr[10];
  std::cout << sizeof(arr);  // 返回整个数组的字节数（通常是 40，假设 int 是 4 字节）
  ```

- **`strlen`**：`strlen` 是一个函数，用于返回以空字符（`\0`）结尾的字符串的长度（不包括空字符本身）。`strlen` 依赖于字符串的内容，它从字符串的起始位置遍历直到遇到空字符。

  ```cpp
  const char* str = "Hello";
  std::cout << strlen(str);  // 返回字符串的长度（5）
  ```

### 2. 适用类型

- **`sizeof`**：`sizeof` 可以用于任何数据类型，包括内置类型（如 `int`、`double`）、结构体、类、数组、指针等。

  ```cpp
  double d;
  std::cout << sizeof(d);  // 返回 double 类型的大小（通常是 8 字节）
  ```

- **`strlen`**：`strlen` 只适用于 C 风格的字符串，即以 `\0` 结尾的字符数组或字符指针。它不能用于其他类型的数据。

  ```cpp
  const char* str = "C++";
  std::cout << strlen(str);  // 返回字符串 "C++" 的长度（3）
  ```

### 3. 返回值类型

- **`sizeof`**：`sizeof` 返回的类型是 `size_t`，它是一个无符号整数类型，表示对象或类型的大小。

  ```cpp
  std::cout << sizeof(int);  // 返回 int 类型的字节大小
  ```

- **`strlen`**：`strlen` 也返回 `size_t` 类型的值，表示字符串的长度。

  ```cpp
  const char* str = "example";
  std::cout << strlen(str);  // 返回字符串 "example" 的长度（7）
  ```

### 4. 计算结果

- **`sizeof`**：`sizeof` 返回的大小包括了整个对象的大小。例如，`sizeof(arr)` 返回的是数组 `arr` 的总大小（数组元素的个数乘以单个元素的大小）。

  ```cpp
  int arr[10];
  std::cout << sizeof(arr);  // 返回 40，如果 int 是 4 字节
  ```

- **`strlen`**：`strlen` 只计算字符串的实际字符数，不包括字符串末尾的空字符。

  ```cpp
  char str[20] = "Hello";
  std::cout << strlen(str);  // 返回 5
  std::cout << sizeof(str);  // 返回 20，因为数组大小固定为 20 字节
  ```

### 5. 编译时 vs 运行时

- **`sizeof`**：在编译时确定，计算的是类型或对象的大小。

- **`strlen`**：在运行时确定，计算的是字符串中实际字符的数量。

### 总结

- `sizeof` 是一个编译时运算符，用于返回数据类型或对象所占内存的字节数。
- `strlen` 是一个运行时函数，用于计算以空字符结尾的字符串的长度（字符数）。
