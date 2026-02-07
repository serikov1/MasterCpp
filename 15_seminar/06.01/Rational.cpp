#include "Rational.hpp"

Rational::Rational(int num, int den)
    : m_num(num), m_den(den)
{
    reduce();
}

Rational::operator double() const
{
    return 1.0 * m_num / m_den;
}

Rational& Rational::operator+=(Rational const& other)
{
    auto lcm = std::lcm(m_den, other.m_den);

    m_num = m_num * (lcm / m_den)
          + other.m_num * (lcm / other.m_den);

    m_den = lcm;
    reduce();
    return *this;
}

Rational& Rational::operator-=(Rational const& other)
{
    return *this += Rational(-other.m_num, other.m_den);
}

Rational& Rational::operator*=(Rational const& other)
{
    m_num *= other.m_num;
    m_den *= other.m_den;
    reduce();
    return *this;
}

Rational& Rational::operator/=(Rational const& other)
{
    return *this *= Rational(other.m_den, other.m_num);
}

Rational operator+(Rational lhs, Rational const& rhs)
{
    return lhs += rhs;
}

Rational operator-(Rational lhs, Rational const& rhs)
{
    return lhs -= rhs;
}

Rational operator*(Rational lhs, Rational const& rhs)
{
    return lhs *= rhs;
}

Rational operator/(Rational lhs, Rational const& rhs)
{
    return lhs /= rhs;
}

std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs)
{
    long long l = 1LL * lhs.m_num * rhs.m_den;
    long long r = 1LL * rhs.m_num * lhs.m_den;

    if (l < r) return std::strong_ordering::less;
    if (l > r) return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

bool operator==(Rational const& lhs, Rational const& rhs)
{
    return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
}

std::istream& operator>>(std::istream& in, Rational& r)
{
    return (in >> r.m_num).ignore() >> r.m_den;
}

std::ostream& operator<<(std::ostream& out, Rational const& r)
{
    return out << r.m_num << '/' << r.m_den;
}

void Rational::reduce()
{
    if (m_den < 0)
    {
        m_num = -m_num;
        m_den = -m_den;
    }

    auto g = std::gcd(m_num, m_den);
    m_num /= g;
    m_den /= g;
}
