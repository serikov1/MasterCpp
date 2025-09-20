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
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O':
        case 'P': case 'Q': case 'R': case 'S': case 'T':
        case 'U': case 'V': case 'W': case 'X': case 'Y':
        case 'Z':
            std::cout << "Заглавная буква\n";
            break;

        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z':
            std::cout << "Строчная буква\n";
            break;

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
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