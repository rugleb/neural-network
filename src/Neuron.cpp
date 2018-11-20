#include "Neuron.h"

Neuron::Neuron()
{

}

double Neuron::activate(double x, bool derivative = false)
{
    if (derivative) {
        return 1;
    }

    return x;
}

double Neuron::calc(const D_VECTOR &input, const D_VECTOR &weights)
{
    double y = input * weights;

    return this->activate(y);
}
