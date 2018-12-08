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

    trainParams params = {              // enabling training params
        .dataset = dataset,             // training dataset
        .accuracy = 1e-2,               // stop accuracy value
        .teach = 1e-4,                  // teaching coefficient
        .epochs = 100                   // max epochs number
    };

    model.fit(params);

    data testing = {{ 3.14 / 6 }, { .5 }};
    vector actual = model.predict(testing.x);

    std::cout << "Testing accuracy: " << relative(testing.y, actual) << std::endl;

    return 0;
}
