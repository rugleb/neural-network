#include "src/Model.h"

dataset generate(unsigned int size)
{
    dataset data(size);

    for (unsigned int i = 0; i < size; i++) {
        set set;

        set.X = { .0, .1, .2 };
        set.Y = { (double) i };

        data[i] = set;
    }

    return data;
}

int main()
{
    Model model;

    model.add(Layer(10, linear));
    model.add(Layer(5, relu));

    dataset train = generate((unsigned int) 1e+6);
    model.fit(train, 20, 1e-5);

    return 0;
}
