#include "src/Model.h"

int main()
{
    Model model;

    model.add(Layer(10, linear));
    model.add(Layer(5, relu));

    return 0;
}
