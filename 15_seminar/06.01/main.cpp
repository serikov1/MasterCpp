#include <cassert>
#include <cmath>
#include <sstream>
#include <vector>
#include "Rational.hpp"

bool equal(double x, double y, double eps = 1e-6)
{
    return std::abs(x - y) < eps;
}

int main()
{
    Rational x = 1, y(2, 1);

    assert(equal(static_cast<double>(x), 1));

    assert((x += y) == Rational(3, 1));
    assert((x -= y) == Rational(1, 1));
    assert((x *= y) == Rational(2, 1));
    assert((x /= y) == Rational(1, 1));

    assert((x++) == Rational(1, 1));
    assert((x--) == Rational(2, 1));
    assert((++y) == Rational(3, 1));
    assert((--y) == Rational(2, 1));

    assert((x + y) == Rational(3, 1));
    assert((x / y) == Rational(1, 2));

    std::stringstream s1("1/2"), s2;
    s1 >> x;
    s2 << x;

    assert(s1.str() == s2.str());
}
