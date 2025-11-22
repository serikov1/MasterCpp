#include <cassert>
#include <limits>

template <int N>
struct Fibonacci
{
    static inline constexpr int prev = Fibonacci<N-1>::value;
    static inline constexpr int prev_prev = Fibonacci<N-2>::value;

    static inline constexpr int value = prev + prev_prev;

    static_assert(value <= std::numeric_limits<int>::max());
    
};

template <>
struct Fibonacci<1>
{
    static inline constexpr int value = 1;
};

template <>
struct Fibonacci<2>
{
    static inline constexpr int value = 1;
};

template <int N>
inline constexpr int Fibonacci_v = Fibonacci<N>::value;


int main()
{
    static_assert(Fibonacci_v<1> == 1);
    static_assert(Fibonacci_v<2> == 1);
    static_assert(Fibonacci_v<3> == 2);
    static_assert(Fibonacci_v<4> == 3);
    static_assert(Fibonacci_v<5> == 5);
    static_assert(Fibonacci_v<10> == 55);
    static_assert(Fibonacci_v<15> == 610);

    //static_assert(Fibonacci_v<47> > 0);
    return 0;
}