////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////

class Vector
{
public :

	Vector() : m_array(nullptr), m_size(0) 
	{
		std::cout << "Vector:: Vector (1)\n";
	}

//  --------------------------------------------------------------------------------

	Vector(std::initializer_list < int > list) : m_size(std::size(list)), m_capacity(std::size(list))
	{
		std::cout << "Vector:: Vector (2)\n";

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(list, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector const & other) : m_size(other.m_size), m_capacity(other.m_capacity)
	{
		std::cout << "Vector:: Vector (3)\n";

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector && other)
	: 
		m_array(std::exchange(other.m_array, nullptr)), 
		
		m_size (std::exchange(other.m_size,  0      )),

        m_capacity(std::exchange(other.m_capacity, 0))
	{
		std::cout << "Vector:: Vector (4)\n";
	}

//  --------------------------------------------------------------------------------

   ~Vector()
	{
		std::cout << "Vector::~Vector\n";

		delete[] m_array;
	}
	
//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // error
//	{
//		std::cout << "Vector::operator= (1)\n";
//
//		if (this != &other)
//		{
//			delete[] m_array;
//
//			m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // bad
//	{
//		std::cout << "Vector::operator= (2)\n";
//
//		if (this != &other)
//		{
//			auto array = other.m_size ? new int[other.m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, array);		
//		
//			delete[] std::exchange(m_array, array);
//
//			m_size = other.m_size;
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector && other) // bad
//	{
//		std::cout << "Vector::operator= (3)\n";
//
//		if (this != &other)
//		{
//			delete[] m_array;
//			
//			m_array = std::exchange(other.m_array, nullptr);
//
//			m_size  = std::exchange(other.m_size,  0      );
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

	auto & operator=(Vector other)
	{
		std::cout << "Vector::operator= (4)\n";

		swap(other);

		return *this;
	}

//  --------------------------------------------------------------------------------

	void swap(Vector & other)
	{
		std::swap(m_array, other.m_array);
		
		std::swap(m_size,  other.m_size );

        std::swap(m_capacity, other.m_capacity);
	}

//  --------------------------------------------------------------------------------

    std::size_t size()
    {
        return m_size;
    }

//  --------------------------------------------------------------------------------

    std::size_t capacity()
    {
        return m_capacity;
    }

//  --------------------------------------------------------------------------------

    bool empty()
    {
        return m_size == 0;
    }

//  --------------------------------------------------------------------------------

    void clear()
    {
        m_size = 0;
    }

//  --------------------------------------------------------------------------------

    void push_back(int value)
    {
        if(m_size >= m_capacity)
        {
            std::size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            
            int* new_array = new int[new_capacity]{};

            if(m_array)
            {
                std::ranges::copy(m_array, m_array + m_size, new_array);
            }

            delete[] m_array;
            m_array = new_array;
            m_capacity = new_capacity;
        }

        m_array[m_size++] = value;
    }

private :

	int * m_array = nullptr;

	std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Vector vector_1;

    vector_1.push_back(10);
    vector_1.push_back(20);
    vector_1.push_back(30);

	assert(vector_1.empty() == false);
	assert(vector_1.size() == 3);

    vector_1.clear();

	assert(vector_1.size() == 0);
	assert(vector_1.empty() == true);

	Vector vector_2 = { 1, 2, 3, 4, 5 };

	Vector vector_3 = vector_2;

	Vector vector_4 = std::move(vector_3);

//  --------------------------------------

	vector_3 = vector_2;

	vector_4 = std::move(vector_3);
}

////////////////////////////////////////////////////////////////////////////////////