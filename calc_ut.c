#include <stdio.h>
#include "minunit.h"
#include "calc.h"

int tests_run = 0;

char *test1(void)
{
  MU_ASSERT("test -1+5-3", calc("-1+5-3") == 1);
  return 0;
}

char *test2(void)
{
  MU_ASSERT("test -10 + (8 * 2.5) - (3 / 1,5)", calc("-10 + (8 * 2.5) - (3 / 1,5)") == 8);
  return 0;
}

char *test3(void)
{
  MU_ASSERT("test 1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)", calc("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)") == 11);
  return 0;
}

char *test_suite(void)
{
    MU_RUN_TEST(test1);
    MU_RUN_TEST(test2);
    MU_RUN_TEST(test3);
    return 0;
}

int main(int ac, char **av)
{
  char *result = test_suite();

  printf("number of tests run: %d\n", tests_run);
  if (result) printf("FAIL: %s\n", result);
  return 0 != result;
}
