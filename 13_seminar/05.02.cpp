#include <iostream>
#include <string>


class Entity
{
public:

    virtual void info() const = 0;

    virtual ~Entity() = default;
};


class Client : public virtual Entity
{
public:

    void info() const override
    {
        std::cout << "Client::info() \n";
    }
};


template <typename T>
class Decorator : public virtual Entity, public T
{
public:

    void info() const override
    {
        std::cout << "Decorator::info() -> ";
        T::info();
    }
};


int main()
{
    Client base;

    Decorator<Client> d;
    d.info();

    return 0;
}
