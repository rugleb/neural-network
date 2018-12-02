#include <iostream>

#include "Model.h"
#include "Training.h"

void Model::add(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::fit(const std::vector<data> &dataset, std::size_t maxEpochs, double acc)
{
    Training training(this);

    training.run(maxEpochs, acc, dataset);

    std::cout << "Training time: " << training.getTime() << " ms" << std::endl;
    std::cout << "Training epochs: " << training.getEpochs() << std::endl;
    std::cout << "Training accuracy: " << training.getAcc() << std::endl;
}
