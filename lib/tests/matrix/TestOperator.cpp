#include <gtest/gtest.h>

#include "Matrix/Operator.hpp"


TEST(Operator, TestAddMethod)
{
    double a = 5;
    double b = 2;

    auto expected = a + b;
    auto actual = Operator<double>::add(a, b);

    ASSERT_EQ(expected, actual);
}


TEST(Operator, TestSubMethod)
{
    double a = 5;
    double b = 2;

    auto expected = a - b;
    auto actual = Operator<double>::sub(a, b);

    ASSERT_EQ(expected, actual);
}


TEST(Operator, TestDivMethod)
{
    double a = 5;
    double b = 2;

    auto expected = a / b;
    auto actual = Operator<double>::div(a, b);

    ASSERT_EQ(expected, actual);
    ASSERT_THROW(Operator<double>::div(a, 0.), ZeroDivisionError);
}


TEST(Operator, TestMulMethod)
{
    double a = 5;
    double b = 2;

    auto expected = a * b;
    auto actual = Operator<double>::mul(a, b);

    ASSERT_EQ(expected, actual);
}


TEST(Operator, TestEqMethod)
{
    auto actual = Operator<int>::eq(5, 5);

    ASSERT_TRUE(actual);
}


TEST(Operator, TestNeMethod)
{
    auto actual = Operator<int>::ne(5, 7);

    ASSERT_TRUE(actual);
}
