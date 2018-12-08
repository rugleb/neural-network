#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>
#include <random>
#include <algorithm>

#include "support/math.h"

struct Data {
    vector x = {};
    vector y = {};
};

typedef std::vector<Data> Dataset;

struct TrainParams {
    std::vector<Data> dataset = {};
    std::double_t accuracy = 1e-2;
    std::double_t teach = 1e-4;
    std::size_t epochs = 200;
};

struct Layer {
    matrix w;
    std::size_t dim;
    callable activation;

    explicit Layer(std::size_t dimension, callable activation) {
        this->w = {};
        this->dim = dimension;
        this->activation = activation;
    }

    matrix apply(const matrix &x, bool derivative = false) {
        auto rows = x.size();
        auto cols = x.front().size();

        matrix y(rows);

        for (auto i = 0; i < rows; i++) {
            y[i] = vector(cols);
            for (auto j = 0; j < cols; j++) {
                y[i][j] = this->activation(x[i][j], derivative);
            }
        }

        return y;
    }

    matrix activate(const matrix &x, bool derivative = false)
    {
        matrix v = w * x;

        return apply(v, derivative);
    }
};

class Model {
protected:
    std::vector<Layer> layers;
    void init(TrainParams params);
public:
    void add(Layer layer);
    void fit(TrainParams params);
    vector predict(const vector &);
};

void shuffle(Dataset);

#endif
