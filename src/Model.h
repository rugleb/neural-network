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

typedef struct {
    std::vector<data> dataset;
    std::double_t accuracy;
    std::double_t teach;
    std::size_t epochs;
} trainParams;

class Model {
protected:
    std::vector<Layer> layers;
public:
    void add(Layer layer);
    void fit(trainParams params);
    vector predict(const vector &);
};

void shuffle(std::vector<data>);

#endif
