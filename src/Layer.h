#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "support/math.h"

class Layer {
protected:
    callable activation;
    unsigned long neurons;
public:
    Layer(unsigned long neurons, callable activation);
    matrix activate(const matrix &m, bool derivative = false);
    double activate(double x, bool derivative = false);
    unsigned long getNeurons();
};


#endif
