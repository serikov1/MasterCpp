// rational.cpp
#include "rational.hpp"
#include <numeric> // на всякий случай (std::lcm в operator+=)

Rational::Rational(int num, int den) : m_num(num), m_den(den)
{
    reduce();
}

Rational::operator double() const
{
    return static_cast<double>(m_num) / static_cast<double>(m_den);
}

Rational& Rational::operator+=(Rational const& other)
{
    // корректно вычисляем НОК и приводим числители
    auto l = std::lcm(m_den, other.m_den);
    m_num = m_num * (l / m_den) + other.m_num * (l / other.m_den);
    m_den = static_cast<int>(l);
    reduce();
    return *this;
}

void Rational::reduce()
{
    if (m_den == 0) return;
    if (m_den < 0) {
        m_num = -m_num;
        m_den = -m_den;
    }
    auto g = std::gcd(m_num, m_den);
    if (g != 0) {
        m_num /= g;
        m_den /= g;
    }
}

std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs)
{
    long long left = static_cast<long long>(lhs.m_num) * rhs.m_den;
    long long right = static_cast<long long>(rhs.m_num) * lhs.m_den;
    if (left < right) return std::strong_ordering::less;
    if (left > right) return std::strong_ordering::greater;

    return std::strong_ordering::equal;
}

std::istream& operator>>(std::istream& stream, Rational& rational)
{
    char sep = '/';
    stream >> rational.m_num >> sep >> rational.m_den;
    rational.reduce();

    return stream;
}

std::ostream& operator<<(std::ostream& stream, Rational const& rational)
{
    return stream << rational.m_num << '/' << rational.m_den;
}

bool operator==(Rational const& lhs, Rational const& rhs)
{
    return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
}
