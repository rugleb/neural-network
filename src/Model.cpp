#include <algorithm>

#include "Model.h"

#define SQUARE(x) (x * x)


Model::Model()
{
    Layer layer;
    this->layers = {layer};
}

void Model::addLayer(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::train(std::vector<Set> dataset, double error)
{
    this->init(dataset.front());

    for (size_t epoch = 0; epoch < 1; epoch++) {
        double err = .0;

        for (Set &set : dataset) {
            D_VECTOR output = this->feedForward(set.X);
            err += this->error(set.Y, output);
        }

        if (err / dataset.size() < error) break;
    }
}

D_VECTOR Model::feedForward(const D_VECTOR x)
{
    D_VECTOR output = x;

    for (size_t i = 0; i < this->weights.size(); i++) {
        D_MATRIX w = this->weights[i];
        Layer layer = this->layers[i + 1];

        output = layer.activate(output, w);
    }

    return output;
}

void Model::init(const Set &set)
{
    this->generateLayers(set);
    this->generateWeights(set);
}

void Model::generateLayers(const Set &set)
{
    Layer first(Neuron(), set.X.size());
    Layer last(Neuron(), set.Y.size());

    this->layers[0] = first;
    this->layers.push_back(last);
}

void Model::generateWeights(const Set &set)
{
    this->weights = {};
    for (size_t i = 1; i < this->layers.size(); i++) {

        size_t rowsCount = this->layers[i - 0].getNeurons().size();
        size_t colsCount = this->layers[i - 1].getNeurons().size();

        D_MATRIX localWeights;
        for (size_t j = 0; j < rowsCount; j++) {

            D_VECTOR row(colsCount);
            for (size_t k = 0; k < colsCount; k++) {
                row[k] = .1;
            }

            localWeights.push_back(row);
        }

        this->weights.push_back(localWeights);
    }
}

double Model::error(const D_VECTOR &expected, const D_VECTOR &actual)
{
    double err = .0;
    size_t size = expected.size();

    for (size_t i = 0; i < size; i++) {
        err += SQUARE(actual[i] - expected[i]) / 2;
    }

    return err;
}
