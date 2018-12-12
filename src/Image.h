#ifndef NEURAL_NETWORK_IMAGE_H
#define NEURAL_NETWORK_IMAGE_H

#include <iostream>
#include <string>
#include <png.h>

#include "support/math.h"

struct Frame {
    /**
     * Matrix of pixels contained in the frame.
     */
    matrix pixels;

    /**
     * The Frame struct constructor.
     *
     * @param  h  Frame height
     * @param  w  Frame width
     */
    Frame(unsigned int h, unsigned int w);

    /**
     * Spreads the matrix of pixels in rows into a vector.
     *
     * @return  Vector of pixels
     */
    vector toVector();

    /**
     * Returns frame width.
     *
     * @return  The frame width
     */
    std::size_t width();

    /**
     * Returns frame height.
     *
     * @return  The frame height
     */
    std::size_t height();
};

typedef std::vector<Frame> Series;
typedef std::vector<Series> Dataframe;

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

    Dataframe split(unsigned int frameWidth, unsigned int frameHeight);
};


#endif
