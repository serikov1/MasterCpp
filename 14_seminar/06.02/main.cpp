#include <cassert>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

import rational;


static bool equal(double x, double y, double eps = 1e-6)
{
    return std::abs(x - y) < eps;
}

int main()
{
    math::Rational x = 1, y(2, 1);

    std::vector<int> v(5);
    std::vector<int> v2 = {1,2,3,4,5};

    assert(equal(static_cast<double>(x), 1.0));

    assert((x += y) == math::Rational(3,1));
    assert((x -= y) == math::Rational(1,1));
    assert((x *= y) == math::Rational(2,1));
    assert((x /= y) == math::Rational(1,1));

    assert((x++ ) == math::Rational(1,1));
    assert((x-- ) == math::Rational(2,1));
    assert((++y ) == math::Rational(3,1));
    assert((--y ) == math::Rational(2,1));

    assert((x + y) == math::Rational(3,1));
    assert((x - y) == math::Rational(-1,1));
    assert((x * y) == math::Rational(2,1));
    assert((x / y) == math::Rational(1,2));

    assert((x += 1) == math::Rational(2,1));
    assert((x + 1) == math::Rational(3,1));
    assert((1 + y) == math::Rational(3,1));
    assert((1 + 1) == math::Rational(2,1));

    assert((x < y) == 0);
    assert((x > y) == 0);
    assert((x <= y) == 1);
    assert((x >= y) == 1);
    assert((x == y) == 1);
    assert((x != y) == 0);

    std::stringstream s1("1/2");
    std::stringstream s2;
    s1 >> x;
    s2 << x;
    assert(s2.str() == std::string("1/2"));
}
