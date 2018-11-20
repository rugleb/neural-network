#include <iostream>

#include "src/Model.h"
#include "src/support.h"

#define DATASET std::vector<Set>

DATASET generate(unsigned int count) {
    DATASET dataset(count);

    for (size_t i = 0; i < count; i++) {
        D_VECTOR x = {0., 1., 2.};
        D_VECTOR y = {0., 1., 2.};

        Set set = {x, y};
        dataset[i] = set;
    }

    return dataset;
}

int main() {

    Neuron neuron;
    Layer layer(neuron, 2);

    Model model;
    model.addLayer(layer);

    DATASET dataset = generate(2);
    model.train(dataset, 1e-3);

    return 0;
}
