#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "Support.h"
#include "Neuron.h"


class Layer
{
protected:
    std::vector<Neuron> neurons;
public:
    Layer();
    Layer(const Neuron &neuron, std::size_t number = 1) {
        this->addNeurons(neuron, number);
    }

    std::vector<Neuron> getNeurons() {
        return neurons;
    }

    void addNeuron(Neuron neuron);
    void addNeurons(Neuron neuron, std::size_t count);

    D_VECTOR calc(D_VECTOR input);
};


#endif
