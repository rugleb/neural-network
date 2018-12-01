#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "Matrix.h"

typedef double (*callable) (double, bool);


double relu(double x, bool derivative);
double linear(double x, bool derivative);


class Layer {
protected:
    unsigned int units;
    callable activation;
public:
    Layer(unsigned int units, callable activation);
    vector activate(vector input);
};


#endif
