#ifndef NN_CPP_MODEL_H
#define NN_CPP_MODEL_H

#include "support.h"
#include "layer.h"


struct Set {
    D_VECTOR X;
    D_VECTOR Y;
};


class Model {
    std::vector<Layer> layers;
    std::vector<D_MATRIX> weights;

    void generateLayers(const Set &set);
    void generateWeights(const Set &set);
    double error(const D_VECTOR &expected, const D_VECTOR &actual);
public:
    Model();

    void addLayer(Layer layer);

    void train(std::vector<Set> dataset, double error);
    D_VECTOR feedForward(D_VECTOR x);
};


#endif
