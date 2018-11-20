#include "layer.h"

Layer::Layer() {

}

void Layer::addNeuron(Neuron neuron) {
    this->neurons.push_back(neuron);
}
