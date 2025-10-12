#include <iostream>
#include <cassert>
#include <numeric>
#include <vector>

int nod(int a, int b)
{
    if(b == 0)
    {
        return a;
    }
    return nod(b, a % b);
}

int nok(int a, int b)
{
    if(a == 0 || b == 0)
    {
        return 0;
    }
    return a / nod(a, b) * b; 
}

int main()
{
    std::vector < std::pair <int, int> > data = { {12, 18}, {100, 80}, {5, 18}, {42, 56}, {121, 754} };

    for (auto &pair : data) {
        int my_gcd = nod(pair.first, pair.second);
        int std_gcd = std::gcd(pair.first, pair.second);

        int my_lcm = nok(pair.first, pair.second);
        int std_lcm = std::lcm(pair.first, pair.second);

        assert(my_gcd == std_gcd);
        assert(my_lcm == std_lcm);
    }

    return 0;
}