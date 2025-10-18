#include<cassert>
#include<iostream>
#include<cmath>

class Triangle
{
public:

    Triangle(double a, double b, double c): m_a(a), m_b(b), m_c(c) {}

    double perimeter()
    {
        return m_a + m_b + m_c;
    }

    double square()
    {
        double p_2 = perimeter() / 2;
        return std::sqrt(p_2 * (p_2 - m_a) * (p_2 - m_b) * (p_2 - m_c));
    }

private:

    double m_a = 0;
    double m_b = 0;
    double m_c = 0;
};

class Square
{
public:

    Square(double a): m_a(a) {}

    double perimeter()
    {
        return 4 * m_a;
    }

    double square()
    {
        return m_a * m_a;
    }

private:

    double m_a = 0;
};

class Circle
{
public:

    Circle(double r): m_r(r) {}

    double lenght()
    {
        return 2 * std::numbers::pi * m_r;
    }

    double square()
    {
        return std::numbers::pi * m_r * m_r;
    }

private:

    double m_r = 0;
};

int main()
{
    Triangle t(3, 4, 5);

    assert(t.perimeter() - 12 < 1e-3);
    assert(t.square() - 6 < 1e-3);

    Square s(10);

    assert(s.perimeter() - 40 < 1e-6);
    assert(s.square() - 100 < 1e-6);

    Circle c(3);

    assert(c.lenght() - 18.849 < 1e-3);
    assert(c.square() - 28.274 < 1e-3);

    return 0;
}