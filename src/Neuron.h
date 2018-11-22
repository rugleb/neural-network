#ifndef NEURAL_NETWORK_NEURON_H
#define NEURAL_NETWORK_NEURON_H

#include "Support.h"


class Neuron {
protected:
    D_VECTOR weights;
public:
    explicit Neuron(std::size_t size);

    double activate(double x);
    double calc(D_VECTOR x);
};


#endif
