#include "Model.h"

void Model::add(Layer layer) {
    layers.push_back(layer);
}

void Model::fit(dataset dataset, std::size_t epochs, double precision) {

    for (std::size_t epoch = 0; epoch < epochs; epoch++) {

        double error = .0;

        for (set &set : dataset) {
            double2 e = feedforward(set);
            error += MSE(e);
        }

        if (error / dataset.size() < precision) {
            break;
        }
    }

}

double2 Model::feedforward(set data) {

    double2 y;

    return data.Y - y;
}

double MSE(double2 e) {

    std::size_t size = e.size();
    double y = .0;

    for (int i = 0; i < size; ++i) {
        y += SQUARE(e[i]);
    }

    return y / size;
}
