#pragma once

#include <compare>
#include <istream>
#include <ostream>
#include <numeric>

class Rational
{
public:
    Rational(int num = 0, int den = 1);

    explicit operator double() const;

    Rational& operator+=(Rational const& other);
    Rational& operator-=(Rational const& other);
    Rational& operator*=(Rational const& other);
    Rational& operator/=(Rational const& other);

    // маленькие функции — inline
    Rational& operator++() { *this += 1; return *this; }
    Rational& operator--() { *this -= 1; return *this; }

    Rational operator++(int)
    {
        Rational tmp(*this);
        ++(*this);
        return tmp;
    }

    Rational operator--(int)
    {
        Rational tmp(*this);
        --(*this);
        return tmp;
    }

    friend Rational operator+(Rational lhs, Rational const& rhs);
    friend Rational operator-(Rational lhs, Rational const& rhs);
    friend Rational operator*(Rational lhs, Rational const& rhs);
    friend Rational operator/(Rational lhs, Rational const& rhs);

    friend std::strong_ordering operator<=>(Rational const&, Rational const&);
    friend bool operator==(Rational const&, Rational const&);

    friend std::istream& operator>>(std::istream&, Rational&);
    friend std::ostream& operator<<(std::ostream&, Rational const&);

    private:

    void reduce();

    int m_num = 0;
    int m_den = 1;

};
