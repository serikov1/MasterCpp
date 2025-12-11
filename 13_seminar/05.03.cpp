#include <iostream>
#include <vector>
#include <string>


class Entity
{
public:

    virtual ~Entity() = default;

    void takeTurn()
    {
        std::cout << "Start turn\n";
        move();
        action();
        std::cout << "End turn\n\n";
    }

protected:

    virtual void move() = 0;
    virtual void action() = 0;
};


class Unit : public Entity
{
public:

    Unit(const std::string& name, int hp, int dmg)
        : m_name(name), m_hp(hp), m_dmg(dmg) {}

protected:

    void move() override
    {
        std::cout << m_name << " moves\n";
    }

    void action() override
    {
        std::cout << m_name << " hits for " << m_dmg << "\n";
    }

private:

    std::string m_name;
    int m_hp;
    int m_dmg;
};


class Group : public Entity
{
public:

    void add(Entity* e)
    {
        m_entities.push_back(e);
    }

protected:

    void move() override
    {
        std::cout << "Group moves together\n";
    }

    void action() override
    {
        std::cout << "Group coordinated attack:\n";
    }

private:

    std::vector<Entity*> m_entities;
};


class UnitBuilder
{
public:

    UnitBuilder& name(const std::string& n)
    {
        m_name = n;
        return *this;
    }

    UnitBuilder& hp(int h)
    {
        m_hp = h;
        return *this;
    }

    UnitBuilder& dmg(int d)
    {
        m_dmg = d;
        return *this;
    }

    Unit* build() const
    {
        return new Unit(m_name, m_hp, m_dmg);
    }

private:

    std::string m_name = "Unknown";
    int m_hp = 10;
    int m_dmg = 1;
};


int main() {
    UnitBuilder builder;

    Unit* knight = builder.name("Knight").hp(50).dmg(10).build();
    Unit* archer = builder.name("Archer").hp(30).dmg(7).build();

    Group squad;
    squad.add(knight);
    squad.add(archer);

    knight->takeTurn();

    archer->takeTurn();

    squad.takeTurn();

    delete knight;
    delete archer;
}
