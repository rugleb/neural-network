#include "Layer.h"

Layer::Layer(unsigned int units, callable activation)
{
    this->units = units;
    this->activation = activation;
}

vector Layer::activate(vector input)
{
    return input;
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

matrix relu(const matrix &m, bool derivative)
{
    std::size_t rows = m.size();
    std::size_t cols = m.front().size();

    matrix y(rows);

    for (std::size_t i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; j++) {
            y[i][j] = relu(m[i][j], derivative);
        }
    }

    return  y;
}

matrix linear(const matrix &m, bool derivative)
{
    std::size_t rows = m.size();
    std::size_t cols = m.front().size();

    matrix y(rows);

    for (std::size_t i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (std::size_t j = 0; j < cols; j++) {
            y[i][j] = linear(m[i][j], derivative);
        }
    }

    return  y;
}
