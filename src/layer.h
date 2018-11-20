#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H


#include "support.h"
#include "neuron.h"

class Layer {
protected:
    std::vector<Neuron> neurons;
public:
    Layer();

    void addNeuron(Neuron);
};


#endif
