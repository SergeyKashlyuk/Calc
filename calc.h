#ifndef CALC_H
#define CALC_H

class Calculator
{
    std::istream*     input;
    double       number_value;
    std::string  string_value;

    enum Token_value
    {
        NAME, NUMBER, END, PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
        PRINT = ',', ASSIGN = '=', LP = '(', RP = ')'
    };
    Token_value curr_tok = PRINT;

    double expr(bool get);
    double term(bool get);
    double prim(bool get);
    bool is_space(const char ch);
    Token_value get_token();
    void error(const std::string &s);

public:
    double calc(const std::string& expression);
};


#endif // CALC_H
