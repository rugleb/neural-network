#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H


#include "support.h"
#include "neuron.h"

class Layer {
protected:
    std::vector<Neuron> neurons;
public:
    Layer();
    Layer(const Neuron &neuron, size_t count = 1) {
        this->addNeurons(neuron, count);
    }

    std::vector<Neuron> getNeurons() {
        return neurons;
    }

    void addNeuron(Neuron neuron);
    void addNeurons(Neuron neuron, size_t count);

    D_VECTOR calc(D_VECTOR input, D_MATRIX weights);
};


#endif
