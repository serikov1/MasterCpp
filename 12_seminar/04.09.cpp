#include <type_traits>
#include <utility>

template <typename T>
struct is_class_helper
{
private:
    template <typename C>
    static std::true_type test(int C::*);

    template <typename C>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
struct is_class : std::bool_constant<is_class_helper<T>::value> {};

template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;

// ===========================================================

template <typename T>
struct add_const { using type = T const; };

template <typename T>
struct remove_const { using type = T; };

template <typename T>
struct remove_const<T const> { using type = T; };

template <typename T> using add_const_t = typename add_const<T>::type;
template <typename T> using remove_const_t = typename remove_const<T>::type;

// ===========================================================

template <bool B, typename T, typename F>
struct conditional { using type = T; };

template <typename T, typename F>
struct conditional<false, T, F> { using type = F; };

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

// ===========================================================

template <typename T>
struct decay {
private:
    using U = remove_const_t<T>;
public:
    using type = conditional_t<
        std::is_array_v<U>,
        std::remove_extent_t<U>*, 

        conditional_t<
            std::is_function_v<U>,
            std::add_pointer_t<U>,
            remove_const_t<T>
        >
    >;
};

template <typename T>
using decay_t = typename decay<T>::type;

// ===========================================================

struct A {};
union U { int x; };

void func(int) {}

int main() {

    // ---------- is_class ----------
    static_assert(is_class_v<A> == true);
    static_assert(is_class_v<U> == true);
    static_assert(is_class_v<int> == false);
    static_assert(is_class_v<int*> == false);

    // ---------- add/remove const ----------
    static_assert(std::is_same_v<add_const_t<int>, int const>);
    static_assert(std::is_same_v<remove_const_t<int const>, int>);
    static_assert(std::is_same_v<remove_const_t<int>, int>);

    // ---------- conditional ----------
    static_assert(std::is_same_v<conditional_t<true, int, double>, int>);
    static_assert(std::is_same_v<conditional_t<false, int, double>, double>);

    // ---------- decay ----------
    static_assert(std::is_same_v<decay_t<int>, int>);
    static_assert(std::is_same_v<decay_t<int const>, int>);
    static_assert(std::is_same_v<decay_t<int[3]>, int*>);
    static_assert(std::is_same_v<decay_t<decltype(func)>, void(*)(int)>);

    return 0;
}
