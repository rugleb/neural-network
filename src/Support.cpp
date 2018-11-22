#include <cmath>
#include "Support.h"

D_VECTOR operator*(const D_VECTOR &a, double b)
{
    std::size_t size = a.size();
    D_VECTOR y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] * b;
    }

    return y;
}

double operator*(const D_VECTOR &a, const D_VECTOR &b)
{
    std::size_t size = a.size();
    double y = 0.;

    for (std::size_t i = 0; i < size; i++) {
        y = a[i] * b[i];
    }

    return y;
}

D_VECTOR operator+(const D_VECTOR &a, const D_VECTOR &b)
{
    std::size_t size = a.size();
    D_VECTOR y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] + b[i];
    }

    return y;
}

D_VECTOR operator-(const D_VECTOR &a, const D_VECTOR &b)
{
    std::size_t size = a.size();
    D_VECTOR y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = a[i] - b[i];
    }

    return y;
}

double sum(const D_VECTOR &x)
{
    double y = .0;

    for (double i : x) {
        y += i;
    }

    return y;
}

double mid(const D_VECTOR &x)
{
    return sum(x) / x.size();
}

double random(double min, double max)
{
    return min + ((double) rand() / RAND_MAX) * (max - min);
}

D_VECTOR random(std::size_t size, double min, double max)
{
    D_VECTOR y(size);

    for (std::size_t i = 0; i < size; i++) {
        y[i] = random(min, max);
    }

    return y;
}

D_MATRIX random(std::size_t linesSize, std::size_t columnsSize, double min, double max)
{
    D_MATRIX y(linesSize);

    for (std::size_t i = 0; i < linesSize; i++) {
        y[i] = random(columnsSize, min, max);
    }

    return y;
}
