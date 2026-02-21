#include <gtest/gtest.h>

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


TEST(QuickSort, Int_Reverse_1000)
{
    std::size_t size = 1'000uz;
    std::vector<int> v(size, 0);

    for (std::size_t i = 0; i < size; ++i)
    {
        v[i] = static_cast<int>(size - i);
    }
    sort(v);

    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSort, Double_Reverse_1000)
{
    std::size_t size = 1'000uz;
    std::vector<double> v(size, 0);

    for (std::size_t i = 0; i < size; ++i)
    {
        v[i] = static_cast<double>(size - i) - 0.5;
    }
    sort(v);

    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSort, Int_AlreadySorted)
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSort, Int_WithNegativesAndDuplicates)
{
    std::vector<int> v{0, -10, 5, -3, 2, -10, 100, -1, 5, 5, 0};
    sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
}

TEST(QuickSort, Int_EmptyVector)
{
    std::vector<int> v;
    sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
    EXPECT_TRUE(v.empty());
}

TEST(QuickSort, Int_SingleElement)
{
    std::vector<int> v{42};
    sort(v);
    EXPECT_TRUE(std::ranges::is_sorted(v));
    EXPECT_EQ(v[0], 42);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//g++ -std=c++23 -O0 07.04.cpp -lgtest -lgtest_main -pthread -o 07.04