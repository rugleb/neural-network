#include "src/Model.h"

std::vector<data> generate(unsigned int size)
{
    std::vector<data> dataset(size);

    for (unsigned int i = 0; i < size; i++) {
        data set;

        set.x = { (double) i / size};
        set.y = { (double) i * 2 / size };

        dataset[i] = set;
    }

    return dataset;
}

int main()
{
    std::vector<data> dataset = generate((unsigned int) 1e+5);

    Model model;

    model.add(Layer(3, relu));      // hidden layer
    model.add(Layer(1, relu));      // output layer

    model.fit(dataset, 200, 1e-5);

    return 0;
}
