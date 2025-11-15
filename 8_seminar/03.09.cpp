#include<iostream>
#include<cstdint>
#include<array>
#include<cassert>
#include<sstream>

class IPv4
{
public:
    IPv4() : m_bytes{0, 0, 0, 0} {}

    IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) : m_bytes{a, b, c, d} {}

// --------------------------------------------------------------------------------

    IPv4& operator++()
    {
        add(1);
        return *this;
    }

    IPv4 operator++(int)
    {
        IPv4 temp = *this;
        add(1);
        return temp;
    }

    IPv4& operator--()
    {
        sub(1);
        return *this;
    }

    IPv4 operator--(int)
    {
        IPv4 temp = *this;
        sub(1);
        return temp;
    }

// --------------------------------------------------------------------------------

    friend bool operator==(const IPv4& lhs, const IPv4& rhs)
    {
        return lhs.to_uint32() == rhs.to_uint32();
    }

    // friend bool operator!=(const IPv4& lhs, const IPv4& rhs)
    // {
    //     return !(lhs == rhs);
    // }

    friend bool operator<(const IPv4& lhs, const IPv4& rhs)
    {
        return lhs.to_uint32() < rhs.to_uint32();
    }

    friend bool operator>(const IPv4& lhs, const IPv4& rhs)
    {
        return rhs < lhs;
    }

    friend bool operator<=(const IPv4& lhs, const IPv4& rhs)
    {
        return !(rhs < lhs);
    }

    friend bool operator>=(const IPv4& lhs, const IPv4& rhs)
    {
        return !(lhs < rhs);
    }

// --------------------------------------------------------------------------------

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip)
    {
        os << static_cast<int>(ip.m_bytes[0]) << '.'
           << static_cast<int>(ip.m_bytes[1]) << '.'
           << static_cast<int>(ip.m_bytes[2]) << '.'
           << static_cast<int>(ip.m_bytes[3]);
        return os;
    }

// --------------------------------------------------------------------------------

    friend std::istream& operator>>(std::istream& is, IPv4& ip)
    {
        int a, b, c, d;
        char dot1, dot2, dot3;

        if (!(is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d) ||
            dot1 != '.' || dot2 != '.' || dot3 != '.' ||
            a < 0 || a > 255 || b < 0 || b > 255 ||
            c < 0 || c > 255 || d < 0 || d > 255)
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        ip.m_bytes = { static_cast<std::uint8_t>(a),
                       static_cast<std::uint8_t>(b),
                       static_cast<std::uint8_t>(c),
                       static_cast<std::uint8_t>(d) };

        return is;
    }

private:
    std::array<std::uint8_t, 4> m_bytes;

    std::uint32_t to_uint32() const
    {
        return (static_cast<std::uint32_t>(m_bytes[0]) << 24) |
               (static_cast<std::uint32_t>(m_bytes[1]) << 16) |
               (static_cast<std::uint32_t>(m_bytes[2]) << 8)  |
               (static_cast<std::uint32_t>(m_bytes[3]));
    }

    void add(std::uint32_t n)
    {
        std::uint32_t value = to_uint32();
        value += n;
        for (int i = 3; i >= 0; --i)
        {
            m_bytes[i] = static_cast<std::uint8_t>(value & 0xFF);
            value >>= 8;
        }
    }

    void sub(std::uint32_t n)
    {
        std::uint32_t value = to_uint32();
        value -= n;
        for (int i = 3; i >= 0; --i)
        {
            m_bytes[i] = static_cast<std::uint8_t>(value & 0xFF);
            value >>= 8;
        }
    }
};

int main()
{
    IPv4 ip1(192, 168, 0, 254);
    IPv4 ip2;

    std::cout << "Initial ip1: " << ip1 << "\n";
    ++ip1;
    assert(ip1 == IPv4 (192, 168, 0, 255));

    std::cout << "After ++: " << ip1 << "\n";
    ip1++;
    assert(ip1 == IPv4 (192, 168, 1, 0));

    std::cout << "After postfix ++: " << ip1 << "\n";
    --ip1;
    assert(ip1 == IPv4 (192, 168, 0, 255));

    std::cout << "After --: " << ip1 << "\n";

    std::stringstream stream_1("212.55.76.102");
    stream_1 >> ip2;

    std::cout << "Initial ip2: " << ip2 << "\n";
    ++ip2;
    assert(ip2 == IPv4 (212, 55, 76, 103));
    
    std::cout << "After ++: " << ip2 << "\n";
    ip2++;
    assert(ip2 == IPv4 (212, 55, 76, 104));

    std::cout << "After postfix ++: " << ip2 << "\n";
    --ip2;
    assert(ip2 == IPv4 (212, 55, 76, 103));

    std::cout << "After --: " << ip2 << "\n";

    assert(ip2 > ip1);

    std::cout << "\nВведите IP-адрес: ";
    if (std::cin >> ip2)
        std::cout << "Вы ввели: " << ip2 << "\n";
    else
        std::cerr << "Ошибка ввода!\n";

    return 0;
}
