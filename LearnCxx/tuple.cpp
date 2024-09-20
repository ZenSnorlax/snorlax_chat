#include <iostream>
#include <string>

// TupleElement 定义
template<std::size_t Index, typename T>
struct TupleElement {
    T value;
};

// 递归基础类
template<typename... Types>
struct TupleImpl;

// 递归终止条件
template<>
struct TupleImpl<> {};

// 递归定义
template<typename Head, typename... Tail>
struct TupleImpl<Head, Tail...>
    : public TupleElement<sizeof...(Tail), Head>, public TupleImpl<Tail...> {
    
    // 只在继承 TupleElement 时使用 using
    using TupleElement<sizeof...(Tail), Head>::value;
    
    TupleImpl(Head head, Tail... tail)
        : TupleElement<sizeof...(Tail), Head>{head}, TupleImpl<Tail...>{tail...} {}

    // 获取元素的递归方法
    template<std::size_t N>
    auto& get() {
        return TupleImpl<Tail...>::template get<N>();
    }

    template<>
    auto& get<sizeof...(Tail)>() {
        return this->value;
    }
};

// 对外接口
template<typename... Types>
struct Tuple : public TupleImpl<Types...> {
    Tuple(Types... values) : TupleImpl<Types...>{values...} {}

    template<std::size_t N>
    auto& get() {
        return this->TupleImpl<Types...>::template get<N>();
    }
};

int main() {
    Tuple<int, double, std::string> t(1, 2.5, "Hello");

    std::cout << t.get<0>() << std::endl;  // 打印第一个元素: 1
    std::cout << t.get<1>() << std::endl;  // 打印第二个元素: 2.5
    std::cout << t.get<2>() << std::endl;  // 打印第三个元素: Hello

    return 0;
}
