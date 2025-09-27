#include <iostream>

int main()
{
    char input = 0;
    std::cin >> input;

    if (static_cast<int>(input) < 32 || static_cast<int>(input) > 127)
    {
        std::cout << "вне диапазона\n";
        return -1;
    }

    switch (input) {
        case 'A'...'Z':
            std::cout << "Заглавная буква\n";
            break;

        case 'a'...'z':
            std::cout << "Строчная буква\n";
            break;

        case '0'...'9':
            std::cout << "Десятичная цифра\n";
            break;

        case '!': case '"': case '(': case ')': case ',':
        case '-': case '.': case ':': case ';': case '?':
        case '[': case ']': case '{': case '}':
            std::cout << "Знак препинания\n";
            break;
            
        default:
            std::cout << "Прочий символ\n";
            break;
    }
    

    return 0;
}