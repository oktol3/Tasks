#pragma once
#include "point.h"
/**
    @brief   класс пирамида
**/
class pyramid {
private:
    point A;
    point B;
    point C;
    point D;

public:
    /**
        @brief конструктор
        @param A - точка A
        @param B - точка B
        @param C - точка C
        @param D - точка D
    **/
    pyramid(const point& A, const point& B, const point& C, const point& D);
    /**
        @brief рассчет высоты тэтрайдера
        @return рассчитанное значение
    **/
    double getH();
    /**
        @brief рассчет площади боковой поверхности
        @return рассчитанное значение
    **/
    double square();
};

