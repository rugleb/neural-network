#include "Layer.h"

Layer::Layer(unsigned int units, callable activation)
{
    this->units = units;
    this->activation = activation;
}

double linear(double x)
{
    return x;
}

double relu(double x)
{
    if (x > 0) {
        return x;
    }

    return x;
}
