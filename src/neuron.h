#ifndef NEURAL_NETWORK_NEURON_H
#define NEURAL_NETWORK_NEURON_H


#include "support.h"

class Neuron {
public:
    Neuron();

    double activate(double);
    double calc(D_VECTOR, D_VECTOR);
};


#endif
