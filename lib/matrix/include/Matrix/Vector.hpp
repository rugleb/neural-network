#pragma once


#include <vector>

#include "Operator.hpp"
#include "Utils.hpp"


template <typename T>
class Vector
{
public:
    explicit Vector(std::size_t size, T initial = 0);
    explicit Vector(const std::vector<T> &data);

    static Vector<T> random(T min, T max, std::size_t size);

    std::size_t size();
    std::vector<T> data() const;

    T& operator[](std::size_t i);
    
    Vector<T> operator+ (T x);
    Vector<T> operator- (T x);
    Vector<T> operator* (T x);
    Vector<T> operator/ (T x);

    Vector<T> operator+ (const std::vector<T> &x);
    Vector<T> operator- (const std::vector<T> &x);

    Vector<T> operator+ (const Vector<T> &x);
    Vector<T> operator- (const Vector<T> &x);

    bool operator== (const std::vector<T> &x);
    bool operator== (const Vector<T> &x);

    Vector<T> map(T x, T f(T, T));
    Vector<T> map(const std::vector<T> &x, T f(T, T));
    Vector<T> map(const Vector<T> &x, T f(T, T));
    
protected:
    std::vector<T> m_data;
};


template <typename T>
Vector<T>::Vector(std::size_t size, T initial)
{
    m_data = std::vector<T>(size, initial);
}


template <typename T>
Vector<T>::Vector(const std::vector<T> &data)
    : m_data(data)
{
    //
}


template <typename T>
Vector<T> Vector<T>::random(T min, T max, std::size_t size)
{
    auto data = rand(min, max, size);

    return Vector<T>(data);
}


template <typename T>
std::size_t Vector<T>::size()
{
    return m_data.size();
}


template <typename T>
std::vector<T> Vector<T>::data() const
{
    return m_data;
}


template <typename T>
T& Vector<T>::operator[](std::size_t i)
{
    return m_data[i];
}


template <typename T>
Vector<T> Vector<T>::operator+(const T x)
{
    return map(x, Operator<T>::add);
}


template <typename T>
Vector<T> Vector<T>::operator-(const T x)
{
    return map(x, Operator<T>::sub);
}


template <typename T>
Vector<T> Vector<T>::operator*(const T x)
{
    return map(x, Operator<T>::mul);
}


template <typename T>
Vector<T> Vector<T>::operator/(const T x)
{
    return map(x, Operator<T>::div);
}


template <typename T>
Vector<T> Vector<T>::operator+(const std::vector<T> &x)
{
    return map(x, Operator<T>::add);
}


template <typename T>
Vector<T> Vector<T>::operator-(const std::vector<T> &x)
{
    return map(x, Operator<T>::sub);
}


template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &x)
{
    return map(x.data(), Operator<T>::add);
}


template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &x)
{
    return map(x.data(), Operator<T>::sub);
}


template <typename T>
bool Vector<T>::operator==(const std::vector<T> &x)
{
    return m_data == x;
}


template <typename T>
bool Vector<T>::operator==(const Vector<T> &x)
{
    return m_data == x.data();
}


template <typename T>
Vector<T> Vector<T>::map(T x, T (*f)(T, T))
{
    std::size_t size = m_data.size();

    auto result = Vector<T>(size);

    for (std::size_t i = 0; i < size; i++) {
        result[i] = f(m_data[i], x);
    }

    return result;
}


template <typename T>
Vector<T> Vector<T>::map(const std::vector<T> &x, T (*f)(T, T))
{
    std::vector<T> data(m_data.size());

    std::transform(m_data.begin(), m_data.end(), x.begin(), data.begin(), f);

    return Vector<T>(data);
}


template <typename T>
Vector<T> Vector<T>::map(const Vector<T> &x, T (*f)(T, T))
{
    return map(x.data(), f);
}
