#include "Matrix.h"

matrix operator*(const matrix &a, const matrix &b)
{
    std::size_t rows = a.size();
    std::size_t cols = b.front().size();

    if (a.front().size() != b.size()) {
        throw "Error: matrix dimension is wrong";
    }

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            for (std::size_t k = 0; k < a.front().size(); ++k) {
                y[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return y;
}

matrix operator+(const matrix &a, const matrix &b)
{
    std::size_t rows = a.size();
    std::size_t cols = a.front().size();

    if (rows != b.size() || cols != b.front().size()) {
        throw "Error: matrix dimension is wrong";
    }

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            y[i][j] = a[i][j] + b[i][j];
        }
    }

    return y;
}

matrix operator-(const matrix &a, const matrix &b)
{
    std::size_t rows = a.size();
    std::size_t cols = a.front().size();

    if (rows != b.size() || cols != b.front().size()) {
        throw "Error: matrix dimension is wrong";
    }

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            y[i][j] = a[i][j] - b[i][j];
        }
    }

    return y;
}

matrix operator^(const matrix &a, const matrix &b)
{
    std::size_t rows = a.size();
    std::size_t cols = a.front().size();

    if (rows != b.size() || cols != a.front().size()) {
        throw "Error: matrix dimension is wrong";
    }

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            y[i][j] = a[i][j] * b[i][j];
        }
    }

    return y;
}

matrix operator*(const matrix &a, double b)
{
    std::size_t rows = a.size();
    std::size_t cols = a.front().size();

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            y[i][j] = a[i][j] * b;
        }
    }

    return y;
}

double rand(double min, double max)
{
    std::random_device device;
    std::default_random_engine engine(device());

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

matrix transpose(const vector &m)
{
    std::size_t size = m.size();
    matrix y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = {m[i]};
    }

    return y;
}

matrix activate(const matrix &m, callable f)
{
    std::size_t rows = m.size();
    std::size_t cols = m.front().size();

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            y[i][j] = f(m[i][j], false);
        }
    }

    return y;
}

matrix derivative(const matrix &m, callable f)
{
    std::size_t rows = m.size();
    std::size_t cols = m.front().size();

    matrix y(rows);

    for (std::size_t i = 0; i < rows; ++i) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; ++j) {
            y[i][j] = f(m[i][j], true);
        }
    }

    return y;
}

double linear(double x, bool derivative = false)
{
    if (derivative) {
        return 1.;
    }

    return x;
}

double relu(double x, bool derivative = false)
{
    if (derivative) {
        return x > 0 ? 1. : 0.;
    }

    return x > 0 ? x : 0.;
}

double MSE(matrix e)
{
    std::size_t size = e.size();
    double y = .0;

    for (vector &x : e) {
        y += x.front() * x.front();
    }

    return y / size;
}

double sigmoid(double x, bool derivative)
{
    if (derivative) {
        double y = sigmoid(x, false);
        return (1 - y) * y;
    }

    return 1 / (1 + exp(-x));
}

matrix transpose(const matrix &m)
{
    std::size_t rows = m.front().size();
    std::size_t cols = m.size();

    matrix y(rows);

    for (std::size_t i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; j++) {
            y[i][j] = m[j][i];
        }
    }

    return y;
}
