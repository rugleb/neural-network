#ifndef NEURAL_NETWORK_IMAGE_H
#define NEURAL_NETWORK_IMAGE_H

#include <iostream>
#include <string>
#include <png.h>

#include "support/math.h"

class Image {
protected:
    png_infop info = nullptr;
    png_structp reader = nullptr;

    png_bytep * pointers;

    unsigned int width;
    unsigned int height;
    unsigned char bitDepth;
    unsigned char colorType;

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

};


#endif
