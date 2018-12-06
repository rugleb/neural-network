#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H

typedef double (*callable) (double, bool);

double relu (double, bool = false);
double linear (double, bool = false);

class Layer {
protected:
    callable activation;
    unsigned int neurons;
public:
    Layer(unsigned int neurons, callable activation);
};


#endif
