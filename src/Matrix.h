#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>
#include <random>
#include <algorithm>

typedef double unit;
typedef std::vector<unit> vector;
typedef std::vector<vector> matrix;

matrix operator* (const matrix &a, const matrix &b);
matrix operator+ (const matrix &a, const matrix &b);
matrix operator- (const matrix &a, const matrix &b);
matrix operator^ (const matrix &a, const matrix &b);
matrix operator* (const matrix &a, double b);

typedef double (*callable) (double, bool);

double relu(double x, bool derivative);
double linear(double x, bool derivative);
double sigmoid(double x, bool derivative);

matrix transpose  (const matrix &m);
matrix transpose  (const vector &m);
matrix activate   (const matrix &m, callable f);
matrix derivative (const matrix &m, callable f);

unit   rand (double min, double max);
vector rand (unsigned int size, double min, double max);
matrix rand (unsigned int rows, unsigned int cols, double min, double max);

double MSE(matrix e);

#endif
