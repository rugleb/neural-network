#include "Image.h"

#define PNG_BYTES_TO_CHECK 8

Frame::Frame(unsigned int h, unsigned int w)
{
    pixels = matrix(h, vector(w));
}

FILE * Image::readFile(const std::string &filename)
{
    FILE * f = fopen(filename.data(), "r");

    if (! f) {
        throw std::string("Can't read file: ") + filename;
    }

    return f;
}

void Image::validate(FILE * f)
{
    char header[PNG_BYTES_TO_CHECK];

    if (fread(header, 1, PNG_BYTES_TO_CHECK, f) != PNG_BYTES_TO_CHECK) {
        throw std::string("Can't read bytes from file");
    }

    if (png_sig_cmp((png_const_bytep) header, (png_size_t) 0, PNG_BYTES_TO_CHECK)) {
        throw std::string("File is not recognized as a PNG file");
    }
}

png_struct * Image::makeReadStruct()
{
    png_structp reader = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (! reader) {
        throw std::string("Can't create image reader struct");
    }

    return reader;
}

png_info * Image::makeInfoStruct(png_structp reader)
{
    png_infop info = png_create_info_struct(reader);

    if (! info) {
        throw std::string("Can't create image info struct");
    }

    return info;
}

void Image::init(png_structp png_reader, png_infop png_info)
{
    this->setColorType(png_reader, png_info);
    this->setBitDepth(png_reader, png_info);
    this->setPointers(png_reader, png_info);
    this->setHeight(png_reader, png_info);
    this->setWidth(png_reader, png_info);

    this->interlace = png_get_interlace_type(png_reader, png_info);
    this->compression = png_get_compression_type(png_reader, png_info);
    this->filterType = png_get_filter_type(png_reader, png_info);
}

void Image::setColorType(png_structp png_reader, png_infop png_info)
{
    unsigned char type = png_get_color_type(png_reader, png_info);

    if (type != 0) {
        throw std::string("Invalid color type: expected 0");
    }

    this->colorType = type;
}

void Image::setBitDepth(png_structp png_reader, png_infop png_info)
{
    unsigned char depth = png_get_bit_depth(png_reader, png_info);

    if (depth != 8) {
        throw std::string("Invalid color type: expected 0");
    }

    this->bitDepth = depth;
}

void Image::setHeight(png_structp png_reader, png_infop png_info)
{
    this->height = png_get_image_height(png_reader, png_info);
}

void Image::setWidth(png_structp png_reader, png_infop png_info)
{
    this->width = png_get_image_width(png_reader, png_info);
}

void Image::setPointers(png_structp png_reader, png_infop png_info)
{
    this->pointers = png_get_rows(png_reader, png_info);
}

png_structp Image::makeWriteStruct()
{
    png_structp writer = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if (writer == nullptr) {
        throw std::string("Can't create image reader struct");
    }

    return writer;
}

void Image::dump(const std::string &filename)
{
    FILE * f = fopen(filename.data(), "w");

    if (! f) {
        throw std::string("Can't open file: ") + filename;
    }

    png_structp writer;
    png_infop info;

    try {
        writer = this->makeWriteStruct();
        info = this->makeInfoStruct(writer);

        if (setjmp(png_jmpbuf(writer))) {
            throw std::string("Error during image IO initialization");
        }
    } catch (const std::string &msg) {
        png_destroy_write_struct(&writer, &info);
        fclose(f);
        throw;
    }

    png_set_IHDR(writer, info, width, height, bitDepth,
                 colorType, interlace, compression, filterType);

    png_set_rows(writer, info, pointers);
    png_init_io(writer, f);
    png_write_png(writer, info, PNG_TRANSFORM_IDENTITY, nullptr);

    fclose(f);
}

unsigned int Image::getHeight()
{
    return this->height;
}

unsigned int Image::getWidth()
{
    return this->width;
}

matrix Image::getMatrix()
{
    matrix m(this->height);

    for (std::size_t i = 0; i < this->height; i++) {
        m[i] = vector(this->width);
        for (std::size_t j = 0; j < this->width; j++) {
            m[i][j] = (double) this->pointers[i][j];
        }
    }

    return m;
}

void Image::setPointers(const matrix &m)
{
    for (auto i = 0; i < m.size(); i++) {
        for (auto j = 0; j < m[i].size(); j++) {
            pointers[i][j] = (png_byte) m[i][j];
        }
    }
}

Dataframe Image::split(unsigned int frameWidth, unsigned int frameHeight)
{
    if (width % frameWidth != 0) {
        throw std::string("Can't split the image width to frame width");
    } else if (height % frameHeight) {
        throw std::string("Can't split the image height to frame height");
    }

    Dataframe df;
    for (auto i = 0; i < height; i += frameHeight) {

        Series series;
        for (auto j = 0; j < width; j += frameWidth) {

            Frame frame(frameHeight, frameWidth);
            for (auto ii = 0; ii < frameHeight; ii++) {
                for (auto jj = 0; jj < frameWidth; jj++) {

                    frame.pixels[ii][jj] = (double) pointers[i + ii][j + jj];
                }
            }

            series.push_back(frame);
        }

        df.push_back(series);
    }

    return df;
}
