module;
#include <numeric>
#include <istream>
#include <ostream>
#include <type_traits>
#include <compare>

export module rational;


export namespace math
{
    class Rational
    {
    public:

        Rational(int num = 0, int den = 1);

        explicit operator double() const;

        Rational& operator+=(Rational const& other);

        Rational& operator-=(Rational const& other)
        {
            return *this += Rational(-other.m_num, other.m_den);
        }

        Rational& operator*=(Rational const& other)
        {
            m_num *= other.m_num;
            m_den *= other.m_den;
            reduce();
            return *this;
        }

        Rational& operator/=(Rational const& other)
        {
            return *this *= Rational(other.m_den, other.m_num);
        }

        auto const operator++(int) { auto tmp = *this; *this += 1; return tmp; }
        Rational& operator++() { *this += 1; return *this; }

        auto const operator--(int) { auto tmp = *this; *this -= 1; return tmp; }
        Rational& operator--() { *this -= 1; return *this; }


        friend Rational operator+(Rational lhs, Rational const& rhs) { return lhs += rhs; }
        friend Rational operator-(Rational lhs, Rational const& rhs) { return lhs -= rhs; }
        friend Rational operator*(Rational lhs, Rational const& rhs) { return lhs *= rhs; }
        friend Rational operator/(Rational lhs, Rational const& rhs) { return lhs /= rhs; }

        friend std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs);

        friend bool operator==(Rational const& lhs, Rational const& rhs);

        friend std::istream& operator>>(std::istream& stream, Rational& rational);

        friend std::ostream& operator<<(std::ostream& stream, Rational const& rational);

    private:

        void reduce();

        int m_num = 0;
        int m_den = 1;
    };
}