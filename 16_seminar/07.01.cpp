#include <iostream>
#include <cmath>
#include <optional>
#include <variant>
#include <utility> 
#include <limits>

using Roots = std::variant<double, std::pair<double, double>, std::monostate>;
using MaybeRoots = std::optional<Roots>;

constexpr double epsilon = 1e-6;

static bool is_zero(double x)
{
    return std::abs(x) < epsilon;
}

MaybeRoots solve(double a, double b, double c)
{
    if (is_zero(a) && is_zero(b) && is_zero(c))
    {
        return Roots{std::monostate{}};
    }

    if (is_zero(a) && is_zero(b))
    {
        return std::nullopt;
    }

    if (is_zero(a))
    {
        double x = -c / b;
        return Roots{x};
    }

    double d = b * b - 4.0 * a * c;

    if (is_zero(d))
    {
        double x = -b / (2.0 * a);
        return Roots{x};
    }

    if (d > epsilon)
    {
        double sqrt_d = std::sqrt(d);
        double x1 = (-b + sqrt_d) / (2.0 * a);
        double x2 = (-b - sqrt_d) / (2.0 * a);
        return Roots{std::pair<double, double>{x1, x2}};
    }

    return std::nullopt;
}

int main()
{
    double a = 0, b = 0, c = 0;
    std::cin >> a >> b >> c;

    auto ans = solve(a, b, c);

    if (!ans)
    {
        std::cout << "no real roots\n";
        return 0;
    }
    if (std::holds_alternative<std::monostate>(*ans))
    {
        std::cout << "infinitely many roots\n";
    }
    else if (std::holds_alternative<double>(*ans))
    {
        std::cout << "one root: " << std::get<double>(*ans) << "\n";
    }
    else
    {
        auto p = std::get<std::pair<double, double>>(*ans);
        std::cout << "first root is: " << p.first << "\n"
                  << "second root is: " << p.second << "\n";
    }

    return 0;
}
