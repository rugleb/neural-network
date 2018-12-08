#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>

#include "Layer.h"
#include "support/math.h"

typedef struct {
    vector x;
    vector y;
} data;

class Model {
protected:
    std::vector<Layer> layers;
public:
    void add(Layer layer);
    void fit(const std::vector<data> &, double, std::size_t);
};

#endif
