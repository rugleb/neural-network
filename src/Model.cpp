#include "Model.h"

void Model::add(Layer layer)
{
    this->layers.push_back(layer);
}

void Model::fit(dataset trains, double acc, std::size_t epochs)
{
    
}
