#include "src/Model.h"

int main()
{
    dataset data = {};

    Model model;

    model.add(Layer(3, linear));
    model.add(Layer(2, relu));

    model.fit(data, 1e-5, 5);

    return 0;
}
