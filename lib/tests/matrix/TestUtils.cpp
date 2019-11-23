#include <algorithm>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Matrix/Utils.hpp"


using namespace testing;


TEST(Rand, TestThatUnitRandomized)
{
    double min = 10.;
    double max = 20.;

    auto unit = rand(min, max);

    ASSERT_GE(unit, min);
    ASSERT_LE(unit, max);
}


TEST(Rand, TestThatVectorRandomized)
{
    std::size_t size = 5;

    double min = 10;
    double max = 20;

    auto vector = rand(min, max, size);

    ASSERT_EQ(size, vector.size());
    ASSERT_THAT(vector, Each(AllOf(Ge(min), Le(max))));
}


TEST(Rand, TestThatMatrixRandomized)
{
    std::size_t rows = 2;
    std::size_t cols = 4;

    double min = 10.;
    double max = 20.;

    auto matrix = rand(min, max, rows, cols);

    ASSERT_EQ(rows, matrix.size());

    for (const auto & vector : matrix) {
        ASSERT_EQ(cols, vector.size());
        ASSERT_THAT(vector, Each(AllOf(Ge(min), Le(max))));
    }
}


TEST(Shuffle, TestThatVectorShuffled)
{
    std::vector<int> vector = {1, 2, 3, 4};

    shuffle(vector);
    ASSERT_THAT(vector, Not(ElementsAre(1, 2, 3, 4)));
}
