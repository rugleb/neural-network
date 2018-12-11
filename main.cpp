#include "src/Model.h"
#include "src/Image.h"

#define  FRAME_W     4
#define  FRAME_H     4
#define  L_X         2
#define  L_Y         2

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

    Model model;

    model.add(Layer(L_X * L_Y, linear));
    model.add(Layer(params.dataset.back().y.size(), linear));

    model.fit(params);

//    vector expected = { 141, 130, 137, 122 };
//    vector actual = model.predict(expected);

//    std::cout << "Testing error: " << relative(expected, actual) << std::endl;

    auto df = img.split(FRAME_W, FRAME_H);

    for (Serial &serial : df) {
        for (Partial &partial : serial) {
            vector x = partial.toVector();
            tensor y = model.feedforward(x);
            vector result = vectorize(y[1]);

            matrix m(L_Y, vector(L_X));
            for (auto i = 0; i < L_Y; i++) {
                for (auto j = 0; j < L_X; j++) {
                    auto n = i * L_X + j;
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

    img.setWidth(width);
    img.setHeight(height);
    img.setPointers(pixels);

    img.dump("new.png");

    return 0;
}
