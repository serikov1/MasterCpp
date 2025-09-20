#include <iostream>
#include <cmath>

int main()
{
    double n = 0;
    std::cin >> n;

    double const sqrt_5 = std::sqrt(5);
    double minus_eq = std::pow((1 - sqrt_5)/2, n);
    double plus_eq = std::pow((1 + sqrt_5)/2, n);

    int result = (plus_eq - minus_eq) / sqrt_5;

    std::cout << static_cast <double> (result) << "\n";

    return 0;
}