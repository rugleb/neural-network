#include "src/Model.h"

std::vector<data> generate(unsigned int size)
{
    std::vector<data> dataset(size);

    for (unsigned int i = 0; i < size; i++) {
        data set;

        set.x = { .0, .1, .2 };
        set.y = { (double) i };

        dataset[i] = set;
    }

    return dataset;
}

int main()
{
    Model model;

    model.add(Layer(10, linear));
    model.add(Layer(5, relu));

    std::vector<data> dataset = generate((unsigned int) 1e+6);
    model.fit(dataset, 20, 1e-5);

    return 0;
}
