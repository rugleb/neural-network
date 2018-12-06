#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>
#include <string>
#include <random>
#include <iostream>

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;

struct MatrixException : public std::exception {
    const char * what () const noexcept override;
};

matrix operator+ (const matrix &, const matrix &);
matrix operator- (const matrix &, const matrix &);
matrix operator^ (const matrix &, const matrix &);
matrix operator* (const matrix &, const matrix &);
matrix T (const matrix &);
matrix T (const vector &);

double rand(double, double);
vector rand(unsigned int, double, double);
matrix rand(unsigned int, unsigned int, double, double);

#endif
