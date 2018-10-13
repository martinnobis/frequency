#include <iostream>
#include <typeinfo>

#include "frequency.h"

void test_something(void)
{
    frequency<Hz> a {5};
    frequency<kHz> b {5};
    std::cout << "a: " << a.count() << " Hz" << std::endl;
    std::cout << "b: " << b.count() << " kHz" << std::endl;

    auto c = a + b;
    assert(c.count() == 5005);

    auto d = a + b + b + a;
    assert(typeid(d) == typeid(frequency<Hz>));
    assert(d.count() == 10010);

    a += b;
    assert(typeid(a) == typeid(frequency<Hz>));
    assert(a.count() == 5005);

    b += a;
    assert(typeid(b) == typeid(frequency<kHz>));
    assert(b.count() == 10.005);
}

int main(void)
{
    test_something();
    return 0;
}