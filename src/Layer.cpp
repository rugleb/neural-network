#include "Layer.h"

Layer::Layer()
{

}

void Layer::addNeuron(Neuron neuron)
{
    this->neurons.push_back(neuron);
}

void Layer::addNeurons(Neuron neuron, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        this->addNeuron(neuron);
    }
}

D_VECTOR Layer::activate(const D_VECTOR &input, const D_MATRIX &weights)
{
    D_VECTOR output(this->neurons.size());

    for (size_t i = 0; i < this->neurons.size(); i++) {
        Neuron neuron = this->neurons[i];
        output[i] = neuron.calc(input, weights[i]);
    }

    return output;
}
