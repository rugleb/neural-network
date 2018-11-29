#include "Matrix.h"

std::size_t checkDim(const double2 &a, const double2 &b)
{
    std::size_t size = a.size();

    if (size != b.size()) {
        throw "Error: invalid dimension of vectors";
    }

    return size;
}

double operator*(const double2 &a, const double2 &b)
{
    std::size_t size = checkDim(a, b);
    double y = .0;

    for (std::size_t i = 0; i < size; i++) {
        y += a[i] * b[i];
    }

    return y;
}

double2 operator+(const double2 &a, const double2 &b)
{
    std::size_t size = checkDim(a, b);
    double2 y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] + b[i];
    }

    return y;
}

double2 operator-(const double2 &a, const double2 &b)
{
    std::size_t size = checkDim(a, b);
    double2 y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] - b[i];
    }

    return y;
}
