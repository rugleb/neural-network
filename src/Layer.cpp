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
