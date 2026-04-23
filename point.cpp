#include "point.h"

point::point(const double x1, const double y1, const double z1)
{
    this->x1 = x1;
    this->y1 = y1;
    this->z1 = z1;
}

double point::x() const {
    return x1;
}

double point::y() const {
    return y1;
}

double point::z() const {
    return z1;
}
