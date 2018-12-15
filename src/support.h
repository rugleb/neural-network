#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>
#include <string>
#include <random>

typedef std::vector<double> vector;
typedef std::vector<vector> matrix;
typedef std::vector<matrix> tensor;

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
vector rand(unsigned long, double, double);
matrix rand(unsigned long, unsigned long, double, double);

double relu (double, bool = false);
double tanh (double, bool = false);
double linear (double, bool = false);
double sigmoid (double, bool = false);

vector apply(const vector &, callable, bool = false);
matrix apply(const matrix &, callable, bool = false);

double MSE (const vector &, const vector &);
double MSE (const matrix &, const matrix &);

#endif
