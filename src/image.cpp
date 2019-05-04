#include "image.h"

#define PNG_BYTES_TO_CHECK 8

Frame::Frame(std::size_t h, std::size_t w)
{
    data = matrix(h, vector(w));
}

vector Frame::toVector()
{
    vector v;

    for (vector &row : data) {
        for (double pixel : row) {
            v.push_back(pixel);
        }
    }

    return v;
}

std::size_t Frame::width() const
{
    return data.front().size();
}

std::size_t Frame::height() const
{
    return data.size();
}

void Frame::fromVector(const vector &v)
{
    for (auto i = 0; i < height(); i++) {
        for (auto j = 0; j < width(); j++) {
            data[i][j] = v[i * width() + j];
        }
    }
}

Png::Png(const std::string &filename)
{
    FILE * f = read(filename);

    png_structp reader;

    try {
        reader = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        info = png_create_info_struct(reader);

        if (setjmp(png_jmpbuf(reader))) {
            throw std::string("Error during image IO initialization");
        }
    } catch (const std::string &msg) {
        png_destroy_read_struct(&reader, &info, nullptr);
        fclose(f);
        throw;
    }

    png_init_io(reader, f);
    png_set_sig_bytes(reader, PNG_BYTES_TO_CHECK);
    png_read_png(reader, info, PNG_TRANSFORM_IDENTITY, nullptr);

    init(reader, info);

    fclose(f);
    png_destroy_read_struct(&reader, nullptr, nullptr);
}

FILE * Png::read(const std::string &filename)
{
    FILE * f = fopen(filename.data(), "r");

    if (! f) {
        throw std::string("Can't read file: ") + filename;
    }

    unsigned char header[PNG_BYTES_TO_CHECK];

    if (fread(header, 1, PNG_BYTES_TO_CHECK, f) != PNG_BYTES_TO_CHECK) {
        throw std::string("Can't read bytes from file");
    }

    if (png_sig_cmp(header, 0, PNG_BYTES_TO_CHECK)) {
        throw std::string("File is not recognized as a PNG file");
    }

    return f;
}

void Png::init(png_structp png_reader, png_infop png_info)
{
    png_get_IHDR(png_reader, png_info, &width, &height, &colorDepth,
                 &colorType, &interlaceMethod, &compressionMethod,
                 &filterMethod);

    if (colorType != PNG_COLOR_TYPE_GRAY) {
        throw std::string("Invalid color type: expected 0");
    }

    if (colorDepth != 8) {
        throw std::string("Invalid color depth: expected 8");
    }

    data = png_get_rows(png_reader, png_info);
}

void Png::dump(const std::string &filename)
{
    FILE * f = fopen(filename.data(), "w");

    if (! f) {
        throw std::string("Can't open file: ") + filename;
    }

    png_structp writer;

    try {
        writer = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

        if (setjmp(png_jmpbuf(writer))) {
            throw std::string("Error during image IO initialization");
        }
    } catch (const std::string &msg) {
        png_destroy_write_struct(&writer, &info);
        fclose(f);
        throw;
    }

    png_set_IHDR(writer, info, width, height, colorDepth, colorType,
                 interlaceMethod, compressionMethod, filterMethod);

    png_set_rows(writer, info, data);
    png_init_io(writer, f);
    png_write_png(writer, info, PNG_TRANSFORM_IDENTITY, nullptr);

    fclose(f);
    png_destroy_write_struct(&writer, nullptr);
}

Dataframe Png::split(unsigned int frameWidth, unsigned int frameHeight)
{
    if (width % frameWidth != 0) {
        throw std::string("Can't split the image width to frame width");
    }

    if (height % frameHeight != 0) {
        throw std::string("Can't split the image height to frame height");
    }

    Dataframe df;
    for (auto i = 0; i < height; i += frameHeight) {

        Series series;
        for (auto j = 0; j < width; j += frameWidth) {

            Frame frame(frameHeight, frameWidth);
            for (auto ii = 0; ii < frameHeight; ii++) {
                for (auto jj = 0; jj < frameWidth; jj++) {

                    frame.data[ii][jj] = (double) data[i + ii][j + jj];
                }
            }

            series.push_back(frame);
        }

        df.push_back(series);
    }

    return df;
}

void Png::assemble(const Dataframe &df)
{
    auto frameWidth = df.front().front().width();
    auto frameHeight = df.front().front().height();

    width  = (png_uint_32) (frameWidth * df.front().size());
    height = (png_uint_32) (frameHeight * df.size());

    for (auto i = 0; i < df.size(); i++) {
        for (auto j = 0; j < df[i].size(); j++) {

            Frame frame = df[i][j];

            for (auto ii = 0; ii < frame.height(); ii++) {
                for (auto jj = 0; jj < frame.width(); jj++) {

                    auto value = frame.data[ii][jj];
                    auto pixel = (png_byte) (value > 0 ? value : 0);

                    data[i * frameHeight + ii][j * frameWidth + jj] = pixel;
                }
            }
        }
    }
}

Dataset Png::makeTestingSet(std::size_t size, std::size_t ySize)
{
    Dataset set(size);

    for (auto i = 0; i < size; i++) {
        vector pixels = rand(ySize, 0, 255);
        set[i] = {pixels, pixels};
    }

    return set;
}

Dataset convert(const Dataframe &df)
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
