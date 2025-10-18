#include<cassert>
#include<iostream>
#include<cmath>
#include<vector>

class Shape
{
public:

    virtual ~Shape() = default;

    virtual double perimeter() = 0;

    virtual double area() = 0;

};

class Triangle : public Shape
{
public:

    Triangle(double a, double b, double c): m_a(a), m_b(b), m_c(c) {}

    double perimeter() override
    {
        return m_a + m_b + m_c;
    }

    double area() override
    {
        double p_2 = perimeter() / 2;
        return std::sqrt(p_2 * (p_2 - m_a) * (p_2 - m_b) * (p_2 - m_c));
    }

private:

    double m_a = 0;
    double m_b = 0;
    double m_c = 0;
};

class Square : public Shape
{
public:

    Square(double a): m_a(a) {}

    double perimeter() final override
    {
        return 4 * m_a;
    }

    double area() final override
    {
        return m_a * m_a;
    }

private:

    double m_a = 0;
};

class Circle : public Shape
{
public:

    Circle(double r): m_r(r) {}

    double perimeter() final override
    {
        return 2 * std::numbers::pi * m_r;
    }

    double area() final override
    {
        return std::numbers::pi * m_r * m_r;
    }

private:

    double m_r = 0;
};

int main()
{
    std::vector <Shape *> shapes;

    shapes.push_back(new Triangle(3, 4, 5));
    shapes.push_back(new Square(10));
    shapes.push_back(new Circle(3));

    assert(shapes[0]->perimeter() - 12 < 1e-3);
    assert(shapes[0]->area() - 6 < 1e-3);

    assert(shapes[1]->perimeter() - 40 < 1e-3);
    assert(shapes[1]->area() - 100 < 1e-3);

    assert(shapes[2]->perimeter() - 18.849 < 1e-3);
    assert(shapes[2]->area() - 28.274 < 1e-3);

    return 0;
}