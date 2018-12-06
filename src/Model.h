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
    void fit(const dataset &data, double acc, std::size_t epochs);
};

class Training {
protected:
    Model *model;

    matrix feedforward(set sample);
    void backPropagation(matrix e);
public:
    explicit Training(Model * model);
    void compile();
    void run(dataset dataset, double acc, std::size_t epochs);
};

double MSE(const matrix &e);

#endif
