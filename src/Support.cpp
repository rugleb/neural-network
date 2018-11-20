#include <cmath>
#include "Support.h"

D_VECTOR operator*(D_VECTOR a, double b)
{
    size_t size = a.size();
    D_VECTOR y(size);

    for (size_t i = 0; i < size; i++) {
        y[i] = a[i] * b;
    }

    return y;
}

double operator*(D_VECTOR a, D_VECTOR b)
{
    size_t size = a.size();
    double y = 0.;

    for (size_t i = 0; i < size; i++) {
        y = a[i] * b[i];
    }

    return y;
}

D_VECTOR operator+(D_VECTOR a, D_VECTOR b)
{
    size_t size = a.size();
    D_VECTOR y(size);

    for (size_t i = 0; i < size; i++) {
        y[i] = a[i] + b[i];
    }

    return y;
}

D_VECTOR operator-(D_VECTOR a, D_VECTOR b)
{
    size_t size = a.size();
    D_VECTOR y(size);

    for (size_t i = 0; i < size; i++) {
        y[i] = a[i] - b[i];
    }

    return y;
}
