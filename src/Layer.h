#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "support/math.h"

class Layer {
protected:
    callable activation;
    unsigned int neurons;
public:
    Layer(unsigned int neurons, callable activation);
};


#endif
