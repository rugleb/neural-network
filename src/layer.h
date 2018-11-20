#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H


#include "support.h"

class Layer {
protected:
    D_VECTOR input;
    D_VECTOR output;
public:
    Layer();
};


#endif
