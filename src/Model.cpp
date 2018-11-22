#include <algorithm>

#include "Model.h"


Model::Model()
{
    this->layers = {};
}

void Model::addLayer(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::train(std::vector<Set> dataset, double error)
{
    this->init(dataset.front());

    for (std::size_t epoch = 0; epoch < 1; epoch++) {
        double err = .0;

        for (Set &set : dataset) {
            D_VECTOR output = this->feedForward(set.X);
            this->backPropagation(set.Y - output);

            err += this->error(set.Y, output);
        }

        if (err / dataset.size() < error) break;
    }
}

D_VECTOR Model::feedForward(D_VECTOR output)
{
    for (Layer &layer : this->layers) {
        output = layer.calc(output);
    }

    return output;
}

void Model::init(const Set &set)
{
    for (Layer &layer : this->layers) {
        layer.randomize(-0.1, 0.1);
    }
}

double Model::error(const D_VECTOR &expected, const D_VECTOR &actual)
{
    double err = .0;
    std::size_t size = expected.size();

    for (std::size_t i = 0; i < size; i++) {
        err += SQUARE(actual[i] - expected[i]) / 2;
    }

    return err;
}

void Model::backPropagation(const D_VECTOR &e)
{
    
}
