#pragma once


#include <tuple>
#include <vector>
#include <functional>

#include "Exceptions.hpp"
#include "Utils.hpp"


typedef std::tuple<std::size_t, std::size_t> Dim;


template <typename T>
using Data = std::vector<std::vector<T>>;


template <typename T>
class Matrix
{
public:
    explicit Matrix(std::size_t rows, std::size_t cols, T initial = 0);
    explicit Matrix(const Data<T> & data);

    static Matrix<T> random(std::size_t rows, std::size_t cols, T min, T max);

    Data<T> data() const;

    [[nodiscard]] std::size_t nRows() const;
    [[nodiscard]] std::size_t nCols() const;

    Dim dim();

    std::vector<T> & operator[] (std::size_t i);
    T operator() (std::size_t i, std::size_t j) const;

    bool operator==(const Matrix<T> & other) const;
    bool operator!=(const Matrix<T> & other) const;

    Matrix<T> operator+(T scalar) const;
    Matrix<T> operator-(T scalar) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator/(T scalar) const;

    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator/(const Matrix<T> & other) const;

    Matrix<T> dot(const Matrix<T> & other);
    Matrix<T> transpose();

    Matrix<T> map(std::function<T(T)> f) const;
    Matrix<T> map(const T & scalar, std::function<T(T, T)> f) const;
    Matrix<T> map(const Matrix & other, std::function<T(T, T)> f) const;

    bool every(std::function<T(T)> f);

protected:
    Data<T> m_data;
};


template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, T initial)
{
    m_data = Data<T>(rows, std::vector<T>(cols, initial));
}


template <typename T>
Matrix<T>::Matrix(const Data<T> & data)
    : m_data(data)
{
    //
}


template <typename T>
Matrix<T> Matrix<T>::random(std::size_t rows, std::size_t cols, T min, T max)
{
    auto data = rand(min, max, rows, cols);

    return Matrix<T>(data);
}


template <typename T>
Data<T> Matrix<T>::data() const
{
    return m_data;
}


template <typename T>
std::size_t Matrix<T>::nRows() const
{
    return m_data.size();
}


template <typename T>
std::size_t Matrix<T>::nCols() const
{
    return m_data.front().size();
}


template <typename T>
Dim Matrix<T>::dim()
{
    auto rows = nRows();
    auto cols = nCols();

    return Dim(rows, cols);
}


template <typename T>
std::vector<T> & Matrix<T>::operator[](std::size_t i)
{
    return m_data[i];
}


template <typename T>
T Matrix<T>::operator()(std::size_t i, std::size_t j) const
{
    return m_data[i][j];
}


template <typename T>
bool Matrix<T>::operator==(const Matrix<T> & other) const
{
    return m_data == other.data();
}


template <typename T>
bool Matrix<T>::operator!=(const Matrix<T> & other) const
{
    return m_data != other.data();
}


template <typename T>
Matrix<T> Matrix<T>::operator+(T scalar) const
{
    return map(scalar, std::plus<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator-(T scalar) const
{
    return map(scalar, std::minus<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const
{
    return map(scalar, std::multiplies<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator/(T scalar) const
{
    return map(scalar, std::divides<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const
{
    return map(other, std::plus<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const
{
    return map(other, std::minus<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const
{
    return map(other, std::multiplies<T>());
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T> & other) const
{
    return map(other, std::divides<T>());
}


template <typename T>
Matrix<T> Matrix<T>::map(std::function<T(T)> f) const
{
    auto rows = nRows();
    auto cols = nCols();

    auto result = Matrix<T>(rows, cols);

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            result[i][j] = f(m_data[i][j]);
        }
    }

    return result;
}


template <typename T>
Matrix<T> Matrix<T>::map(const T & scalar, std::function<T(T, T)> f) const
{
    return map([&] (const T & item) {
        return f(item, scalar);
    });
}


template <typename T>
Matrix<T> Matrix<T>::map(const Matrix & other, std::function<T(T, T)> f) const
{
    auto rows = nRows();
    auto cols = nCols();

    auto result = Matrix<T>(rows, cols);

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            result[i][j] = f(m_data[i][j], other(i, j));
        }
    }

    return result;
}


template <typename T>
Matrix<T> Matrix<T>::dot(const Matrix<T> & other)
{
    if (nCols() != other.nRows()) {
        throw DimensionError("Can't perform matrices multiplication: incorrect dimensions");
    }

    auto rows = nRows();
    auto cols = other.nCols();

    auto result = Matrix<T>(rows, cols);

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            for (std::size_t k = 0; k < nCols(); k++) {
                result[i][j] += m_data[i][k] * other(k, j);
            }
        }
    }

    return result;
}


template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    auto rows = nCols();
    auto cols = nRows();

    auto result = Matrix<T>(rows, cols);

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            result[i][j] = m_data[j][i];
        }
    }

    return result;
}


template <typename T>
bool Matrix<T>::every(std::function<T(T)> f)
{
    return std::all_of(m_data.begin(), m_data.end(), [&] (std::vector<T> v) {
        return std::all_of(v.begin(), v.end(), f);
    });
}


template <typename T>
bool operator==(const Matrix<T> & a, const Matrix<T> & b)
{
    return a == b;
}


template <typename T>
bool operator!=(const Matrix<T> & a, const Matrix<T> & b)
{
    return a != b;
}
