#include <iostream>

#include "src/model.h"
#include "src/support.h"

int main() {

    Neuron neuron;
    Layer layer(neuron, 3);

    Model model;
    model.addLayer(layer);
    
    return 0;
}
