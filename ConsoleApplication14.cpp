//14.	Правильная трехугольная пирамида задана тремя точками основания и вершиной.
//      Найти высоту пирамиды. Рассчитать площадь боковой поверхности.
#include <iostream>
#include <math.h>
#include <float.h>
#include "Point.h"
#include "pyramid.h"

point getPoint();

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
    //std::cout << c.x() << " " << c.y() << " " << c.z() << std::endl;
    //std::cout << d.x() << " " << d.y() << " " << d.z() << std::endl;

    return 0;
}

point getPoint()
{
    //std::cout << name;
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
