#include "Training.h"

Training::Training(Model * model)
{
    this->model = model;
    this->layers = std::vector<layer>(this->model->getLayers().size());
}

float Training::getTime()
{
    return this->time;
}

double Training::getAcc()
{
    return this->accuracy;
}

std::size_t Training::getEpochs()
{
    return this->epochs;
}

void Training::run(std::size_t maxEpochs, double acc, std::vector<data> dataset)
{
    this->compile(dataset);

    clock_t time = clock();

    this->accuracy = .0;
    for (this->epochs = 0; this->epochs < maxEpochs; this->epochs++) {

        std::random_shuffle(std::begin(dataset), std::end(dataset));

        for (data &set : dataset) {
            matrix e = this->feedforward(set);
            this->backPropagation(e);

            e = this->feedforward(set);
            this->accuracy += MSE(e);
        }

        this->accuracy /= dataset.size();

        if (this->accuracy < acc) {
            break;
        }
    }

    this->time = (float) 1e+3 * (clock() - time) / CLOCKS_PER_SEC;
}

matrix Training::feedforward(data set)
{
    matrix y = transpose(set.x);

    for (layer &l : this->layers) {
        matrix v = l.weights * y;

        l.x = y;
        l.derivative = derivative(v, l.activation);

        y = activate(v, l.activation);
        l.y = y;
    }

    return transpose(set.y) - y;
}

void Training::backPropagation(matrix e)
{
    for (int i = (int) this->layers.size() - 1; i >= 0; i--) {
        layer * layer = &this->layers[i];

        matrix localGradient = e ^ layer->derivative;

        matrix dw = localGradient * transpose(layer->x) * this->teach;
        layer->weights = layer->weights + dw;

        e = transpose(layer->weights) * localGradient;
    }
}

void Training::compile(const std::vector<data> &dataset)
{
    std::vector<Layer> layers = this->model->getLayers();
    auto inputSize = (unsigned int) dataset.front().x.size();

    for (std::size_t i = 0; i < layers.size(); i++) {
        unsigned int outputSize = layers[i].getUnits();

        this->layers[i].weights = rand(outputSize, inputSize, -0.1, 1.0);
        this->layers[i].activation = layers[i].getActivation();

        inputSize = outputSize;
    }
}
