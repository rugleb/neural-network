#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>
#include <random>


typedef std::vector<double> double2;
typedef std::vector<double2> double3;


std::size_t checkDim(const double2 &a, const double2 &b);

double  operator* (const double2 &a, const double2 &b);
double2 operator+ (const double2 &a, const double2 &b);
double2 operator- (const double2 &a, const double2 &b);

double  rand (double min, double max);
double2 rand (unsigned int size, double min, double max);
double3 rand (unsigned int rows, unsigned int cols, double min, double max);

#endif
