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

/**
 * The structure is designed to store
 * parameters of the training model.
 */
struct TrainParams {
    std::vector<Data> dataset = {};        // Model training set
    std::double_t accuracy = 1e-2;         // Acceptable (stop) accuracy
    std::double_t teach = 1e-4;            // Teaching coefficient
    std::size_t epochs = 200;              // Maximum number of learning epochs
};

struct Layer {
    /**
     * Weights matrix of this layer.
     *
     * Not recommended to change
     * weights outside the application.
     */
    matrix w;

    /**
     * The number of neurons in this layer.
     */
    std::size_t dim;

    /**
     * Activation function:
     * one for all neurons of this layer.
     */
    callable activation;

    /**
     * The Layer class constructor.
     *
     * @param  dimension   Neurons number in the layer
     * @param  activation  Neuron activation function
     */
    Layer(std::size_t dimension, callable activation);

    /**
     * Passes the input value vector through the layer
     * and returns the activated weighted sum.
     *
     * @param   x           Input values vector
     * @param   derivative  Use derivative or not flag
     * @return  y           Output values vector
     */
    matrix activate(const matrix &x, bool derivative = false);

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
};

class Model {
protected:
    /**
     * List of layers of this model.
     */
    std::vector<Layer> layers;

    /**
     * Initializes the model parameters
     * and values of its layers.
     *
     * @param  params  Training parameters
     */
    void init(TrainParams params);

public:
    /**
     * The model constructor.
     */
    explicit Model();

    /**
     * Adds a new layer to the model.
     *
     * @param  layer  New layer
     */
    void add(Layer layer);

    /**
     * Starts the model training process.
     *
     * @param  params  Training params list
     */
    void fit(TrainParams params);

    /**
     * Makes prediction based on learning.
     *
     * @param  params  Input values vector
     * @return         Prediction result vector
     */
    vector predict(const vector &x);
};

template <typename T>
void shuffle(std::vector<T>);

#endif
