#pragma once
#include "point.h"
/**
    @brief   класс пирамида
**/
class pyramid {
private:
    /**
         * @breaf рассчет объема по 4 точкам
         * @return Объем паралепипеда по 3 векторам
     */
    double getV();
    /**
         * @breaf рассчет площадь треугольника по 4 точкам
         * @param X - точка X
         * @param Y - точка Y
         * @param Z - точка Z
         * @return площадь треугольника по 2 векторам
    */
    double getS(const point& X, const point& Y, const point& Z);
    /**
         @breif точка A
    **/
    point A;
    /**
         @breif точка B
    **/
    point B;
    /**
         @breif точка C
    **/
    point C;
    /**
         @breif точка D
    **/
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

