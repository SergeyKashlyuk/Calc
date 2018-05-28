#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "calc.h"

int main(int argc, char* argv[])
{
    char    input[1024];
    setlocale(LC_ALL, "Russian");
    input[0] = 0;
    size_t n = 0;
    char ch;
    do
    {
        if(n == 1024)
            error_and_exit("максимальная длина выражения 1024 символов");
        ch = getchar();
        if(ch != '\n')
            input[n++] = ch;
    } while(ch != '\n');
    input[n] = 0;

    printf("%.2f\n", calc(input));
    return 0;
};
