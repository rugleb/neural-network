#include "src/Model.h"
#include "src/Image.h"

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

    params.dataset = split(Frame(2, 2), img);
    params.epochs = 50;
    params.teach = 0.05;

    Model model;

    model.add(Layer(4, linear));
    model.add(Layer(params.dataset.back().y.size(), linear));

    model.fit(params);

    Data testing;
    testing.x = { 141, 130, 137, 122 };
    testing.y = { 141, 130, 137, 122 };

    vector actual = model.predict(testing.x);

    std::cout << std::endl;
    std::cout << "Testing error: " << relative(testing.y, actual) << std::endl;

    return 0;
}
