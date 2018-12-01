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

double rand(double min, double max)
{
    std::random_device device;
    std::default_random_engine engine(device);

    std::uniform_real_distribution<double> uniform(min, max);

    return uniform(engine);
}

double2 rand(unsigned int size, double min, double max)
{
    double2 vector(size);

    for (unsigned int i = 0; i < size; i++) {
        vector[i] = rand(min, max);
    }

    return vector;
}

double3 rand(unsigned int rows, unsigned int cols, double min, double max)
{
    double3 matrix(rows);

    for (unsigned int i = 0; i < rows; i++) {
        matrix[i] = rand(cols, min, max);
    }

    return matrix;
}
