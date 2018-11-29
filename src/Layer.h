#ifndef NEURAL_NETWORK_LAYER_H
#define NEURAL_NETWORK_LAYER_H


typedef double (*callable) (double);

class Layer {
protected:
    unsigned int units;
    callable activation;
public:
    Layer(unsigned int units, callable activation);
};


#endif
