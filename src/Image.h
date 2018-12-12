#ifndef NEURAL_NETWORK_IMAGE_H
#define NEURAL_NETWORK_IMAGE_H

#include <iostream>
#include <string>
#include <png.h>

#include "support/math.h"

struct Partial {
    matrix pixels;

    std::size_t width() {
        return pixels.front().size();
    }

    std::size_t height() {
        return pixels.size();
    }

    vector toVector() {
        return vectorize(pixels);
    }
};

typedef std::vector<Partial> Serial;
typedef std::vector<Serial> Dataframe;

class Image {
protected:
    png_infop info = nullptr;
    png_structp reader = nullptr;

    png_bytep * pointers;

    unsigned int width;
    unsigned int height;
    unsigned char bitDepth;
    unsigned char colorType;
    unsigned char interlace;
    unsigned char filterType;
    unsigned char compression;

    FILE * readFile(const std::string &filename);
    void validate(FILE * f);

    png_structp makeReadStruct();
    png_structp makeWriteStruct();
    png_infop makeInfoStruct(png_structp);

    void init(png_structp, png_infop);
    void setWidth(png_structp, png_infop);
    void setHeight(png_structp, png_infop);
    void setBitDepth(png_structp, png_infop);
    void setColorType(png_structp, png_infop);
    void setPointers(png_structp, png_infop);
public:
    explicit Image(const std::string &filename);
    void dump(const std::string &filename);

    matrix getMatrix();
    unsigned int getHeight();
    unsigned int getWidth();

    void setPointers(const matrix &m);

    Dataframe split(std::size_t Nx, std::size_t Ny)
    {
        auto nFramesX = width / Nx;
        auto nFramesY = height / Ny;

        Dataframe df(nFramesY, Serial(nFramesY));

        for (std::size_t nY = 0; nY < nFramesY; nY++) {
            for (std::size_t nX = 0; nX < nFramesX; nX++) {

                df[nX][nY].pixels = matrix(Ny, vector(Nx));

                for (std::size_t i = 0; i < Nx; i++) {
                    for (std::size_t j = 0; j < Ny; j++) {

                        auto pixel = (double) pointers[nX * Nx + i][nY * Ny + j];
                        df[nX][nY].pixels[i][j] = pixel;
                    }
                }
            }
        }

        return df;
    }
};


#endif
