#include "Layer.h"

Layer::Layer(unsigned int units, callable activation)
{
    this->units = units;
    this->activation = activation;
}

double2 Layer::activate(double2 input)
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
