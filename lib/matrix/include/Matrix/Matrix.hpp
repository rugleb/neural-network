#pragma once


#include <tuple>
#include <vector>
#include <functional>


typedef std::tuple<std::size_t, std::size_t> Dim;


template <typename T>
using Data = std::vector<std::vector<T>>;


template <typename T>
class Matrix
{
public:
    explicit Matrix(std::size_t rows, std::size_t cols, T initial = 0);
    explicit Matrix(const Data<T> & data);

    Data<T> data() const;

    [[nodiscard]] std::size_t nRows() const;
    [[nodiscard]] std::size_t nCols() const;

    Dim dim();

    std::vector<T> & operator[] (std::size_t i);

    bool operator==(const Matrix<T> & other) const;
    bool operator!=(const Matrix<T> & other) const;

    Matrix<T> operator+(T scalar) const;
    Matrix<T> operator-(T scalar) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator/(T scalar) const;

    Matrix<T> map(std::function<T(T)> f) const;
    Matrix<T> map(T scalar, std::function<T(T, T)> f) const;


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
Matrix<T> Matrix<T>::map(T scalar, std::function<T(T, T)> f) const
{
    return map([&] (const T & item) {
        return f(item, scalar);
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
