#include <iostream>

extern "C" void test()
{
    std::cout << "Library v2: Greetings from test()!" << std::endl;
}
