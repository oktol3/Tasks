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
    /**
        @breid сравнение векторов, равны или нет 
        @param вектор с которым сравниваем
        @return True или False
    **/
    bool equally(const vector vector);
    /**
     * @breif сложение векторов
     * @param vector - вектор с которым происходит сложение
     * @return вектор полученный сложением
     */
    vector addition(const vector vector);
    /**
     * @breif вычитание векторов
     * @param vector - вектор который вычитают
     * @return вектор полученный вычитанием
     */
    vector subtraction(vector vector);
    /**
     * @breif умножение вектора на скаляр
     * @param а - вещественное число, которое умножают на вектор
     * @return вектор умноженный на число
     */
    vector multiply(const double a);
    /**
        @breif Координата вектора i
        @return вещественное число
     **/
    double i();
    /**
        @breif Координата вектора j
        @return вещественное число
     **/
    double j();
    /**
        @breif Координата вектора k
        @return вещественное число
     **/
    double k();
};



