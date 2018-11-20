#ifndef NN_CPP_SUPPORT_H
#define NN_CPP_SUPPORT_H

#include <vector>

#define D_VECTOR    std::vector<double>
#define D_MATRIX    std::vector<D_VECTOR>


D_VECTOR operator* (D_VECTOR, double);
double   operator* (D_VECTOR, D_VECTOR);
D_VECTOR operator+ (D_VECTOR, D_VECTOR);
D_VECTOR operator- (D_VECTOR, D_VECTOR);

#endif
