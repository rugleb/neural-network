#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>
#include "Layer.h"


class Model {
protected:
    std::vector<Layer> layers;
public:
    void add(Layer layer);
};


#endif
