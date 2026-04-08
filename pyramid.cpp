#include <iostream>
#include "pyramid.h"
#include <math.h>
#include <float.h>

pyramid::pyramid(const point& A, const point& B, const point& C, const point& D) :A(A), B(B), C(C), D(D)
{
    if ((abs(getV(A, B, C, D)) - DBL_EPSILON) < 0)
    {
        std::cout << "error" << std::endl;
        exit(2);
    }
}

double pyramid::getH()
{
    // 1/3 * S * h = V
    // h = 3V/S

    return getV(A, B, C, D) / getS(A, B, C);
}

double pyramid::square()
{
    return getS(D, A, B) + getS(D, B, C) + getS(D, C, A);
}

double getV()
{
    //|B.x() - A.x()  B.y() - A.y()  B.z() - A.z()|
    //|C.x() - A.x()  C.y() - A.y()  C.z() - A.z()| - 3 объемa пирамиды
    //|D.x() - A.x()  D.y() - A.y()  D.z() - A.z()|

    return abs((B.x() - A.x()) * (C.y() - A.y()) * (D.z() - A.z())
        + (C.x() - A.x()) * (D.y() - A.y()) * (B.z() - A.z())
        + (B.y() - A.y()) * (C.z() - A.z()) * (D.x() - A.x())
        - (D.x() - A.x()) * (C.y() - A.y()) * (B.z() - A.z())
        - (C.x() - A.x()) * (B.y() - A.y()) * (D.z() - A.z())
        - (D.y() - A.y()) * (C.z() - A.z()) * (B.x() - A.x()));
}

double getS(const point& X, const point& Y, const point& Z)
{
    // S = |[вектор A * вектор B]| / 2
    // A = ((x2 - x1), (y2 - y1), (z2 - z1))
    // B = ((x3 - x1), (y3 - y1), (z3 - z1))
    // 
    // |       i              j              k       |
    // | Y.x() - X.x()  Y.y() - X.y()  Y.z() - X.z() |
    // | Z.x() - X.x()  Z.y() - X.y()  Z.z() - X.z() |

    return pow((pow((Y.y() - X.y()) * (Z.z() - X.z()) - (Z.y() - X.y()) * (Y.z() - X.z()), 2)
        + pow(-(Y.x() - X.x()) * (Z.z() - X.z()) + (Z.x() - X.x()) * (Y.z() - X.z()), 2)
        + pow((Y.x() - X.x()) * (Z.y() - X.y()) - (Z.x() - X.x()) * (Y.z() - X.z()), 2)), 0.5) / 2;
}

