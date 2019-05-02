#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <png.h>
#include <zlib.h>

#include "matrix.h"
#include "network.h"

struct Frame {
    /**
     * Matrix of pixels contained in the frame.
     */
    matrix data;

    /**
     * The Frame struct constructor.
     *
     * @param  h  Frame height
     * @param  w  Frame width
     */
    Frame(std::size_t h, std::size_t w);

    /**
     * Spreads the matrix of pixels in rows into a vector.
     *
     * @return  Vector of pixels
     */
    vector toVector();

    /**
     * Update frame data by input vector.
     */
    void fromVector(const vector &v);

    /**
     * Returns frame width.
     *
     * @return  The frame width
     */
    std::size_t width() const;

    /**
     * Returns frame height.
     *
     * @return  The frame height
     */
    std::size_t height() const;
};

typedef std::vector<Frame> Series;          // vector of frames
typedef std::vector<Series> Dataframe;      // matrix of frames

/**
 * Convert Dataframe to Dataset.
 *
 * @param   df  Input dataframe
 * @return      Output dataset
 */
Dataset convert(const Dataframe &df);

class Png {
protected:
    /**
     * This structure provided info about the PNG file.
     */
    png_infop info;

    /**
     * The image data.
     * It is an array of pointers to the pixel data for each row.
     */
    unsigned char ** data;

    /**
     * The image width.
     * Specifies the number of pixels by image height.
     */
    unsigned int width;

    /**
     * The image height.
     * Specifies the number of pixels to the width of the image.
     */
    unsigned int height;

    /**
     * The image color depth.
     * Also known as bit depth, is either the number of bits used
     * to indicate the color of a single pixel, or the number of
     * bits used for each color component of a single pixel.
     */
    int colorDepth;

    /**
     * The image color type.
     * Color type is a single-byte integer that describes
     * the interpretation of the image data.
     */
    int colorType;

    /**
     * The image interlace method.
     * Interlacing is a method of encoding a bitmap image such
     * that a person who has partially received it sees a
     * degraded copy of the entire image.
     */
    int interlaceMethod;

    /**
     * The image filter method.
     * It's a technique through which size, colors, shading and other
     * characteristics of an image are altered. Used to transform
     * the image using different graphical editing techniques.
     */
    int filterMethod;

    /**
     * The image compression method.
     */
    int compressionMethod;

    /**
     * Read image from file.
     *
     * @param  filename  The image file name
     * @return           FILE pointer
     */
    FILE * read(const std::string &filename);

    /**
     * Initializes the properties of the image.
     */
    void init(png_structp, png_infop);
public:
    /**
     * The image constructor.
     *
     * @param  filename  Name of image file
     */
    explicit Png(const std::string &filename);

    /**
     * Saves the image by the specified file name.
     * 
     * @param  filename  Output file name of image
     */
    void dump(const std::string &filename);

    /**
     * Splits image into frame matrix (dataframe).
     *
     * @param   frameWidth    A frame width
     * @param   frameHeight   A frame height
     * @return                Matrix of frames
     */
    Dataframe split(unsigned int frameWidth, unsigned int frameHeight);

    /**
     * Assembly the image from matrix of frames (dataframe).
     *
     * @param  dataframe  Matrix of frames
     */
    void assemble(const Dataframe &dataframe);

    /**
     * Generate testing dataset.
     *
     * @param   size   Size of dataset
     * @param   ySize  Output vector size
     * @return         Testing dataset
     */
    Dataset makeTestingSet(std::size_t size, std::size_t ySize);
};

#endif
