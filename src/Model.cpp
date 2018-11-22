#include <algorithm>

#include "Model.h"


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

D_VECTOR Model::feedForward(const D_VECTOR x)
{
    D_VECTOR output = x;

    for (std::size_t i = 0; i < this->weights.size(); i++) {
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
    for (std::size_t i = 1; i < this->layers.size(); i++) {

        std::size_t linesSize = this->layers[i - 0].getNeurons().size();
        std::size_t columnsSize = this->layers[i - 1].getNeurons().size();

        D_MATRIX w = random(linesSize, columnsSize, -0.1, 0.1);
        this->weights.push_back(w);
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
