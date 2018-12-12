#include "src/Model.h"
#include "src/Image.h"

#define  FRAME_W     2
#define  FRAME_H     2
#define  L           4

Dataset toDataset(const Dataframe &df)
{
    Dataset dataset;
    for (const Series &series : df) {
        for (Frame frame : series) {

            vector values;
            for (double pixel : frame.toVector()) {
                values.push_back(pixel / 255);
            }

            dataset.push_back({values, values});
        }
    }

    return dataset;
}

int main(int argc, char **argv)
{
    Image img("exam.png");
    Dataframe df = img.split(FRAME_W, FRAME_H);

    Dataset dataset = toDataset(df);

    TrainParams params;
    params.dataset = dataset;
    params.epochs = 15;
    params.teach = 0.05;

    auto outputSize = params.dataset.front().y.size();

    Model model;

    model.add(Layer(L, linear));                    // define hidden layer
    model.add(Layer(outputSize, linear));           // define output layer

    model.fit(params);

    Dataset testingSet;
    for (auto i = 0; i < 5; i++) {
        vector pixels = rand(outputSize, 0, 255);
        testingSet.push_back({pixels, pixels});
    }

    model.testing(testingSet);

    for (Series &series : df) {
        for (Frame &frame : series) {
            vector output = model.predict(frame.toVector());

            for (auto i = 0; i < frame.height(); i++) {
                for (auto j = 0; j < frame.width(); j++) {
                    auto pixel = output[i * frame.width() + j];
                    frame.pixels[i][j] = pixel;
                }
            }
        }
    }

    img.assemble(df);
    img.dump(argc > 1 ? argv[1] : "result.png");

    return 0;
}
