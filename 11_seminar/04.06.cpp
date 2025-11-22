#include <cassert>
#include <cmath>
#include <array>

consteval double consteval_pi(double eps)
{
    double sum = 0.0;
    double term = 1.0;
    int k = 0;

    while(true)
    {
        term = ((k % 2 == 0) ? 1.0 : -1.0) / (2.0 * k + 1.0);
        if (std::abs(term) < eps)
            break;

        sum += term;
        ++k;
    }

    return 4.0 * sum;
}

consteval double consteval_e(double eps)
{
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    while(true)
    {
        term /= n;
        if (term < eps)
            break;

        sum += term;
        ++n;
    }

    return sum;
}

int main()
{
    constexpr std::array<double, 3> epsilons = {1e-2, 1e-3, 1e-4};

    static_assert( std::abs(consteval_pi(epsilons[0]) - 3.14) < 1e-1 );
    static_assert( std::abs(consteval_e (epsilons[0]) - 2.71) < 1e-1 );

    static_assert( std::abs(consteval_pi(epsilons[1]) - 3.141) < 1e-2 );
    static_assert( std::abs(consteval_e (epsilons[1]) - 2.718) < 1e-2 );

    static_assert( std::abs(consteval_pi(epsilons[2]) - 3.1415) < 1e-3 );
    static_assert( std::abs(consteval_e (epsilons[2]) - 2.7182) < 1e-3 );
}
