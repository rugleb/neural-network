#ifndef NETWORK_H
#define NETWORK_H

#define SQUARE(x) ((x) * (x))

#include <cstdio>
#include <vector>
#include <random>
#include <algorithm>

#include "matrix.h"

/**
 * List of neuron activation functions.
 *
 * @param   x           Input value
 * @param   derivative  Use first derivative or not
 * @return              Activation output value
 */
double relu (double x, bool derivative = false);
double linear (double x, bool derivative = false);
double sigmoid (double x, bool derivative = false);

/**
 * Applies an activation function to all elements in a vector (matrix).
 *
 * @param   x           Input value
 * @param   activation  Activation function
 * @param   derivative  Use first derivative or not
 * @return              Activation output vector (matrix)
 */
vector apply(const vector &x, callable activation, bool derivative = false);
matrix apply(const matrix &x, callable activation, bool derivative = false);

/**
 * Returns MSE error value.
 *
 * @param   expected  Expected value
 * @param   actual    Received (actual) value
 * @return            MSE error
 */
double MSE (const vector &expected, const vector &actual);
double MSE (const matrix &expected, const matrix &actual);

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

struct Data {
    vector x;        // Neural network input values vector
    vector y;        // Expected output values vector

    Data();
    Data(const vector &x, const vector &y);
};

typedef std::vector<Data> Dataset;

template <typename T>
void shuffle(std::vector<T>);

/**
 * The structure is designed to store
 * parameters of the training model.
 */
struct TrainParams {
    Dataset dataset = {};                  // Model training set
    std::double_t error = 1e-2;            // Acceptable (stop) error
    std::double_t teach = 1e-4;            // Teaching coefficient
    std::size_t epochs = 200;              // Maximum number of learning epochs
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
     * The forward pass propagation.
     *
     * @return  Output matrices vector (tensor)
     */
    tensor feedforward(const vector &x);

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
    void fit(const TrainParams& params);

    /**
     * Makes prediction based on learning.
     *
     * @param  params  Input values vector
     * @return         Prediction result vector
     */
    vector predict(const vector &x);

    /**
     * Checks the quality of network training on a test sample.
     *
     * @param  dataset  Testing dataset
     * @return          Average dataset error
     */
    std::double_t testing(const Dataset &dataset);
};

#endif
