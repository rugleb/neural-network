#ifndef NN_CPP_MODEL_H
#define NN_CPP_MODEL_H

#include "support.h"


struct Set {
    D_VECTOR X;
    D_VECTOR Y;
};


class Model {
    std::vector<Set> dataset;
    std::vector<D_MATRIX> weights;
public:
    Model();
    void train(std::vector<Set>, double);
    double activate(double);
    D_VECTOR activate(D_VECTOR);
};


#endif
