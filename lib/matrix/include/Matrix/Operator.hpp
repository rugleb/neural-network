#pragma once


#include "Exceptions.hpp"


template <typename T>
class Operator
{
public:
    static T add(T a, T b)  // addition
    {
        return a + b;
    }

    static T sub(T a, T b)  // subtraction
    {
        return a - b;
    }

    static double div(T a, T b)  // division
    {
        if (b == 0) {
            throw ZeroDivisionError("Can't divided by zero");
        }

        return (double) a / b;
    }

    static T mul(T a, T b)  // multiplication
    {
        return a * b;
    }

    static bool eq(T a, T b)  // equality
    {
        return a == b;
    }

    static bool ne(T a, T b)  // difference
    {
        return a != b;
    }
};
