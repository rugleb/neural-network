#include "Model.h"

void Model::add(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::fit(std::vector<data> dataset, double accuracy, std::size_t epochs)
{
    auto size = layers.size() + 1;

    double acc = 0.;
    double teach = 1e-4;

    std::vector<matrix> w (size);
    std::vector<matrix> y (size);
    std::vector<matrix> sigma (size);

    auto ySize = dataset.front().x.size();

    for (auto i = 1; i < size; i++) {
        auto xSize = layers[i - 1].getNeurons();
        w[i] = rand(xSize, ySize, -1., 1.);
        ySize = xSize;
    }

    std::cout << "Training started" << std::endl;
    for (auto epoch = 0; epoch < epochs; epoch++) {

        acc = 0.;
        shuffle(dataset);

        for (const data &sample : dataset) {

            y[0] = T(sample.x);
            for (auto i = 1; i < size; i++) {
                y[i] = layers[i - 1].activate(w[i] * y[i - 1]);
            }

            acc += relative(y.back(), T(sample.y));

            matrix e = y.back() - T(sample.y);
            for (auto i = size - 1; i >= 1; i--) {
                sigma[i] = e ^ layers[i - 1].activate(w[i] * y[i - 1], true);
                e = T(w[i]) * sigma[i];
            }

            for (auto i = 1; i < size; i++) {
                matrix gradient = sigma[i] * T(y[i - 1]);
                w[i] = w[i] - gradient * teach;
            }
        }

        acc /= dataset.size();

        std::cout << "---- Epoch: " << epoch + 1 << ", acc: " << acc << std::endl;

        if (acc < accuracy) {
            break;
        }
    }

    std::cout << "Training finished" << std::endl;
}

void shuffle(std::vector<data> dataset)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::shuffle(dataset.begin(), dataset.end(), generator);
}
