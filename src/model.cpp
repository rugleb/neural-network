#include <algorithm>

#include "model.h"

Model::Model() {

}

void Model::train(std::vector<Set> dataset, double error) {

    for (unsigned epoch = 0; epoch < 1e+2; epoch++) {
        double _error = 0.;

        std::shuffle(dataset.begin(), dataset.end(), std::rand);

        for (Set &set : dataset) {

        }

        if (_error < error) break;
    }

}

double Model::activate(double x) {
    return x;
}

D_VECTOR Model::activate(D_VECTOR x) {
    size_t size = x.size();
    D_VECTOR y(size);

    for (size_t i = 0; i < size; i++) {
        y[i] = activate(x[i]);
    }

    return y;
}
