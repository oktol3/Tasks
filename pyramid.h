#pragma once
#include "point.h"

class pyramid {
private:
    point A;
    point B;
    point C;
    point D;

public:
    pyramid(const point& A, const point& B, const point& C, const point& D);
    double getH();
    double square();
};

