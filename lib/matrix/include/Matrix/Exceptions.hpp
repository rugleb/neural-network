#pragma once


#include <stdexcept>


class ValueError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};


class ZeroDivisionError : public ValueError
{
public:
    using ValueError::ValueError;
};


class DimensionError : public ValueError
{
public:
    using ValueError::ValueError;
};
