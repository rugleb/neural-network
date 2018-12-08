#include "math.h"

const char * MatrixException::what() const noexcept
{
    return "Can't perform an operation on matrices";
}

matrix operator+(const matrix &a, const matrix &b)
{
    auto rows = a.size();
    auto cols = a.front().size();

    if (b.size() != rows || b.front().size() != cols) {
        throw MatrixException();
    }

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = a[i][j] + b[i][j];
        }
    }

    return y;
}

matrix operator-(const matrix &a, const matrix &b)
{
    auto rows = a.size();
    auto cols = a.front().size();

    if (b.size() != rows || b.front().size() != cols) {
        throw MatrixException();
    }

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = a[i][j] - b[i][j];
        }
    }

    return y;
}

matrix operator^(const matrix &a, const matrix &b)
{
    auto rows = a.size();
    auto cols = a.front().size();

    if (b.size() != rows || b.front().size() != cols) {
        throw MatrixException();
    }

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = a[i][j] * b[i][j];
        }
    }

    return y;
}

matrix operator*(const matrix &a, const matrix &b)
{
    auto rows = a.size();
    auto cols = b.front().size();

    if (a.front().size() != b.size()) {
        throw MatrixException();
    }

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = 0;
            for (auto k = 0; k < a.front().size(); k++) {
                y[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return y;
}

matrix operator*(const matrix &a, double b)
{
    auto rows = a.size();
    auto cols = a.front().size();

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = a[i][j] * b;
        }
    }

    return y;
}

matrix T(const matrix &m)
{
    auto rows = m.front().size();
    auto cols = m.size();

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = m[j][i];
        }
    }

    return y;
}

matrix T(const vector &v)
{
    auto rows = v.size();
    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = { v[i] };
    }

    return y;
}

double rand(double min, double max)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<> distribution(min, max);

    return distribution(generator);
}

vector rand(unsigned long size, double min, double max)
{
    vector v(size);

    for (auto i = 0; i < size; i++) {
        v[i] = rand(min, max);
    }

    return v;
}

matrix rand(unsigned long rows, unsigned long cols, double min, double max)
{
    matrix m(rows);

    for (auto i = 0; i < rows; i++) {
        m[i] = rand(cols, min, max);
    }

    return m;
}

double relu(double x, bool derivative)
{
    if (derivative) {
        return x > 0 ? 1. : 0.;
    }

    return x > 0 ? x : 0.;
}

double linear(double x, bool derivative)
{
    if (derivative) {
        return 1.;
    }

    return x;
}

double sigmoid(double x, bool derivative)
{
    double y = 1. / (1. + exp(-x));

    if (derivative) {
        return y * (1. - y);
    }

    return y;
}

double tanh(double x, bool derivative)
{
    double y = (exp(2 * x) - 1) / (exp(2 * x) + 1);

    if (derivative) {
        return 4. / square(exp(-x) + exp(x));
    }

    return y;
}

double MSE(const vector &e, const vector &a)
{
    auto size = e.size();
    double y = 0.;

    for (auto i = 0; i < size; i++) {
        y += square(e[i] - a[i]) / 2;
    }

    return y / size;
}

double MSE(const matrix &e, const matrix &a)
{
    auto size = e.size();
    double y = 0.;

    for (auto i = 0; i < size; i++) {
        y += square(e[i][0] - a[i][0]) / 2;
    }

    return y / size;
}

double relative(const matrix &e, const matrix &a)
{
    auto rows = e.size();
    double y = .0;

    for (auto i = 0; i < rows; i++) {
        y += fabs((e[i][0] - a[i][0]) / e[i][0]);
    }

    return y / rows;
}
