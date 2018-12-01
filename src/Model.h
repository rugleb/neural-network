#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>

#include "Layer.h"
#include "Matrix.h"

#define  SQUARE(x)  (x * x)


typedef struct {
    double2 X;
    double2 Y;
} data;


double MSE(double2 e);


class Model {
protected:
    std::vector<Layer> layers;

    double2 feedforward(data trainSet);
public:
    void add(Layer layer);
    void fit(std::vector<data> dataset, std::size_t epochs, double precision);
};


#endif
