#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "Matrix.h"

class Layer {
protected:
    unsigned int units;
    callable activation;
public:
    Layer(unsigned int units, callable activation);
    vector activate(vector input);
    unsigned int getUnits() { return this->units; };
    callable getActivation() { return this->activation; };
};


#endif
