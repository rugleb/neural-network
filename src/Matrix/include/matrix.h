#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <random>

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;
typedef std::vector<matrix> tensor;

typedef double (*callable) (double, bool);

struct MatrixException : public std::exception {
    const char * what () const noexcept override;
};

matrix operator+ (const matrix &a, const matrix &b);
matrix operator- (const matrix &a, const matrix &b);
matrix operator^ (const matrix &a, const matrix &b);
matrix operator* (const matrix &a, const matrix &b);
matrix operator* (const matrix &a, double b);
matrix T (const matrix &a);
matrix T (const vector &a);

double rand(double min, double max);
vector rand(unsigned long cols, double min, double max);
matrix rand(unsigned long rows, unsigned long cols, double min, double max);

#endif
