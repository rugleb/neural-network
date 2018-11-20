#ifndef NN_CPP_MODEL_H
#define NN_CPP_MODEL_H

#include "support.h"
#include "layer.h"


struct Set {
    D_VECTOR X;
    D_VECTOR Y;
};


class Model {
    std::vector<Set> dataset;
    std::vector<Layer> layers;
    std::vector<D_MATRIX> weights;
public:
    Model();

    void addLayer(Layer layer);
    void addLayers(Layer layer, size_t count);

    void train(std::vector<Set> dataset, double error);
};


#endif
