#include "layer.h"

Layer::Layer() {

}

void Layer::addNeuron(const Neuron neuron) {
    this->neurons.push_back(neuron);
}

D_VECTOR Layer::calc(const D_VECTOR input, const D_MATRIX weights) {
    D_VECTOR output(this->neurons.size());

    for (size_t i = 0; i < this->neurons.size(); i++) {
        Neuron neuron = this->neurons[i];
        output[i] = neuron.calc(input, weights[i]);
    }

    return output;
}

void Layer::addNeurons(const Neuron neuron, const size_t count) {
    for (size_t i = 0; i < count; i++) {
        this->addNeuron(neuron);
    }
}
