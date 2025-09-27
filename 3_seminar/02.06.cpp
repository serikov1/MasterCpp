#include <iostream>
#include <cmath>

int main()
{
    size_t max_len = 100'000;
    double array[max_len];
    size_t n = 0;

    std::cin >> n;

    if(n > max_len) return -1;

    for(size_t i = 0; i < n; i++)
    {
        std::cin >> array[i];
    }

    double min_value = array[0];
    double max_value = array[0];
    double average = 0;
    double std = 0;

    for(size_t i = 0; i < n; ++i)
    {
        if(array[i] < min_value) min_value = array[i];
        if(array[i] > max_value) max_value = array[i];
        average += array[i];
    }
    average /= n;

    for(size_t i = 0; i < n; ++i)
    {
        std += (array[i] - average) * (array[i] - average);
    }
    std /= n-1;
    std = std::sqrt(std);

    std::cout << "Минимальное значение: " << min_value << "\n";
    std::cout << "Максимальное значение: " << max_value << "\n";
    std::cout << "Среднее арифметическое: " << average << "\n";
    std::cout << "Стандартное отклонение: " << std << "\n";
    
    return 0;
}