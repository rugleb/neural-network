#include "src/Model.h"
#include "src/Image.h"

#define  FRAME_W     2
#define  FRAME_H     2
#define  L           4

int main(int argc, char **argv)
{
    std::string inputFile(argc > 1 ? argv[1] : "example.png");
    std::string outputFile(argc > 2 ? argv[2] : "output.png");

    Image img(inputFile);
    Dataframe df = img.split(FRAME_W, FRAME_H);

    Dataset dataset = convert(df);
    std::size_t outputSize = dataset.front().y.size();

    TrainParams params;
    params.dataset = dataset;
    params.epochs = 15;
    params.teach = 0.05;

    Model model;

    model.add(Layer(L, linear));                    // define hidden layer
    model.add(Layer(outputSize, linear));           // define output layer

    model.fit(params);

    Dataset testingSet = img.makeTestingSet(5, outputSize);
    model.testing(testingSet);

    for (Series &series : df) {
        for (Frame &frame : series) {
            auto output = model.predict(frame.toVector());
            frame.fromVector(output);
        }
    }

    img.assemble(df);
    img.dump(outputFile);

    return 0;
}
