#include <cassert>
#include <cmath>
#include <exception>
#include <istream>
#include <numeric>
#include <ostream>
#include <sstream>
#include <vector>
#include <optional>
#include <variant>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////

class Exception : public std::exception
{
public:
    explicit Exception(std::string msg) : m_msg(std::move(msg)) {}

    const char* what() const noexcept override
    {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template <typename Derived>
struct addable
{
    friend Derived operator+(Derived lhs, Derived const& rhs)
    {
        lhs += rhs;
        return lhs;
    }
};

template <typename Derived>
struct subtractable
{
    friend Derived operator-(Derived lhs, Derived const& rhs)
    {
        lhs -= rhs;
        return lhs;
    }
};

template <typename Derived>
struct multipliable
{
    friend Derived operator*(Derived lhs, Derived const& rhs)
    {
        lhs *= rhs;
        return lhs;
    }
};

template <typename Derived>
struct dividable
{
    friend Derived operator/(Derived lhs, Derived const& rhs)
    {
        lhs /= rhs;
        return lhs;
    }
};

template <typename Derived>
struct incrementable
{
    friend Derived operator++(Derived& x, int)
    {
        Derived tmp(x);
        ++x;
        return tmp;
    }
};

template <typename Derived>
struct decrementable
{
    friend Derived operator--(Derived& x, int)
    {
        Derived tmp(x);
        --x;
        return tmp;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Rational
    : public addable<Rational<T>>
    , public subtractable<Rational<T>>
    , public multipliable<Rational<T>>
    , public dividable<Rational<T>>
    , public incrementable<Rational<T>>
    , public decrementable<Rational<T>>
{
public:
    Rational(T num = T{}, T den = T{1})
        : m_num(num), m_den(den)
    {
        if (m_den == T{})
        {
            throw Exception("Rational: denominator is zero");
        }
        reduce();
    }

    explicit operator double() const
    {
        return static_cast<double>(m_num) / static_cast<double>(m_den);
    }

    auto& operator+=(Rational const& other)
    {
        auto lcm = std::lcm(m_den, other.m_den);

        m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
        m_den = lcm;

        reduce();
        return *this;
    }

    auto& operator-=(Rational const& other)
    {
        return *this += Rational(-other.m_num, other.m_den);
    }

    auto& operator*=(Rational const& other)
    {
        m_num *= other.m_num;
        m_den *= other.m_den;

        if (m_den == T{})
        {
            throw Exception("Rational: denominator became zero after multiplication");
        }

        reduce();
        return *this;
    }

    auto& operator/=(Rational const& other)
    {
        return *this *= Rational(other.m_den, other.m_num);
    }

    auto& operator++()
    {
        m_num += m_den;
        return *this;
    }

    auto& operator--()
    {
        m_num -= m_den;
        return *this;
    }

    friend std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs)
    {
        auto left  = lhs.m_num * rhs.m_den;
        auto right = rhs.m_num * lhs.m_den;

        if (left < right)  return std::strong_ordering::less;
        if (left > right)  return std::strong_ordering::greater;
        return std::strong_ordering::equal;
    }

    friend bool operator==(Rational const& lhs, Rational const& rhs)
    {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

    friend std::istream& operator>>(std::istream& stream, Rational& r)
    {
        return (stream >> r.m_num).ignore() >> r.m_den;
    }

    friend std::ostream& operator<<(std::ostream& stream, Rational const& r)
    {
        return stream << r.m_num << '/' << r.m_den;
    }

private:
    void reduce()
    {
        if (m_den < T{})
        {
            m_num = -m_num;
            m_den = -m_den;
        }

        auto g = std::gcd(m_num, m_den);

        m_num /= g;
        m_den /= g;
    }

    T m_num{}, m_den{1};
};

///////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

int main()
{
    try
    {
        Rational<int> x = 1, y(2, 1);

        assert((x += y) == Rational<int>(+3, 1));
        assert((x -= y) == Rational<int>(+1, 1));
        assert((x *= y) == Rational<int>(+2, 1));
        assert((x /= y) == Rational<int>(+1, 1));

        assert((x++) == Rational<int>(+1, 1));
        assert((x--) == Rational<int>(+2, 1));
        assert((++y) == Rational<int>(+3, 1));
        assert((--y) == Rational<int>(+2, 1));

        assert((x + y) == Rational<int>(+3, 1));
        assert((x - y) == Rational<int>(-1, 1));
        assert((x * y) == Rational<int>(+2, 1));
        assert((x / y) == Rational<int>(+1, 2));

        assert((x += 1) == Rational<int>(+2, 1));
        assert((x + 1) == Rational<int>(+3, 1));
        assert((1 + y) == Rational<int>(+3, 1));
        assert((1 + 1) == Rational<int>(+2, 1));

        assert((x < y) == 0);
        assert((x > y) == 0);
        assert((x <= y) == 1);
        assert((x >= y) == 1);
        assert((x == y) == 1);
        assert((x != y) == 0);

        std::stringstream stream_1("1/2");
        std::stringstream stream_2;

        stream_1 >> x;
        stream_2 << x;

        assert(stream_2.str() == stream_1.str());

        try
        {
            [[maybe_unused]] Rational<int> bad(1, 0);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[caught in inner block] std::exception: " << e.what() << "\n";
        }

        // ===== std::bad_optional_access =====
        try
        {
            std::optional<int> o;
            o.value();
        }
        catch (const std::exception& e)
        {
            std::cerr << "[bad_optional_access] " << e.what() << "\n";
        }

        // ===== std::bad_variant_access =====
        try
        {
            std::variant<int, double> v = 3.14;
            std::get<int>(v);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[bad_variant_access] " << e.what() << "\n";
        }

        // ===== std::out_of_range и std::length_error для vector =====
        try
        {
            std::vector<int> vec{1,2,3};
            [[maybe_unused]] int value = vec.at(100);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[vector out_of_range] " << e.what() << "\n";
        }

        try
        {
            std::vector<int> vec;
            vec.reserve(vec.max_size() + 1);
        }
        catch (const std::exception& e)
        {
            std::cerr << "[vector length_error] " << e.what() << "\n";
        }

        // ===== std::bad_alloc =====
        try
        {
            std::vector<int> huge;
            huge.resize(static_cast<std::size_t>(-1) / sizeof(int));
        }
        catch (const std::bad_alloc& e)
        {
            std::cerr << "[bad_alloc] " << e.what() << "\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << "[huge allocation other std::exception] " << e.what() << "\n";
        }


        std::cerr << "Program finished normally after handling exceptions\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "[main catch std::exception] " << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "[main catch ...] unknown exception\n";
    }
}
