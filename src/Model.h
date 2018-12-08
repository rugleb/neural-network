#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>
#include <random>
#include <algorithm>

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
    void fit(std::vector<data>, double, std::size_t);
    vector predict(const vector &);
};

void shuffle(std::vector<data>);

#endif
