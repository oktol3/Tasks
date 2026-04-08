#pragma once
#include "point.h"
/**
    @brief   класс пирамида
**/
class pyramid {
private:
    /**
         * @breaf рассчет объема по 4 точкам
         *
         * @param A - точка A
         * @param B - точка B
         * @param C - точка C
         * @param D - точка D
         * @return Объем паралепипеда по 3 векторам
     */
    double getV(const point& A, const point& B, const point& C, const point& D);
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

