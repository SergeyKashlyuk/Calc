#ifndef CALC_H
#define CALC_H

#ifdef __cplusplus
extern "C"
{
#endif

double calc(const char* expression);
void error_and_exit(const char* s);

#ifdef __cplusplus
}
#endif

#endif // CALC_H
