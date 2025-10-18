#include<cassert>
#include<iostream>

class Entity_v1
{
public:
    virtual ~Entity_v1() = default;

    virtual void test() const
    {
        std::cout << "test function for Entity_v1 class\n";
    }
};

class Entity_v2
{
public:
    virtual ~Entity_v2() = default;

    virtual void test() const
    {
        std::cout << "test function for Entity_v2 class\n";
    }
};

class Adapter_v1 : public Entity_v1
{
public:
    virtual ~Adapter_v1() = default;

    void test() const final override
    {
        test_v1();
    }

    virtual void test_v1() const
    {
        std::cout << "redefined test function in Adapter_v1\n";
    }
};

class Adapter_v2 : public Entity_v2
{
public:
    virtual ~Adapter_v2() = default;

    void test() const final override
    {
        test_v2();
    }

    virtual void test_v2() const
    {
        std::cout << "redefined test function in Adapter_v2\n";
    }
};

class Client : public Adapter_v1, public Adapter_v2
{
public:
    void test_v1() const override
    {
        std::cout << "redefined test_v1 function in Client\n";
    }

    void test_v2() const override
    {
        std::cout << "redefined test_v2 function in Client\n";
    }
};

int main()
{
    Client client;

    Entity_v1 *e1 = &client;
    Entity_v2 *e2 = &client;

    std::cout << "Call Entity_v1:\n";
    e1->test();

    std::cout << "Call Entity_v2:\n";
    e2->test();
}