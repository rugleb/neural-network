#include "neuron.h"

Neuron::Neuron() {

}

double Neuron::activate(double x, bool derivative = false) {
    if (derivative) {
        return 1;
    }

    return x;
}

double Neuron::calc(const D_VECTOR &input, const D_VECTOR &weights) {
    double y = 0.;

    for (size_t i = 0; i < input.size(); i++) {
        y += input[i] * weights[i];
    }

    return this->activate(y);
}
