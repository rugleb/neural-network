#include "Model.h"

void Model::add(Layer layer) {
    layers.push_back(layer);
}

void Model::fit(dataset dataset, std::size_t epochs, double precision) {

    for (std::size_t epoch = 0; epoch < epochs; epoch++) {

        double error = .0;

        for (set &set : dataset) {

        }

        if (error < precision) {
            break;
        }
    }

}
