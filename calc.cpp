#include <sstream>
#include "calc.h"

double Calculator::expr(bool get)
{
    double left = term(get);
    for (;;)
    {
        switch (curr_tok)
        {
        case PLUS:   left += term(true); break;
        case MINUS:   left -= term(true); break;
        default:   return left;
        };
    };
};

double Calculator::term(bool get)
{
    double left = prim(get);
    for (;;)
    {
        switch (curr_tok)
        {
        case MUL:   left *= prim(true); break;
        case DIV:   if (double d = prim(true))
        {
            left /= d;
            break;
        };
        error("деление на ноль");
        default:
            return left;
        };
    };
};

double Calculator::prim(bool get)
{
    if (get)
        get_token();
    switch (curr_tok)
    {
        case NUMBER:
        {
            double v = number_value;
            get_token();
            return v;
        };

        case MINUS:
            return -prim(true);

        case LP:
        {
            double e = expr(true);
            if (curr_tok != RP)
                error(") ожидается");
            get_token();
            return e;
        };

        default:
            return 1;
    };
};

bool Calculator::is_space(const char ch)
{
    switch (ch)
    {
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0x20:
        return true;
    }
    return false;
};

Calculator::Token_value Calculator::get_token()
{
    char ch = 0;
    do {
        if (!input->get(ch))
            return curr_tok = END;
    } while (ch != '\n' && is_space(ch));

    switch (ch)
    {
    case 0:   return curr_tok = END;

    case ':': case '*': case '/': case '+':
    case '-': case '(': case ')':
    case '=':
        return curr_tok = Token_value(ch);
    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
    case '8': case '9':
    case '.':
        input->putback(ch);
        *input >> number_value;
        return curr_tok = NUMBER;

    case '\n':
        return curr_tok = PRINT;

    default:
        string_value = ch;
        while (input->get(ch))
            string_value.push_back(ch);
        error("некорректный ввод, строка содержит недопустимое выражение " + string_value);
        return curr_tok = END;
    };
};

void Calculator::error(const std::string &s)
{
    throw s;
};

double Calculator::calc(const std::string& expression)
{
    std::stringstream ss;
    for (const char ch : expression)
        ss << ((ch == ',') ? '.' : ch);

    input = &ss;

    while (input)
    {
        get_token();
        if (curr_tok == END)
            break;
        if (curr_tok == PRINT)
            continue;
        return expr(false);
    };
    return 0.;
}
