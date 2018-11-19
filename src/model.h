#ifndef NN_CPP_MODEL_H
#define NN_CPP_MODEL_H

#include "support.h"


struct Set {
    D_VECTOR X;
    double y;
};


class Model {
    std::vector<Set> dataset;
    std::vector<D_VECTOR> W;
public:
    Model();
    void train(std::vector<Set>, double);
    double activate(double);
};


#endif
