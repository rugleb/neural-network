#include "src/Model.h"

int main()
{
    std::vector<data> dataset = {};

    Model model;

    model.add(Layer(3, linear));
    model.add(Layer(2, relu));

    model.fit(dataset, 1e-5, 5);

    return 0;
}
