#include "Layer.h"

Layer::Layer()
{

}

void Layer::addNeuron(Neuron neuron)
{
    this->neurons.push_back(neuron);
}

void Layer::addNeurons(Neuron neuron, std::size_t number)
{
    for (std::size_t i = 0; i < number; i++) {
        this->addNeuron(neuron);
    }
}

D_VECTOR Layer::calc(const D_VECTOR input)
{
    D_VECTOR output(this->neurons.size());

    for (std::size_t i = 0; i < input.size(); i++) {
        output[i] = neurons[i].calc(input);
    }

    return output;
}
