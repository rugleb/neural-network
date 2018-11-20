#include <iostream>

#include "src/Model.h"
#include "src/Support.h"

#define DATASET std::vector<Set>


DATASET generate(unsigned int count)
{
    DATASET dataset(count);

    for (size_t i = 0; i < count; i++) {
        D_VECTOR x = {0., 1., 2.};
        D_VECTOR y = {0., 1., 2.};

        Set set = {x, y};
        dataset[i] = set;
    }

    return dataset;
}

int main()
{
    Layer layer(Neuron(), 2);

    Model model;
    model.addLayer(layer);

    DATASET dataset = generate(1000);
    model.train(dataset, 1e-3);

    return 0;
}
