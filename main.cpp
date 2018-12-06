#include "src/Model.h"

int main()
{
    Model model;

    model.add(Layer(3, linear));
    model.add(Layer(2, relu));

    return 0;
}
