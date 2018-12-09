#include "Model.h"

template <typename T>
void shuffle(std::vector<T> vector)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::shuffle(vector.begin(), vector.end(), generator);
}

Layer::Layer(std::size_t dimension, callable function)
{
    activation = function;
    dim = dimension;
    w = {};
}

matrix Layer::activate(const matrix &x, bool derivative)
{
    return apply(w * x, activation, derivative);
}

Model::Model()
{
    layers = {};
}

void Model::add(Layer layer)
{
    layers.push_back(layer);
}

void Model::fit(TrainParams params)
{
    // The number of layers during training
    // is considered from the input layer
    auto size = layers.size() + 1;
    std::double_t acc;

    tensor y(size);
    tensor sigma(size);

    init(params);

    std::cout << "Training started" << std::endl;
    for (auto epoch = 0; epoch < params.epochs; epoch++) {

        acc = 0.;
        shuffle(params.dataset);

        for (const Data &sample : params.dataset) {

            y[0] = T(sample.x);
            for (auto i = 1; i < size; i++) {
                y[i] = layers[i - 1].activate(y[i - 1]);
            }

            acc += relative(T(sample.y), y.back());

            matrix e = y.back() - T(sample.y);
            for (auto i = size - 1; i >= 1; i--) {
                sigma[i] = e ^ layers[i - 1].activate(y[i - 1], true);
                e = T(layers[i - 1].w) * sigma[i];
            }

            for (auto i = 1; i < size; i++) {
                matrix gradient = sigma[i] * T(y[i - 1]);
                layers[i - 1].w = layers[i - 1].w - gradient * params.teach;
            }
        }

        acc /= params.dataset.size();

        std::cout << "---- Epoch: " << epoch + 1 << ", acc: " << acc << std::endl;

        if (acc < params.accuracy) {
            break;
        }
    }

    std::cout << "Training finished" << std::endl;
}

void Model::init(TrainParams params)
{
    // The number of rows of the matrix is equal to
    // the dimension of the input vector (layer)
    auto cols = params.dataset.front().x.size();

    for (auto &layer : layers) {
        // The number of columns of the matrix is equal to
        // the dimension of the output vector (layer)
        auto rows = layer.dim;
        layer.w = rand(rows, cols, -1., 1.);

        cols = rows;
    }
}

vector Model::predict(const vector &sample)
{
    matrix y = T(sample);

    for (Layer &layer : layers) {
        y = layer.activate(y);
    }

    return T(y).front();
}
