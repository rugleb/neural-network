#include "Layer.h"

Layer::Layer(unsigned long dimension, callable activation)
{
    this->dim = dimension;
    this->activation = activation;
}

unsigned long Layer::dimension()
{
    return this->dim;
}

matrix Layer::activate(const matrix &x, bool derivative)
{
    auto rows = x.size();
    auto cols = x.front().size();

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = this->activate(x[i][j], derivative);
        }
    }

    return y;
}

double Layer::activate(double x, bool derivative)
{
    return this->activation(x, derivative);
}
