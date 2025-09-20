#include <iostream>

int main()
{
    for (int i = 1; i < 9; ++i)
    {
        for (int j = 0u; j < 9; ++j)
        {
            for (int k = 0u; k < 9; ++k)
            {
                if (i * i * i + j * j * j + k * k * k == i * 100 + j * 10 + k)
                {
                    std::cout << i << j << k << "\n";
                }
            }
        }
    }
    return 0;
}