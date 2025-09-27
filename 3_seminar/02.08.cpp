#include <iostream>
#include <vector>

std::size_t len_collatc(unsigned long long n, std::vector<std::size_t> &cashe_vector)
{
    std::size_t len = 0;
    if(n >= cashe_vector.size())
    {
        cashe_vector.resize(n + 1, 0);
    }

    if(cashe_vector.at(n) != 0)
    {
        return cashe_vector.at(n);
    }

    if(n == 1)
    {
        len = 1;
    }
    else if(n % 2 == 0)
    {
        len = 1 + len_collatc(n/2, cashe_vector);
    }
    else
    {
        len = 1 + len_collatc(3 * n + 1, cashe_vector);
    }

    cashe_vector.at(n) = len;

    return len;
}

int main()
{
    std::vector<std::size_t> lenghts(1, 0);

    std::size_t max_len = 0;
    unsigned long long start_value = 1;

    for(size_t i = 1; i < 100; ++i)
    {
        std::size_t len = len_collatc(i, lenghts);
        if(len > max_len)
        {
            max_len = len;
            start_value = i;
        }
    }

    std::cout << "Макисмальная длина: " << max_len << "\nСтартовое число: " << start_value << "\n";

    return 0;
}