#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <numeric>


template < typename T >
void order(std::vector<T> &vector, std::size_t left, std::size_t right)
{
    for (auto i = left + 1; i < right; ++i)
    {
        for (auto j = i; j > left && vector[j - 1] > vector[j]; --j)
        {
            std::swap(vector[j], vector[j - 1]);
        }
    }
}


template < typename T >
std::size_t median_of_three(std::vector<T> &v, std::size_t left, std::size_t right)
{
    std::size_t mid = std::midpoint(left, right);

    int left_v = v[left];
    int mid_v = v[mid];
    int right_v = v[right - 1];

    if ((left_v <= mid_v && mid_v <= right_v) || (right_v <= mid_v && mid_v <= left_v))
        return mid;
    else if ((mid_v <= left_v && left_v <= right_v) || (right_v <= left_v && left_v <= mid_v))
        return left;
    else
        return right - 1;
}


template < typename T >
std::size_t hoar_partition(std::vector<T> &v, std::size_t left, std::size_t right)
{
    std::size_t pivot_index = median_of_three(v, left, right);
    int pivot = v[pivot_index];

    std::swap(v[left], v[pivot_index]);

    std::size_t i = left + 1;
    std::size_t j = right - 1;

    while (true)
    {
        while (i <= j && v[i] < pivot) ++i;
        while (i <= j && v[j] > pivot) --j;

        if (i >= j)
            break;

        std::swap(v[i++], v[j--]);
    }

    std::swap(v[left], v[j]);
    return j;
}


template < typename T >
void quicksort(std::vector<T> &v, std::size_t left, std::size_t right)
{
    if (right - left <= 16)
    {
        order(v, left, right);
        return;
    }

    std::size_t pivot_pos = hoar_partition(v, left, right);

    if (pivot_pos > left)
        quicksort(v, left, pivot_pos);

    quicksort(v, pivot_pos + 1, right);
}


template < typename T >
void sort(std::vector<T> &vector)
{
    quicksort(vector, 0, vector.size());
}


int main()
{
    std::size_t size = 1'000uz;

    std::vector<int> vector_int(size, 0);
    
    for (std::size_t i = 0; i < size; ++i)
    {
        vector_int[i] = size - i;
    }

    sort(vector_int);

    assert(std::ranges::is_sorted(vector_int));


    std::vector<double> vector_double(size, 0);
    
    for (std::size_t i = 0; i < size; ++i)
    {
        vector_double[i] = size - i - 0.5;
    }

    sort(vector_double);

    assert(std::ranges::is_sorted(vector_double));
}
