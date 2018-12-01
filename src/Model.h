#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>

#include "Layer.h"

typedef struct {
    vector x;
    vector y;
} data;

class Model {
protected:
    std::vector<Layer> layers;
public:
    void add(Layer layer);
    void fit(const std::vector<data> &dataset, std::size_t epochs, double precision);

    std::vector<Layer> getLayers() { return this->layers; };
};


#endif
