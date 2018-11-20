#ifndef NEURAL_NETWORK_NEURON_H
#define NEURAL_NETWORK_NEURON_H

#include "Support.h"


class Neuron {
public:
    Neuron();

    double activate(double x, bool derivative);
    double calc(const D_VECTOR &input, const D_VECTOR &weights);
};


#endif
