#pragma once


#include <tuple>
#include <vector>


typedef std::tuple<std::size_t, std::size_t> Dim;


template <typename T>
class Matrix
{
public:
    explicit Matrix(std::size_t rows, std::size_t cols, T initial = 0);
    explicit Matrix(const std::vector<std::vector<T>> & data);

    std::vector<std::vector<T>> data() const;

    std::size_t nRows();
    std::size_t nCols();

    Dim dim();

    bool operator==(const Matrix<T> & other) const;
    bool operator!=(const Matrix<T> & other) const;

protected:
    std::vector<std::vector<T>> m_data;
};


template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, T initial)
{
    auto row = std::vector<T>(cols, initial);

    m_data = std::vector<std::vector<T>>(rows, row);
}


template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> & data)
    : m_data(data)
{
    //
}


template <typename T>
std::vector<std::vector<T>> Matrix<T>::data() const
{
    return m_data;
}


template <typename T>
std::size_t Matrix<T>::nRows()
{
    return m_data.size();
}


template <typename T>
std::size_t Matrix<T>::nCols()
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
bool operator==(const Matrix<T> & a, const Matrix<T> & b)
{
    return a == b;
}


template <typename T>
bool operator!=(const Matrix<T> & a, const Matrix<T> & b)
{
    return a != b;
}
