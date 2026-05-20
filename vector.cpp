#include <iostream>
#include <cmath>
#include <float.h>
#include "vector.h"
#include "point.h"

vector::vector(const point& X, const point& Y)
    : A(X), B(Y) {}

vector::vector(const vector& other)
    : A(other.A)
    , B(other.B) 
{
    std::cout << "[DEBUG] vector copy constructor called" << std::endl;
}

vector& vector::operator=(const vector& other)
{
    std::cout << "[DEBUG] vector copy assignment called" << std::endl;

    if (this != &other)
    {
        A = other.A;
        B = other.B;
    }

    return *this;
}


vector::vector(vector&& other) noexcept
    : A(std::move(other.A))
{
    std::cout << "[DEBUG] vector move constructor called" << std::endl;

}

vector& vector::operator=(vector&& other) noexcept
{
    std::cout << "[DEBUG] vector move assignment called" << std::endl;

    if (this != &other)
    {
        A = std::move(other.A);
        B = std::move(other.B);
    }

    return *this;
}

vector::~vector()
{
    std::cout << "[DEBUG] vector destructor called" << std::endl;

}

bool vector::operator==(const vector& other) const
{
    return (std::abs(i() - other.i()) < DBL_EPSILON &&
        std::abs(j() - other.j()) < DBL_EPSILON &&
        std::abs(k() - other.k()) < DBL_EPSILON);
}

bool vector::operator!=(const vector& other) const
{
    return !(*this == other);
}

vector vector::operator+(const vector& other) const
{
    double new_i = i() + other.i();
    double new_j = j() + other.j();
    double new_k = k() + other.k();

    point new_point(new_i, new_j, new_k);

    return vector(point(0, 0, 0), new_point);
}

vector vector::operator-(const vector& other) const
{
    double new_i = i() - other.i();
    double new_j = j() - other.j();
    double new_k = k() - other.k();

    point new_point(new_i, new_j, new_k);
    return vector(point(0, 0, 0), new_point);
}

vector vector::operator*(double scalar) const
{
    double new_i = i() * scalar;
    double new_j = j() * scalar;
    double new_k = k() * scalar;

    point new_point(new_i, new_j, new_k);
    return vector(point(0, 0, 0), new_point);
}

vector operator*(double scalar, const vector& v)
{
    return v * scalar;
}

double vector::i() const
{
    return B.x() - A.x();
}

double vector::j() const
{
    return B.y() - A.y();
}

double vector::k() const
{
    return B.z() - A.z();
}
