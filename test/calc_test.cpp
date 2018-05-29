#include <limits.h>
#include <string>
#include "gtest/gtest.h"
#include "../calc.h"

TEST(Test0,Simple)
{
    Calculator c;
    EXPECT_DOUBLE_EQ(c.calc("-1+5-3"), 1.);
}

TEST(Test1,Brackets1)
{
    Calculator c;
    EXPECT_DOUBLE_EQ(c.calc("-10 + (8 * 2.5) - (3 / 1,5)"), 8.);
}

TEST(Test2,Brackets2)
{
    Calculator c;
    EXPECT_DOUBLE_EQ(c.calc("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)"), 11.);
}

TEST(Test3,Error)
{
    Calculator c;
    ASSERT_THROW(c.calc("1.1 + 2.1 + abc"), std::string);
}
