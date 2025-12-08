#include <string>


class Person
{
public:
    std::string name;
    int age = 0;
    int grade = 0;
};


class Builder
{    
public:
    Builder() = default;
    
    auto name(std::string n)
    {
        p.name = std::move(n);
        return *this;
    }
    
    auto age(int a)
    {
        p.age = a;
        return *this;
    }
    
    auto grade(int g)
    {
        p.grade = g;
        return *this;
    }
    
    auto get() const
    {
        return p;
    }

private:
    Person p;
};


int main()
{
    Builder builder;
    auto person = builder.name("Ivan").age(25).grade(10).get();

    static_assert(std::is_same_v<decltype(person), Person>);

    return 0;
}
