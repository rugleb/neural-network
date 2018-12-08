#include "Model.h"

void Model::add(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::fit(const dataset &data, double acc, std::size_t epochs)
{
    Training train(this);

    train.compile();
    train.run(data, acc, epochs);
}

void Model::predict(const vector &x)
{
    matrix input = T(x);
}

Training::Training(Model *model)
{
    this->model = model;
}

void Training::compile()
{
    //
}

void Training::run(dataset dataset, double accuracy, std::size_t maxEpochs)
{
    double acc = 0;
    std::size_t epoch = 0;

    std::cout << "Training started" << std::endl;

    while (epoch < maxEpochs) {
        acc = 0;

        for (auto &set : dataset) {
            matrix e = this->feedforward(set);
            this->backPropagation(e);
        }

        acc /= dataset.size();
        epoch++;

        std::cout << "---- Epoch: " << epoch << ", acc: " << acc << std::endl;

        if (acc < accuracy) {
            break;
        }
    }

    std::cout << "Training finished" << std::endl;
}
