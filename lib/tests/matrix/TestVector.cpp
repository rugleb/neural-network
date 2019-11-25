#include <algorithm>

#include <gtest/gtest.h>

#include "Matrix/Vector.hpp"


using namespace testing;


TEST(Vector, TestRandomMethod)
{
    double min = 0;
    double max = 1;

    std::size_t size = 5;

    auto v = Vector<double>::random(min, max, size);

    for (std::size_t i = 0; i < size; i++) {
        ASSERT_GE(v[i], min);
        ASSERT_LE(v[i], max);
    }

    ASSERT_EQ(size, v.size());
}


TEST(Vector, TestSizeMethod)
{
    std::size_t size = 5;
    double initial = 10;

    auto v = Vector<double>(size, initial);

    for (std::size_t i = 0; i < size; i++) {
        ASSERT_EQ(v[i], initial);
    }
    
    ASSERT_EQ(size, v.size());
}


TEST(Vector, TestDataMethod)
{
    std::size_t size = 5;
    double initial = 5;

    auto v = Vector<double>(size, initial);
    
    auto expected = std::vector<double>(size, initial);
    auto actual = v.data();

    ASSERT_EQ(expected, actual);
}


TEST(Vector, TestOperatorAddWithSingleArgument)
{
    std::size_t size = 10;
    double initial = 5;

    Vector<double> v1(size, initial);
    double x = 2;

    auto v2 = v1 + x;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] + x;
        auto actual = v2[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v2.size());
}


TEST(Vector, TestOperatorSubWithSingleArgument)
{
    std::size_t size = 10;
    double initial = 5;

    Vector<double> v1(size, initial);
    double x = 2;

    auto v2 = v1 - x;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] - x;
        auto actual = v2[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v2.size());
}


TEST(Vector, TestOperatorMulWithSingleArgument)
{
    std::size_t size = 10;
    double initial = 5;

    Vector<double> v1(size, initial);
    double x = 2;

    auto v2 = v1 * x;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] * x;
        auto actual = v2[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v2.size());
}


TEST(Vector, TestOperatorDivWithSingleArgument)
{
    std::size_t size = 10;
    double initial = 5;

    Vector<double> v1(size, initial);
    double x = 2;

    auto v2 = v1 / x;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] / x;
        auto actual = v2[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v2.size());
}


TEST(Vector, TestOperatorAddWithStdVector)
{
    std::size_t size = 5;

    auto v1 = Vector<double>(size, 3);
    auto v2 = std::vector<double>(size, 1);

    auto v3 = v1 + v2;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] + v2[i];
        auto actual = v3[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v3.size());
}


TEST(Vector, TestOperatorSubWithStdVector)
{
    std::size_t size = 5;

    auto v1 = Vector<double>(size, 3);
    auto v2 = std::vector<double>(size, 1);

    auto v3 = v1 - v2;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] - v2[i];
        auto actual = v3[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v3.size());
}


TEST(Vector, TestOperatorAddWithVector)
{
    std::size_t size = 5;

    auto v1 = Vector<double>(size, 1);
    auto v2 = Vector<double>(size, 2);

    auto v3 = v1 + v2;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] + v2[i];
        auto actual = v3[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v3.size());
}


TEST(Vector, TestOperatorSubWithVector)
{
    std::size_t size = 5;

    auto v1 = Vector<double>(size, 1);
    auto v2 = Vector<double>(size, 2);

    auto v3 = v1 - v2;

    for (std::size_t i = 0; i < size; i++) {
        auto expected = v1[i] - v2[i];
        auto actual = v3[i];

        ASSERT_EQ(expected, actual);
    }

    ASSERT_EQ(size, v3.size());
}


TEST(Vector, TestOperatorEqWithStdVector)
{
    auto v1 = Vector<double>(5);
    auto v2 = Vector<double>(6);

    ASSERT_FALSE(v1 == v2);

    v2 = Vector<double>(v1.size(), v1[0] + 1);

    ASSERT_FALSE(v1 == v2);

    v2 = Vector<double>(v1.size(), v1[0]);

    ASSERT_TRUE(v1 == v2);
}


TEST(Vector, TestOperatorEqWithVector)
{
    auto v1 = Vector<double>(5);
    auto v2 = std::vector<double>(6);

    ASSERT_FALSE(v1 == v2);

    v2 = std::vector<double>(v1.size(), v1[0] + 1);

    ASSERT_FALSE(v1 == v2);

    v2 = std::vector<double>(v1.size(), v1[0]);

    ASSERT_TRUE(v1 == v2);
}
