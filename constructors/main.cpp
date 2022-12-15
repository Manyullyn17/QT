#include <iostream>

class Empty
{

};

class Dummy
{
public:
    Dummy(int value) : m_member{value}
    {
        std::cout << "Dummy: Constructor called" << std::endl;
    }

    ~Dummy()
    {
        std::cout << "Dummy: Destructor called" << std::endl;
    }

    int getValue() const
    {
        return m_member;
    }
private:
    int m_member = 0;
};

class Base
{
public:
    Base() : m_dummy(new Dummy(0))
    {
        std::cout << "Base: Default Constructor called" << std::endl;
        std::cout << "size of m_dummy = " << sizeof(m_dummy) << std::endl;
        std::cout << "size of m_member = " << sizeof(m_member) << std::endl;
    }

    Base(const Base& other) : m_dummy(new Dummy(other.m_dummy->getValue()))
    {
        std::cout << "Base: Copy Constructor called" << std::endl;
    }

    explicit Base(int value) : m_member(value), m_dummy(new Dummy(value))
    {
        std::cout << "Base: int Constructor called" << std::endl;
    }

    Base& operator=(const Base& other)
    {
        std::cout << "Base: assignment operator called" << std::endl;
        m_member = other.m_member;
        delete m_dummy;
        m_dummy = new Dummy(other.m_dummy->getValue());
        return *this;
    }

    virtual int getValue() const
    {
        std::cout << "Base: getValue called" << std::endl;
        return m_member;
    }

    virtual void addValue() const
    {

    }

    virtual ~Base()
    {
        std::cout << "Base: Destructor called" << std::endl;
        delete m_dummy;
    }

private:
    int m_member;
    Dummy* m_dummy;
};

class Derived : public Base
{
public:
    Derived()
    {
        std::cout << "Derived: Default Constructor called" << std::endl;
    }

    int getValue() const override
    {
        std::cout << "Derived: getValue called" << std::endl;
        return 777;
    }

    void addValue() const override
    {
        std::cout << "Derived: addValue called" << std::endl;
    }

    ~Derived()
    {
        std::cout << "Derived: Destructor called" << std::endl;
    }
};

int main()
{
    Empty e1;
    Empty e2(e1);
    e1 = e2;

    Derived* a_derived = new Derived{};
    Base* base_ptr = a_derived;

    a_derived->getValue();
    base_ptr->getValue();
    a_derived->addValue();
    base_ptr->addValue();
    delete base_ptr;
    a_derived = nullptr;
    base_ptr = nullptr;
    return 0;

#if 0
    std::cout << "size of Base = " << sizeof(Base) << std::endl;
    Base an_object(69);
    std::cout << "size of an_object = " << sizeof(an_object) << std::endl;

    Base another_object = an_object;

    Base third_object;
    third_object = another_object;
#endif
}
