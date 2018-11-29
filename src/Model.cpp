#include "Model.h"

void Model::add(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::fit(dataset dataset, std::size_t epochs, double precision)
{
    for (std::size_t epoch = 0; epoch < epochs; epoch++) {

        double error = .0;

        for (set &set : dataset) {
            double2 e = this->feedforward(set);
            error += MSE(e);
        }

        error /= dataset.size();

        if (error < precision) {
            break;
        }
    }
}

double2 Model::feedforward(set trainSet)
{
    double2 output = trainSet.X;

    for (Layer &layer : this->layers) {
        output = layer.activate(output);
    }

    return trainSet.Y - output;
}

double MSE(double2 e)
{
    std::size_t size = e.size();
    double y = .0;

    for (int i = 0; i < size; ++i) {
        y += SQUARE(e[i]);
    }

    return y / size;
}
