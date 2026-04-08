//14.	Правильная трехугольная пирамида задана тремя точками основания и вершиной.
//      Найти высоту пирамиды. Рассчитать площадь боковой поверхности.
#include <iostream>
#include <math.h>
#include <float.h>
#include "Point.h"
#include "pyramid.h"

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
    std::cout << "C: ";
    point C = getPoint();
    std::cout << "D: ";
    point D = getPoint();
    pyramid ABCD(A, B, C, D);
    std::cout << ABCD.getH() << std::endl;
    std::cout << ABCD.square() << std::endl;

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
