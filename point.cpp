#include <float.h>
#include <math.h>
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

void point::move(const double z, const double y, const double x)
{
    x1 += x;
    y1 += y;
    z1 += z;
}

bool point::equally(const point point)
{
    return bool(abs(x1 - point.x()) < DBL_EPSILON && abs(y1 - point.y()) < DBL_EPSILON && abs(y1 - point.y()) < DBL_EPSILON);
}
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
