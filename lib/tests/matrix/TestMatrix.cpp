#include "gtest/gtest.h"

#include "Matrix/Matrix.hpp"

typedef double data_t;


TEST(MatrixTestCase, testDimMethod)
{
    std::size_t rows = 2;
    std::size_t cols = 3;

    auto matrix = Matrix<data_t>(rows, cols);

    ASSERT_EQ(rows, matrix.nRows());
    ASSERT_EQ(cols, matrix.nCols());

    auto dim = Dim(rows, cols);
    ASSERT_EQ(dim, matrix.dim());
}


TEST(MatrixTestCase, testOperatorEqualToMatrix)
{
    std::size_t rows = 2;
    std::size_t cols = 3;

    auto m1 = Matrix<data_t>(rows, cols);
    auto m2 = Matrix<data_t>(rows, cols);

    ASSERT_EQ(m1, m2);
}


TEST(MatrixTestCase, testOperatorNotEqualToMatrix)
{
    std::size_t rows = 2;
    std::size_t cols = 3;

    auto m1 = Matrix<data_t>(rows, cols, 5);
    auto m2 = Matrix<data_t>(rows, cols, 10);

    ASSERT_NE(m1, m2);
}
