#include "Layer.h"

Layer::Layer(unsigned int neurons, callable activation)
{
    this->neurons = neurons;
    this->activation = activation;
}
