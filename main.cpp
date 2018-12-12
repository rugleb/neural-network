#include "src/Model.h"
#include "src/Image.h"

#define  FRAME_W     2
#define  FRAME_H     2
#define  L           4

int main()
{
    Image img("exam.png");
    Dataset dataset;

    TrainParams params;
    params.dataset = dataset;
    params.epochs = 15;
    params.teach = 0.05;

    auto outputSize = params.dataset.front().y.size();

    Model model;

    model.add(Layer(L, linear));                    // define hidden layer
    model.add(Layer(outputSize, linear));           // define output layer

    model.fit(params);

    vector expected = rand(outputSize, 0, 255);
    vector actual = model.predict(expected);

    std::cout << "Testing error: " << relative(expected, actual) << std::endl;

    auto df = img.split(FRAME_W, FRAME_H);

    img.dump("new.png");

    return 0;
}
