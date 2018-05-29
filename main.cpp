#include <iostream>
#include <string>
#include <cctype>
#include <iterator>
#include <locale.h>
#include "calc.h"


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cerr.imbue(std::locale("ru_RU.UTF-8"));

    std::cout << "Введите выражение:";
    std::string s;
    std::getline (std::cin,s);

    Calculator calc;
    try
    {
        std::cout << calc.calc(s) << '\n';
    }
    catch(const std::string& e)
    {
        std::cerr << e << '\n';
    }

    return 0;
};
