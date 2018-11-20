#include "neuron.h"

Neuron::Neuron() {

}

double Neuron::activate(double x) {
    return x;
}

double Neuron::calc(D_VECTOR input, D_VECTOR weights) {
    double y = 0.;

    for (size_t i = 0; i < input.size(); i++) {
        y += input[i] * weights[i];
    }

    return this->activate(y);
}
