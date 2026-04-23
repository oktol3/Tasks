#include <iostream>
#include "point.h"
#include "vector.h"

/**
* @breaf считывает точки с клавиатуры
* @return считанное знаначение в формате point
*/
point getPoint();

/**
* @breaf точка входа в программу
* @return 0, если программа выполнена корректно
*/
int main()
{
    std::cout << "A: ";
    point A = getPoint();
    std::cout << "B: ";
    point B = getPoint();
    vector AB(A, B);
    return 0;
}

point getPoint()
{
    double x = 0;
    double y = 0;
    double z = 0;
    std::cin >> x >> y >> z;
    if (std::cin.fail())
    {
        std::cout << "error" << std::endl;
        exit(1);
    }
    return point(x, y, z);
}
