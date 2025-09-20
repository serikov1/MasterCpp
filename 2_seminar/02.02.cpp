#include <iostream>
#include <cmath>


int main()
{
    double a = 0, b = 0, c = 0;
    std::cin >> a >> b >> c;

    double result_1 = 0;
    double result_2 = 0;
    double epsilon = 1e-6;

    double disckremenant = b * b - 4 * a * c;

    if (std::abs(disckremenant) < epsilon)
    {
        result_1 = result_2 = -b / (2 * a);
    }
    else if (disckremenant > epsilon)
    {
        result_1 = (-b + std::sqrt(disckremenant)) / (2 * a);
        result_2 = (-b - std::sqrt(disckremenant)) / (2 * a);
    }
    else
    {
        result_1 = result_2 = NAN;
    }

    std::cout << "first root is: " << result_1 << "\n" << "second root is: " << result_2 << "\n";

    return 0;
}