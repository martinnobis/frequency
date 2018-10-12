#include <iostream>
#include <typeinfo>

#include "frequency.h"

void test_something(void)
{
    frequency<Hz> a {5};
    frequency<kHz> b {5};
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    //b = a;
    //std::cout << b << std::endl;


    auto c = a + b;
    std::cout << "c: " << c << std::endl;

    a += b;
    std::cout << "a: " << a << std::endl;

    b += a;
    std::cout << "b: " << b << std::endl;

}

int main(void)
{
    test_something();
    return 0;
}