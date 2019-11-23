#pragma once


#include <algorithm>
#include <random>
#include <vector>

#include "Exceptions.hpp"


template <typename T>
T rand(T min, T max)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<T> distribution(min, max);

    return distribution(generator);
}


template <typename T>
std::vector<T> rand(T min, T max, std::size_t size)
{
    auto v = std::vector<T>(size);

    for (std::size_t i = 0; i < size; i++) {
        v[i] = rand(min, max);
    }

    return v;
}


template <typename T>
std::vector<std::vector<T>> rand(T min, T max, std::size_t rows, std::size_t cols)
{
    auto m = std::vector<std::vector<T>>(rows);

    for (std::size_t i = 0; i < rows; i++) {
        m[i] = rand(min, max, cols);
    }

    return m;
}


template <typename T>
void shuffle(std::vector<T> & vector)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::shuffle(vector.begin(), vector.end(), generator);
}
