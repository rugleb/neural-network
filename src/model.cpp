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
}

void Model::addLayer(Layer layer) {
    this->layers.push_back(layer);
}

