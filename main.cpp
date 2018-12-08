#include "src/Model.h"

#define PI 3.14

Dataset generate(unsigned int size)
{
    Dataset dataset(size);

    for (auto i = 0; i < size; i++) {
        Data sample;
        double x = rand(-PI, PI);

        sample.x = { x };
        sample.y = { sin(x) };

        dataset[i] = sample;
    }

    return dataset;
}

int main()
{
    TrainParams params;
    params.dataset = generate(1000);

    Model model;

    model.add(Layer(20, tanh));
    model.add(Layer(20, tanh));
    model.add(Layer(params.dataset.back().y.size(), linear));

    model.fit(params);

    Data testing;
    testing.x = { PI / 6. };
    testing.y = { .5 };

    vector actual = model.predict(testing.x);

    std::cout << std::endl;
    std::cout << "Testing results: " << std::endl;
    std::cout << "---- Received: " << actual.front() << std::endl;
    std::cout << "---- Expected: " << testing.y.front() << std::endl;
    std::cout << "---- Testing error: " << relative(testing.y, actual) << std::endl;

    return 0;
}
