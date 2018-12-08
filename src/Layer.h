#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "support/math.h"

class Layer {
protected:
    unsigned long dim;
    callable activation;
public:
    Layer(unsigned long neurons, callable activation);
    matrix activate(const matrix &x, bool derivative = false);
    double activate(double x, bool derivative = false);
    unsigned long dimension();
};


#endif
