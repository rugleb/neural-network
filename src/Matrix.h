#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>
#include <random>


typedef double unit;
typedef std::vector<unit> vector;
typedef std::vector<vector> matrix;


std::size_t checkDim(const vector &a, const vector &b);
std::size_t checkDim(const matrix &a, const vector &b);

double operator* (const vector &a, const vector &b);
vector operator+ (const vector &a, const vector &b);
vector operator- (const vector &a, const vector &b);
vector operator* (const matrix &a, const vector &b);

unit   rand (double min, double max);
vector rand (unsigned int size, double min, double max);
matrix rand (unsigned int rows, unsigned int cols, double min, double max);

#endif
