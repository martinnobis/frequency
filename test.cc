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
    assert(typeid(c) == typeid(frequency<Hz>));
    assert(c.count() == 5005);

    auto d = a + b + b + a;
    assert(typeid(d) == typeid(frequency<Hz>));
    assert(d.count() == 10010);

    a += b;
    assert(typeid(a) == typeid(frequency<Hz>));
    assert(a.count() == 5005);

    b += a;
    assert(typeid(b) == typeid(frequency<kHz>));
    std::cout << b.count() << std::endl;
    assert(b.count() == 10.005);

    auto hello = 5.0_khz;
    auto hello2 = 2_hz;
    auto sum = hello + hello2;
    std::cout << sum.count() << std::endl;

    std::cout << hello.count() << std::endl;

}

int main(void)
{
    test_something();
    return 0;
}
