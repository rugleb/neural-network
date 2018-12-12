#include "src/Model.h"
#include "src/Image.h"

#define  FRAME_W     2
#define  FRAME_H     2
#define  L           4

struct Frame {
    std::size_t width;
    std::size_t height;

    explicit Frame(std::size_t w, std::size_t h) {
        width = w;
        height = h;
    }
};

Dataset split(Frame frame, Image img)
{
    Dataset dataset;
    matrix pixels = img.getMatrix();

    for (auto i = 0; i < img.getWidth(); i += frame.width) {
        for (auto j = 0; j < img.getHeight(); j += frame.height) {
            vector v;
            for (auto ii = 0; ii < frame.width; ii++) {
                for (auto jj = 0; jj < frame.height; jj++) {
                    v.push_back(pixels[i + ii][j + jj] / 255);
                }
            }
            dataset.push_back({v, v});
        }
    }

    return dataset;
}

int main()
{
    Image img("exam.png");
    TrainParams params;

    params.dataset = split(Frame(FRAME_W, FRAME_H), img);
    params.epochs = 15;
    params.teach = 0.05;

    auto outputSize = params.dataset.front().y.size();

    Model model;

    model.add(Layer(L, linear));
    model.add(Layer(outputSize, linear));

    model.fit(params);

    vector expected = rand(outputSize, 0, 255);
    vector actual = model.predict(expected);

    std::cout << "Testing error: " << relative(expected, actual) << std::endl;

    auto df = img.split(FRAME_W, FRAME_H);

    for (Serial &serial : df) {
        for (Partial &partial : serial) {
            vector x = partial.toVector();
            tensor y = model.feedforward(x);
            vector result = vectorize(y[1]);

            matrix m(FRAME_H, vector(FRAME_W));
            for (auto i = 0; i < FRAME_H; i++) {
                for (auto j = 0; j < FRAME_W; j++) {
                    auto n = i * FRAME_W + j;
                    m[i][j] = result[n];
                }
            }

            partial.pixels = m;
        }
    }

    Partial partial = df.front().front();

    auto height = df.size() * partial.height();
    auto width = df.front().size() * partial.width();

    matrix pixels(height, vector(width));

    for (auto i = 0; i < df.size(); i++) {
        for (auto j = 0; j < df[i].size(); j++) {

            for (auto ii = 0; ii < partial.height(); ii++) {
                for (auto jj = 0; jj < partial.width(); jj++) {
                    pixels[i * partial.height() + ii][j * partial.width() + jj] = df[i][j].pixels[ii][jj];
                }
            }
        }
    }

    img.setPointers(pixels);

    img.dump("new.png");

    return 0;
}
