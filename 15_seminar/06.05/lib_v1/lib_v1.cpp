#include <iostream>

extern "C" void test()
{
    std::cout << "Library v1: Hello from test()!" << std::endl;
}
