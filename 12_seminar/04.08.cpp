//////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public :

	constexpr Tuple(T && x, Ts && ... xs)
	:
		m_head(std::forward < T  > (x )   ),
		
		m_tail(std::forward < Ts > (xs)...)
	{}

//  ------------------------------------------------

	template < std::size_t I > constexpr auto get() const
	{
		if constexpr (I > 0)
		{
			return m_tail.template get < I - 1 > ();
		}
		else
		{
			return m_head;
		}
	}

    constexpr std::size_t size() const
    {
        return 1 + sizeof...(Ts);
    }

private :

	T m_head;
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
	constexpr Tuple < int, double, const char* > tuple(1, 2.0, "aaaaa");

//  ----------------------------------------------------------

	static_assert(tuple.get < 0 > () == 1);

    static_assert(tuple.size() == 3);
    static_assert(tuple.get<0>() == 1);
    static_assert(tuple.get<1>() == 2.0);
    static_assert(tuple.get<2>()[0] == 'a');

    constexpr auto t2 = Tuple<char, int>('X', 42);
    
    static_assert(t2.size() == 2);
    static_assert(t2.get<0>() == 'X');
    static_assert(t2.get<1>() == 42);
}

//////////////////////////////////////////////////////////////////