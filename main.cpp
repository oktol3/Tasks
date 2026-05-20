//Вариант 17 Вектор в трехмерном пространстве
//Вектор в трехмерном пространстве.Предусмотреть задание вектора двумя точками класса Точка(класс Точка задается
//тройкой чисел(абсцисса, ордината, аппликата).Переопределить операторы равенства и неравенства
//векторов, сложения векторов, вычитание векторов, умножение на скаляр.
//Для класса Точка определить все необходимые для дальнейшего использования операторы(операторы сравнения, сдвига 
//влево и вправо, сложение и вычитание Точки и вещественного числа).



#include <iostream>
#include <float.h>
#include "point.h"
#include "vector.h"

/**
* @breaf считывает точки с клавиатуры
* @return считанное знаначение в формате point
*/
point getPoint();

/**
 * @breif Получить вещественное число
 * @retutn вещественное число
 */
double getA();

/**
* @breaf точка входа в программу
* @return 0, если программа выполнена корректно
*/
int main()
{
    std::cout << "O: ";
    point O = getPoint();
    std::cout << "P: ";
    point P = getPoint();
    std::cout << "R: ";
    point R = getPoint();
    std::cout << "S: ";
    point S = getPoint();
    vector OP(O, P);
    vector RS(R, S);
    std::cout << "OP (" << OP.i() << "; " << OP.j() << "; " << OP.k() << " )" << std::endl;
    std::cout << "RS (" << RS.i() << "; " << RS.j() << "; " << RS.k() << " )" << std::endl;
    if (OP.operator==(RS))
    {
        std::cout << "The vectors are equal" << std::endl;
    }
    else
    {
        std::cout << "The vectors are not equal" << std::endl;
    }
    vector OP_plus_RS = OP.operator+(RS);
    std::cout << "OP + RS (" << OP_plus_RS.i() << "; " << OP_plus_RS.j() << "; " << OP_plus_RS.k() << " )" << std::endl;

    vector OP_minus_RS = OP.operator-(RS);
    std::cout << "OP - RS (" << OP_minus_RS.i() << "; " << OP_minus_RS.j() << "; " << OP_minus_RS.k() << " )" << std::endl;

    std::cout << "move O by x, y, z" << std::endl;
    O.move(getA(), getA(), getA());
    std::cout << "move P by x, y, z" << std::endl;
    P.move(getA(), getA(), getA());
    std::cout << "move R by x, y, z" << std::endl;
    R.move(getA(), getA(), getA());
    std::cout << "move S by x, y, z" << std::endl;
    S.move(getA(), getA(), getA());
    vector newOP(O, P);
    vector newRS(R, S);
    std::cout << "new OP (" << newOP.i() << "; " << newOP.j() << "; " << newOP.k() << " )" << std::endl;
    std::cout << "new RS (" << newRS.i() << "; " << newRS.j() << "; " << newRS.k() << " )" << std::endl;
    if (O.equally(P))
    {
        std::cout << "The points are equal" << std::endl;
    }
    else
    {
        std::cout << "The points are not equal" << std::endl;
    }
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

double getA()
{
    double a = 0;
    std::cin >> a;
    if (std::cin.fail())
    {
        std::cout << "error" << std::endl;
        exit(1);
    }
    return a;
}
