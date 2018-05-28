#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    buf[1024];
double  number_value;
size_t  idx = 0;

enum Token_value
{
    NAME, NUMBER, END, PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
    PRINT = ',', ASSIGN = '=', LP = '(', RP = ')'
};

enum Token_value curr_tok = PRINT;

double term(const char *input, int get);
double prim(const char *input, int get);
double expr(const char* input, int get);
void error_and_exit(const char* s);
enum Token_value get_token();

double expr(const char* input, int get)
{
    double left = term(input, get);
    for (;;)
    {
        switch (curr_tok)
        {
        case PLUS:   left += term(input, 1); break;
        case MINUS:   left -= term(input, 1); break;
        default:   return left;
        };
    };
};

double term(const char* input, int get)
{
    double d;
    double left = prim(input, get);
    for (;;)
    {
        switch (curr_tok)
        {
        case MUL:
            left *= prim(input, 1);
            break;
        case DIV:
            if (d = prim(input, 1))
            {
                left /= d;
                break;
            };
            error_and_exit("деление на ноль");
        default:
            return left;
        };
    };
};

double prim(const char* input, int get)
{
    if (get)
        get_token(input);
    switch (curr_tok)
    {
        case NUMBER:
        {
            double v = number_value;
            get_token(input);
            return v;
        };

        case MINUS:
            return -prim(input, 1);

        case LP:
        {
            double e = expr(input, 1);
            if (curr_tok != RP)
                error_and_exit(") ожидается");
            get_token(input);
            return e;
        };

        default:
            return 1;
    };
};

int is_space(const char ch)
{
    switch (ch)
    {
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0x20:
        return 1;
    }
    return 0;
};

const char* get_number(const char* number, size_t* count)
{
    size_t i = 0;
    while(1)
    {
        char ch = number[i];
        switch(ch)
        {
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            case '8': case '9':
            case '.':
                buf[i] = ch;
                ++i;
            break;

            default:
                buf[i] = 0;
                *count = i;
                return buf;
            break;
        }
    }
}

enum Token_value get_token(const char* input)
{
    char word[1024];
    char err[2048];
    char ch = 0;
    const char* number_string;
    size_t number_length;

    do {
        ch = input[idx];
        if (!ch)
            return curr_tok = END;
        ++idx;
    } while (ch != '\n' && is_space(ch));

    switch (ch)
    {
    case 0:   return curr_tok = END;

    case ':': case '*': case '/': case '+':
    case '-': case '(': case ')':
    case '=':
        return curr_tok = (enum Token_value)ch;
    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
    case '8': case '9':
    case '.':
        --idx;
        number_string = get_number(input+idx, &number_length);
        number_value = atof(number_string);
        idx += number_length;
        return curr_tok = NUMBER;

    case '\n':
        return curr_tok = PRINT;

    default:
        --idx;
        sscanf(input+idx, "%s", word);
        sprintf(err, "некорректный ввод, строка содержит недопустимое выражение %s", word);
        error_and_exit(err);
        return curr_tok = END;
    };
};

void error_and_exit(const char* s)
{
    printf("%s\n", s);
    exit(1);
};

double calc(const char* expression)
{
    idx = 0;
    char input[1024];
    strcpy(input, expression);
    size_t n = strlen(input);
    for (size_t i = 0; i < n; ++i)
        if(input[i] == ',')
           input[i] = '.';

    while (1)
    {
        get_token(input);
        if (curr_tok == END)
            break;
        if (curr_tok == PRINT)
            continue;
        return expr(input, 0);
        break;
    };
}
