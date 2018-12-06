#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>
#include "Layer.h"
#include "Matrix.h"

typedef struct {
    vector x;
    vector y;
} set;

typedef std::vector<set> dataset;

class Model {
protected:
    std::vector<Layer> layers;
public:
    void add(Layer layer);
    void fit(dataset trains, double acc, std::size_t epochs);
};


#endif
