#ifndef NN_CPP_MODEL_H
#define NN_CPP_MODEL_H

#include "Support.h"
#include "Layer.h"


struct Set {
    D_VECTOR X;
    D_VECTOR Y;
};


class Model
{
protected:
    std::vector<Layer> layers;

    void init(const Set &set);
    double error(const D_VECTOR &expected, const D_VECTOR &actual);
    void backPropagation(const D_VECTOR &e);
public:
    Model();
    void addLayer(Layer layer);
    void train(std::vector<Set> dataset, double error);
    D_VECTOR feedForward(D_VECTOR x);
};


#endif
