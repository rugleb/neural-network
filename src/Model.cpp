#include "Model.h"

Data::Data()
{
    x = {};
    y = {};
}

Data::Data(const vector &_x, const vector &_y)
{
    x = _x;
    y = _y;
};

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
    init(params);

    std::cout << "Training started" << std::endl;
    for (auto epoch = 0; epoch < params.epochs; epoch++) {

        std::double_t error = 0;
        shuffle(params.dataset);

        for (const Data &sample : params.dataset) {

            tensor y = feedforward(sample.x);
            error += relative(T(sample.y), y.back());

            matrix e = y.back() - T(sample.y);
            tensor sigma = backward(e, y);

            corrective(sigma, y, params.teach);
        }

        error /= params.dataset.size();

        std::cout << "---- Epoch: " << epoch + 1 << ", error: " << error << std::endl;

        if (error < params.error) {
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

tensor Model::feedforward(const vector &x)
{
    auto size = layers.size() + 1;
    tensor y(size);

    y[0] = T(x);
    for (auto i = 1; i < size; i++) {
        y[i] = layers[i - 1].activate(y[i - 1]);
    }

    return y;
}

tensor Model::backward(matrix e, const tensor &y)
{
    auto size = layers.size() + 1;
    tensor sigma(size);

    for (auto i = size - 1; i >= 1; i--) {
        sigma[i] = e ^ layers[i - 1].activate(y[i - 1], true);
        e = T(layers[i - 1].w) * sigma[i];
    }

    return sigma;
}

void Model::corrective(const tensor &sigma, const tensor &y, double teach)
{
    auto size = layers.size() + 1;

    for (auto i = 1; i < size; i++) {
        matrix gradient = sigma[i] * T(y[i - 1]);
        layers[i - 1].w = layers[i - 1].w - gradient * teach;
    }
}


vector Model::predict(const vector &x)
{
    matrix y = feedforward(x).back();

    return T(y).front();
}

double Model::testing(const Dataset &dataset)
{
    auto size = dataset.size();            // dataset size
    auto total = 0.;                       // average dataset error

    std::cout << "Testing started" << std::endl;

    for (auto i = 0; i < size; i++) {
        Data set = dataset[i];
        vector output = predict(set.x);

        double err = relative(set.y, output);
        total += err;

        std::cout << "---- Set " << i + 1 << ", error: " << err << std::endl;
    }

    total /= size;
    std::cout << "Testing finished. Total error: " << total << std::endl;

    return total;
}
