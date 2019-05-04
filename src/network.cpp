#include "network.h"

double relu(double x, bool derivative)
{
    if (derivative) {
        return x > 0 ? 1. : 0.;
    }

    return x > 0 ? x : 0.;
}

double linear(double x, bool derivative)
{
    if (derivative) {
        return 1.;
    }

    return x;
}

double sigmoid(double x, bool derivative)
{
    double y = 1. / (1. + exp(-x));

    if (derivative) {
        return y * (1. - y);
    }

    return y;
}

vector apply(const vector &v, callable f, bool derivative)
{
    auto size = v.size();
    vector y(size);

    for (auto i = 0; i < size; i++) {
        y[i] = f(v[i], derivative);
    }

    return y;
}

matrix apply(const matrix &m, callable f, bool derivative)
{
    auto size = m.size();
    matrix y(size);

    for (auto i = 0; i < size; i++) {
        y[i] = apply(m[i], f, derivative);
    }

    return y;
}

double MSE(const vector &e, const vector &a)
{
    auto size = e.size();
    double y = 0.;

    for (auto i = 0; i < size; i++) {
        y += SQUARE(e[i] - a[i]) / 2;
    }

    return y / size;
}

double MSE(const matrix &e, const matrix &a)
{
    auto size = e.size();
    double y = 0.;

    for (auto i = 0; i < size; i++) {
        y += SQUARE(e[i][0] - a[i][0]) / 2;
    }

    return y / size;
}

Data::Data()
{
    x = {};
    y = {};
}

Data::Data(const vector &_x, const vector &_y)
{
    x = _x;
    y = _y;
}

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

void Model::fit(const TrainParams& params)
{
    init(params);

    puts("Training started");
    for (auto epoch = 0; epoch < params.epochs; epoch++) {

        std::double_t error = 0;
        shuffle(params.dataset);

        for (const Data &sample : params.dataset) {

            tensor y = feedforward(sample.x);
            error += MSE(y.back(), T(sample.y));

            matrix e = y.back() - T(sample.y);
            tensor sigma = backward(e, y);

            corrective(sigma, y, params.teach);
        }

        error /= params.dataset.size();

        printf("---- Epoch: %2d, average MSE error: %.2e\n", epoch + 1, error);

        if (error < params.error) {
            break;
        }
    }

    puts("Training finished");
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

void Model::corrective(const tensor &sigma, const tensor &y, std::double_t teach)
{
    auto size = layers.size() + 1;

    for (auto i = 1; i < size; i++) {
        matrix gradient = sigma[i] * T(y[i - 1]);
        layers[i - 1].w = layers[i - 1].w - gradient * teach;
    }
}

vector Model::predict(const vector &x)
{
    matrix out = feedforward(x).back();

    return T(out).front();
}

std::double_t Model::testing(const Dataset &dataset)
{
    std::size_t size = dataset.size();            // dataset size
    std::double_t total = 0.;                     // average dataset error

    puts("Testing started");

    for (auto i = 0; i < size; i++) {
        Data set = dataset[i];
        auto output = predict(set.x);

        std::double_t err = MSE(set.y, output);
        total += err;

        printf("---- Testing set: %2d, MSE error: %.2e\n", i + 1, err);
    }

    total /= size;
    printf("Testing finished. Average MSE error: %.2e\n", total);

    return total;
}
