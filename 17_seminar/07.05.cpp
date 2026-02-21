#include <benchmark/benchmark.h>

#include <vector>
#include <algorithm>
#include <numeric>
#include <cstddef>
#include <utility>
#include <cmath>


template <typename T>
static void order(std::vector<T>& v, std::size_t left, std::size_t right)
{
    for (std::size_t i = left + 1; i < right; ++i)
        for (std::size_t j = i; j > left && v[j - 1] > v[j]; --j)
            std::swap(v[j], v[j - 1]);
}


template <typename T>
static std::size_t median_of_three(std::vector<T>& v, std::size_t left, std::size_t right)
{
    const std::size_t mid = left + (right - left) / 2;

    const T& left_v  = v[left];
    const T& mid_v   = v[mid];
    const T& right_v = v[right - 1];

    if ((left_v <= mid_v && mid_v <= right_v) || (right_v <= mid_v && mid_v <= left_v))
        return mid;
    else if ((mid_v <= left_v && left_v <= right_v) || (right_v <= left_v && left_v <= mid_v))
        return left;
    else
        return right - 1;
}


template <typename T>
static std::size_t hoar_partition(std::vector<T>& v, std::size_t left, std::size_t right)
{
    const std::size_t pivot_index = median_of_three(v, left, right);
    const T pivot = v[pivot_index];

    std::swap(v[left], v[pivot_index]);

    std::size_t i = left + 1;
    std::size_t j = right - 1;

    while (true)
    {
        while (i <= j && v[i] < pivot) ++i;
        while (i <= j && v[j] > pivot) --j;

        if (i >= j) break;

        std::swap(v[i++], v[j--]);
    }

    std::swap(v[left], v[j]);
    return j;
}


template <typename T>
static void quicksort(std::vector<T>& v, std::size_t left, std::size_t right, std::size_t threshold)
{
    if (right - left <= threshold)
    {
        order(v, left, right);
        return;
    }

    const std::size_t pivot_pos = hoar_partition(v, left, right);

    if (pivot_pos > left)
        quicksort(v, left, pivot_pos, threshold);

    quicksort(v, pivot_pos + 1, right, threshold);
}

template <typename T>
static void sort(std::vector<T>& v, std::size_t threshold)
{
    if (v.size() < 2) return;
    quicksort(v, 0, v.size(), threshold);
}


static std::vector<double> make_reverse_sort(std::size_t n)
{
    std::vector<double> v(n);
    for (std::size_t i = 0; i < n; ++i)
        v[i] = static_cast<double>(n - i);
    return v;
}


static void benchmark_quicksort(benchmark::State& state)
{
    const std::size_t threshold = static_cast<std::size_t>(state.range(0));
    const std::vector<double> base = make_reverse_sort(10'000);

    for (auto _ : state)
    {
        auto data = base;
        benchmark::DoNotOptimize(data.data());
        sort(data, threshold);
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(state.iterations() * static_cast<long long>(base.size()));
}


//BENCHMARK(benchmark_quicksort)->Arg(4)->Arg(8)->Arg(12)->Arg(16)->Arg(24)->Arg(32)->Arg(48)->Arg(64)->Arg(96)->Arg(128);

void make_args(::benchmark::Benchmark * benchmark) 
{
    for (auto i = 1; i < 8; ++i)
    {
        int treshold = std::pow(2, i);
        benchmark->Args({treshold});
    }
}
BENCHMARK(benchmark_quicksort)->Apply(make_args);

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

// g++ -O3 -std=c++23 07.05.cpp -lbenchmark -lpthread -o build/07.05
// ./build/07.05 --benchmark_repetitions=5 --benchmark_report_aggregates_only=true