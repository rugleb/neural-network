#include "Model.h"

void Model::add(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::fit(std::vector<data> dataset, std::size_t epochs, double precision)
{
    for (std::size_t epoch = 0; epoch < epochs; epoch++) {

        double error = .0;

        for (data &set : dataset) {
            vector e = this->feedforward(set);
            error += MSE(e);
        }

        error /= dataset.size();

        if (error < precision) {
            break;
        }
    }
}

vector Model::feedforward(data trainSet)
{
    vector output = trainSet.x;

    for (Layer &layer : this->layers) {
        output = layer.activate(output);
    }

    return trainSet.y - output;
}

double MSE(vector e)
{
    std::size_t size = e.size();
    double y = .0;

    for (double &x : e) {
        y += SQUARE(x);
    }

    return y / size;
}
