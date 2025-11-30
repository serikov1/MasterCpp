//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <numeric>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 > struct Ratio
{
    static_assert(D != 0);

	constexpr static auto num = N;
	
	constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 >
struct Sum
{
    constexpr static auto num_raw = R1::num * R2::den + R2::num * R1::den;
	constexpr static auto den_raw = R1::den * R2::den;

    constexpr static auto gcd = std::gcd(num_raw, den_raw);

    constexpr static auto num = num_raw / gcd;
	constexpr static auto den = den_raw / gcd;

//  ------------------------------------------------------------------
	
	using type = Ratio < num, den > ;
};


template<typename R1, typename R2>
struct Sub
{
    using type = typename Sum<R1, Ratio<-R2::num, R2::den>>::type;
};


template<typename R1, typename R2>
struct Mul
{
    constexpr static auto num_raw = R1::num * R2::num;
    constexpr static auto den_raw = R1::den * R2::den;

    constexpr static auto g = std::gcd(num_raw, den_raw);

    constexpr static auto num = num_raw / g;
    constexpr static auto den = den_raw / g;

    using type = Ratio<num, den>;
};


template<typename R1, typename R2>
struct Div
{
    static_assert(R2::num != 0);

    using type = typename Mul<R1, Ratio<R2::den, R2::num>>::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > using sum = typename Sum < R1, R2 > ::type;
template < typename R1, typename R2 > using sub = typename Sub < R1, R2 > ::type;
template < typename R1, typename R2 > using mul = typename Mul < R1, R2 > ::type;
template < typename R1, typename R2 > using div = typename Div < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > > struct Duration 
{
	T x = T();
};

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator+(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
	using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

	auto x = 
	(
		lhs.x * ratio_t::den / R1::den * R1::num +

		rhs.x * ratio_t::den / R2::den * R2::num
	);

	return Duration < decltype(x), ratio_t > (x);
}


template 
< 
	typename T1, typename R1, 
	
	typename T2, typename R2 
>
constexpr auto operator-(Duration<T1, R1> const & lhs, Duration<T2, R2> const & rhs)
{
    Duration<T2, R2> rhs_neg{-rhs.x};
    return lhs + rhs_neg;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	constexpr auto x = 1, y = 2;

//  ----------------------------------------------------------------------

	constexpr Duration < int, Ratio < 1, 2 > > duration_1(x);

	constexpr Duration < int, Ratio < 1, 3 > > duration_2(y);

//  ----------------------------------------------------------------------

	constexpr Duration < int, Ratio < 1, 6 > > duration_3 = duration_1 + duration_2;

//  ----------------------------------------------------------------------

    static_assert(duration_3.x == 7);

//  ----------------------------------------------------------------------

    using R1 = Ratio<1, 2>;
    using R2 = Ratio<1, 3>;

    static_assert(sum<R1, R2>::num == 5 && sum<R1, R2>::den == 6);
    static_assert(sub<R1, R2>::num == 1 && sub<R1, R2>::den == 6);
    static_assert(mul<R1, R2>::num == 1 && mul<R1, R2>::den == 6);
    static_assert(div<R1, R2>::num == 3 && div<R1, R2>::den == 2);

    constexpr auto dsub = duration_1 - duration_2;

    static_assert(Ratio<-1, 6>::num == dsub.x);
}

//////////////////////////////////////////////////////////////////////////////////////////