#include "src/Model.h"

std::vector<data> generate(unsigned int size)
{
    std::vector<data> dataset(size);

    for (auto i = 0; i < size; i++) {
        data sample;
        double x = rand(-3.14, 3.14);

        sample.x = { x };
        sample.y = { sin(x) };

        dataset[i] = sample;
    }

    return dataset;
}

int main()
{
    std::vector<data> dataset = generate(1000);

    Model model;

    model.add(Layer(20, tanh));
    model.add(Layer(20, tanh));
    model.add(Layer(dataset.back().y.size(), linear));

    model.fit(dataset, 1e-2, 50);

    data testing = {{ 3.14 / 6 }, { .5 }};
    vector actual = model.predict(testing.x);

    std::cout << "Testing accuracy: " << relative(testing.y, actual) << std::endl;

    return 0;
}
