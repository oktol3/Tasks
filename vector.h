#pragma once
#include "point.h"
/**
    @brief класс вектор
**/
class vector
{
private:
    /**
        @brief Точка А
    **/
    point A;
    /**
        @brief Точка В
    **/
    point B;
public:
    /**
       @brief конструктор
       @param A - точка A
       @param B - точка B
    **/
    vector(const point& X, const point& Y);
};

