#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>
#include "Layer.h"


typedef std::vector<double> double2;

typedef struct {
    double2 X;
    double2 Y;
} set;

typedef std::vector<set> dataset;


class Model {
protected:
    std::vector<Layer> layers;
public:
    void add(Layer layer);
    void fit(dataset dataset, std::size_t epochs, double precision);
};


#endif
