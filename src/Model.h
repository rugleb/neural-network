#ifndef NEURAL_NETWORK_MODEL_H
#define NEURAL_NETWORK_MODEL_H

#include <vector>
#include <random>
#include <algorithm>

#include "support/math.h"

struct Data {
    vector x = {};
    vector y = {};

    Data() {
        x = {};
        y = {};
    };

    Data(const vector &_x, const vector &_y) {
        x = _x;
        y = _y;
    };
};

typedef std::vector<Data> Dataset;

template <typename T>
void shuffle(std::vector<T>);

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

    /**
     * The backward propagation.
     *
     * @param  e  Network error
     * @param  y  Output matrices vector (tensor)
     * @return    Matrices vector of gradients
     */
    tensor backward(matrix e, const tensor &y);

    /**
     * The weight corrective procedure.
     *
     * @param y
     * @param sigma
     */
    void corrective(const tensor &sigma, const tensor &y, double teach);

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
     * The forward pass propagation.
     *
     * @return  Output matrices vector (tensor)
     */
    tensor feedforward(const vector &x);

    /**
     * Makes prediction based on learning.
     *
     * @param  params  Input values vector
     * @return         Prediction result vector
     */
    vector predict(const vector &x);
};

#endif
