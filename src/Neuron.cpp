#include "Neuron.h"

Neuron::Neuron(std::size_t weightsNumber)
{
    this->weights.reserve(weightsNumber);
}

double Neuron::activate(double x)
{
    return x;
}

double Neuron::calc(const D_VECTOR input)
{
    return this->activate(input * this->weights);
}
