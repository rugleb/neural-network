#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>
#include <string>
#include <random>
#include <iostream>

#define  square(x)  (x * x)

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;

typedef double (*callable) (double, bool);

struct MatrixException : public std::exception {
    const char * what () const noexcept override;
};

matrix operator+ (const matrix &, const matrix &);
matrix operator- (const matrix &, const matrix &);
matrix operator^ (const matrix &, const matrix &);
matrix operator* (const matrix &, const matrix &);
matrix operator* (const matrix &, double);
matrix T (const matrix &);
matrix T (const vector &);

double rand(double, double);
vector rand(unsigned int, double, double);
matrix rand(unsigned int, unsigned int, double, double);

double relu (double, bool = false);
double linear (double, bool = false);
double sigmoid (double, bool = false);

double MSE (const vector &, const vector &);
double MSE (const matrix &, const matrix &);

#endif
