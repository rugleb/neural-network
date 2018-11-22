#ifndef NN_CPP_SUPPORT_H
#define NN_CPP_SUPPORT_H

#include <cmath>
#include <vector>

#define SQUARE(x)   (x * x)

#define D_VECTOR    std::vector<double>
#define D_MATRIX    std::vector<D_VECTOR>


D_VECTOR operator* (const D_VECTOR &, double);
double   operator* (const D_VECTOR &, const D_VECTOR &);
D_VECTOR operator+ (const D_VECTOR &, const D_VECTOR &);
D_VECTOR operator- (const D_VECTOR &, const D_VECTOR &);

double sum (const D_VECTOR &);
double mid (const D_VECTOR &);

double   random (double, double);
D_VECTOR random (std::size_t, double, double);
D_MATRIX random (std::size_t, std::size_t, double, double);


#endif
