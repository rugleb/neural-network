#include "src/Model.h"

int main()
{
    Model model;

    model.add(Layer(10, linear));
    model.add(Layer(5, relu));

    dataset train;
    model.fit(train, 20, 1e-5);

    return 0;
}
