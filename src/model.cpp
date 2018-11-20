#include <algorithm>

#include "model.h"

Model::Model() {
    Layer layer;
    this->layers.push_back(layer);
}

void Model::train(std::vector<Set> dataset, double error) {

    Layer front(Neuron(), dataset.front().X.size());
    Layer back(Neuron(), dataset.front().Y.size());

    this->layers[0] = front;
    this->layers.push_back(back);

    for (size_t i = 1; i < this->layers.size(); i++) {

        size_t rowsCount = this->layers[i].getNeurons().size();
        size_t colsCount = this->layers[i - 1].getNeurons().size();

        D_MATRIX localWeights;
        for (size_t j = 0; j < rowsCount; j++) {
            D_VECTOR row(colsCount);
            for (size_t k = 0; k < colsCount; k++) {
                row[k] = 0.1;
            }
            localWeights.push_back(row);
        }

        this->weights.push_back(localWeights);
    }

    for (size_t epoch = 0; epoch < 1; epoch++) {
        for (Set &set : dataset) {
            D_VECTOR output = this->feedForward(set.X);
        }
    }
}

D_VECTOR Model::feedForward(const D_VECTOR x) {
    D_VECTOR output = x;

    for (size_t i = 0; i < this->weights.size(); i++) {
        D_MATRIX w = this->weights[i];
        Layer layer = this->layers[i + 1];

        output = layer.calc(output, w);
    }

    return output;
}

void Model::addLayer(Layer layer) {
    this->layers.push_back(layer);
}

