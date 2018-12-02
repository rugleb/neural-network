#ifndef NEURAL_NETWORK_TRAINING_H
#define NEURAL_NETWORK_TRAINING_H

#include <vector>
#include <random>
#include <ctime>

#include "Matrix.h"
#include "Model.h"


typedef struct {
    matrix x;
    matrix y;
    matrix weights;
    matrix derivative;
    callable activation;
} layer;


class Training {
protected:
    std::vector<layer> layers;

    Model * model;
    std::size_t epochs;
    float time;
    double accuracy;

    unit teach = 0.7;

    void compile(const std::vector<data> &dataset);
    matrix feedforward(data set);
    void backPropagation(matrix e);
public:
    explicit Training(Model * model);
    void run(std::size_t epochs, double acc, std::vector<data> dataset);

    float getTime();
    double getAcc();
    std::size_t getEpochs();
};


#endif
