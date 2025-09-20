#include <iostream>
#include <format>

int main()
{
    double epsilon = 0;
    std::cin >> epsilon;

    double e = 1;
    double elem = 1;
    int n = 1;

    while (elem > epsilon)
    {
        elem /= n;
        e += elem;
        n++;
    }
    std::cout << std::format("{:.10f}", e) << "\n";

    return 0;
}
