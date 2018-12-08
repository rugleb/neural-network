#include "Layer.h"

Layer::Layer(unsigned long neurons, callable activation)
{
    this->neurons = neurons;
    this->activation = activation;
}

matrix Layer::activate(const matrix &m, bool derivative)
{
    auto rows = m.size();
    auto cols = m.front().size();

    matrix y(rows);

    for (auto i = 0; i < rows; i++) {
        y[i] = vector(cols);
        for (auto j = 0; j < cols; j++) {
            y[i][j] = this->activate(m[i][j], derivative);
        }
    }

    return y;
}

unsigned long Layer::getNeurons()
{
    return this->neurons;
}

double Layer::activate(double x, bool derivative)
{
    return this->activation(x, derivative);
}
