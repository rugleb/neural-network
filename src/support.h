#ifndef NN_CPP_SUPPORT_H
#define NN_CPP_SUPPORT_H

#include <vector>

#define D_VECTOR    std::vector<double>
#define D_MATRIX    std::vector<D_VECTOR>


D_VECTOR multiply(D_VECTOR A, double b);

double multiply(D_VECTOR A, D_VECTOR B);

D_VECTOR sum(D_VECTOR A, D_VECTOR B);


#endif
