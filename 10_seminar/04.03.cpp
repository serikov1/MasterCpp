#include <cassert>
#include <iostream>
#include <vector>
#include <type_traits>

template <typename T>
auto handle(T var)
{
    return 0.0;
}

template <>
auto handle<int>(int var)
{
    return var;
}

void push_from_pack(auto& container, auto ... args)
{
    ( (std::is_same_v<decltype(handle(args)), int> ? container.push_back(handle(args)) : void ()), ... );
}

int main()
{
    std::vector<int> vec;
    push_from_pack(vec, 1, 2, 3, "str", 7, -3.5, 9, 0);

    for(auto elem : vec)
    {
        std::cout << elem << "\n";
    }

    return 0;
}