#include<iostream>

class Entity
{
public:
private:
    friend class Attorney_v1;
    friend class Attorney_v2;

    static void test_v1()
    {
        std::cout << "This is Entity's private function test_v1\n";
    }
    static void test_v2()
    {
        std::cout << "This is Entity's private function test_v2\n";
    }
};

class Attorney_v1
{
public:
private:
    friend class Tester_v1;

    static void test_v1()
    {
        Entity::test_v1();
    }
};

class Tester_v1
{
public :

    static void test_v1()
    {
        Attorney_v1::test_v1();
    }
};

class Attorney_v2
{
public:
private:
    friend class Tester_v2;

    static void test_v2()
    {
        Entity::test_v2();
    }
};

class Tester_v2
{
public :

    static void test_v2()
    {
        Attorney_v2::test_v2();
    }
};

int main()
{
    Tester_v1::test_v1();
    Tester_v2::test_v2();

    return 0;
}