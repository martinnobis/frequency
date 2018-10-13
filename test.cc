#include <iostream>
#include <typeinfo>

#include "frequency.h"

void test_something(void)
{
    frequency<Hz> a {5};
    frequency<kHz> b {5};
    std::cout << "a: " << a.count() << " Hz" << std::endl;
    std::cout << "b: " << b.count() << " kHz" << std::endl;

    //b = a;
    //std::cout << b << std::endl;


    auto c = a + b;
    std::cout << "c: " << c.count() << " Hz" << std::endl;

    a += b;
    std::cout << "a: " << a.count() << " Hz" << std::endl;

    b += a;
    std::cout << "b: " << b.count() << " kHz" << std::endl;
}

int main(void)
{
    test_something();
    return 0;
}