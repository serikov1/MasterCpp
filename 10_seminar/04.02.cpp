#include <iostream>
#include <cassert>


double sum_from_pack(auto ... args)
{
    return (args + ...);
}

double middle_from_pack(auto ... args)
{
    std::size_t count = sizeof...(args);
    double sum = sum_from_pack(args ...);

	return sum / count;
}

double min_from_pack(double arg)
{
    return arg;
}

double min_from_pack(double arg, auto ... args)
{
    double min = min_from_pack(args ...);

    return (arg < min ? arg : min);
}

double max_from_pack(double arg)
{
    return arg;
}

double max_from_pack(double arg, auto ... args)
{
    double max = max_from_pack(args ...);

    return (arg > max ? arg : max);
}

int main()
{
    assert(std::abs(min_from_pack(1.2, 1.6, 0.9, 21.7, -13.6) + 13.6) < 1e-2);
    assert(std::abs(max_from_pack(1.2, 1.6, 0.9, 21.7, -13.6) - 21.7) < 1e-2);

    assert(middle_from_pack(1.2, 1.6, 0.9, 21.7, -13.6) - 2.36 < 1e-2);
    assert(sum_from_pack(1.2, 1.6, 0.9, 21.7, -13.6) - 11.8 < 1e-2);

    return 0;
}
