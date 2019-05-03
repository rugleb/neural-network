[![Build Status](https://travis-ci.com/rugleb/neural-network.svg?branch=master)](https://travis-ci.com/rugleb/neural-network)
[![Language](https://img.shields.io/badge/Lang-C++11-green.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Preview

This repository is created for educational purposes only and is not ready for use in production.

The developed interface for working with neural networks is largely inspired by the [Keras](https://keras.io) framework.

# Getting started

The central data structure of this library is the model.
It defines the structure of the layers and the relationship between them.

At the moment, only a Sequential network model is implemented.

Now create an instance of the new network model:

```C++
#include "src/network.h"

Model model();
```

Then add two hidden layers with different activation functions and neurons number:

```C++
model.add(Layer(20, relu));         // 20 neurons and ReLU activation
model.add(Layer(10, sigmoid));      // 10 neurons and Sigmoid activation
```

> Note that the model automatically selects the number of neurons on the input layer of the network.

Now the structure of the neural network is ready.

The next step is to train the neural network.
But before you train a model, you must set the training parameters.
This is done quite simply:

```C++
TrainParams params;
params.dataset = dataset;           // train dataset
params.epochs = 5;                  // number of training epochs
params.error = 1e-10;               // acceptable learning error
params.teach = 0.05;                // learning rate
```

Under dataset should be understood as a set (vector) of data in the format:
vector of input values of the network and a vector of output values of the network. 
More detailed: [Dataset structure](https://github.com/rugleb/neural-network/blob/b5dbe3ab3a37ac44db6a1044407c7903d623bdb0/src/network.h#L92).

Now that we are ready to train the network, we can start the learning process:

```C++
model.fit(params);
```

During the training program will inform you:

```C++
Training started
---- Epoch: 1, average error: 5.74e-04
---- Epoch: 2, average error: 1.62e-05
---- Epoch: 3, average error: 8.75e-07
---- Epoch: 4, average error: 6.41e-08
---- Epoch: 5, average error: 2.32e-09
Training finished
```

After training the model, we can test the quality on the test data:

```C++
Dataset testing = makeTesting(3);    // creates 3 test datasets
model.testing(testingSet);           // starts testing
```

The output of the program:

```C++
Testing started
---- Testing set: 1, error: 1.12e-02
---- Testing set: 2, error: 1.65e-03
---- Testing set: 3, error: 4.36e-04
Testing finished. Average error: 4.43e-03
```

Now the model is trained and tested.
Then it can be saved and used for other tasks.

# Full example

You can see a complete example of a program that uses a neural network (autoencoder) to compress a PNG image
into a vector and then restores the image from the compressed vector to the original image: [main.cpp file](https://github.com/rugleb/neural-network/blob/master/main.cpp).

Build from sources:

```bash
./compile.sh
```

Run application:
```bash
./app.out example.png output.png
```
