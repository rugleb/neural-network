#include "Layer.h"

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

Layer::Layer(unsigned int neurons, callable activation)
{
    this->neurons = neurons;
    this->activation = activation;
}
