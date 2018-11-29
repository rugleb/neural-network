#ifndef NEURAL_NETWORK_MATRIX_H
#define NEURAL_NETWORK_MATRIX_H

#include <vector>


typedef std::vector<double> double2;
typedef std::vector<double2> double3;


std::size_t checkDim(const double2 &a, const double2 &b);

double  operator* (const double2 &a, const double2 &b);
double2 operator+ (const double2 &a, const double2 &b);
double2 operator- (const double2 &a, const double2 &b);


#endif
