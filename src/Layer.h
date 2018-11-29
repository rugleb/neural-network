#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

#include "Matrix.h"

typedef double (*callable) (double);


double relu(double x);
double linear(double x);


class Layer {
protected:
    unsigned int units;
    callable activation;
public:
    Layer(unsigned int units, callable activation);
    double2 activate(double2 input);
};


#endif
