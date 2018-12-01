#include "Matrix.h"

std::size_t checkDim(const vector &a, const vector &b)
{
    std::size_t size = a.size();

    if (size != b.size()) {
        throw "Error: invalid dimension of vectors";
    }

    return size;
}

std::size_t checkDim(const matrix &a, const vector &b)
{
    std::size_t size = b.size();

    if (size != a.front().size()) {
        throw "Error: invalid dimension of vectors";
    }

    return size;
}

vector operator*(const matrix &a, const vector &b)
{
    std::size_t size = checkDim(a, b);
    vector y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] * b;
    }

    return y;
}

double operator*(const vector &a, const vector &b)
{
    std::size_t size = checkDim(a, b);
    double y = .0;

    for (std::size_t i = 0; i < size; i++) {
        y += a[i] * b[i];
    }

    return y;
}

vector operator*(const vector &a, unit &b)
{
    std::size_t size = a.size();
    vector y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] * b;
    }

    return y;
}

vector operator+(const vector &a, const vector &b)
{
    std::size_t size = checkDim(a, b);
    vector y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] + b[i];
    }

    return y;
}

vector operator-(const vector &a, const vector &b)
{
    std::size_t size = checkDim(a, b);
    vector y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] - b[i];
    }

    return y;
}

vector operator^(const vector &a, const vector &b)
{
    std::size_t size = checkDim(a, b);
    vector y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] * b[i];
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

vector rand(unsigned int size, double min, double max)
{
    vector vector(size);

    for (unsigned int i = 0; i < size; i++) {
        vector[i] = rand(min, max);
    }

    return vector;
}

matrix rand(unsigned int rows, unsigned int cols, double min, double max)
{
    matrix matrix(rows);

    for (unsigned int i = 0; i < rows; i++) {
        matrix[i] = rand(cols, min, max);
    }

    return matrix;
}
