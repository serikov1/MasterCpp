#include <iostream>

class Slow
{
public:

    void test() const
    {
        std::cout << "Slow::test\n";
    }
};

class Fast
{
public:

    void test() const
    {
        std::cout << "Fast::test\n";
    }
};


template <typename Strategy>
class Entity : public Strategy
{
public:

    void test() const
    {
        Strategy::test();
    }
};

/////////////////////////////////////////////////////////

int main()
{
    Entity<Slow>  e1;
    Entity<Fast>  e2;

    e1.test();
    e2.test();
}
