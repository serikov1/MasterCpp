#include <iostream>
#include <string>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include "include/library.hpp"

int main()
{
    std::string lib_name;
    std::cout << "Enter library filename: ";
    std::cin >> lib_name;

    try
    {
        boost::function<void()> test_func = boost::dll::import_symbol<void()>(
            lib_name,
            "test",
            boost::dll::load_mode::append_decorations
        );

        std::cout << "Calling test() from " << lib_name << ":\n";
        test_func();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error loading library: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
