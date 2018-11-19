#include "support.h"

D_VECTOR multiply(D_VECTOR A, double b) {
    D_VECTOR y;

    for (double a : A) {
        y.push_back(a * b);
    }

    return y;
}

double multiply(D_VECTOR A, D_VECTOR B) {
    double y = 0.;

    for (size_t i = 0; i < A.size(); i++) {
        y += A[i] * B[i];
    }

    return y;
}

D_VECTOR sum(D_VECTOR A, D_VECTOR B) {
    D_VECTOR y;

    for (size_t i = 0; i < A.size(); i++) {
        y.push_back(A[i] + B[i]);
    }

    return y;
}
