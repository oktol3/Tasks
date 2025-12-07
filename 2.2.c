#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

/**
 * @brief считывает вещественное значение с клавиатуры с проверкой ввода
 * @return возвращает считанное значение
 */
double getValue();

/**
 * @brief Рассчет по заданной функции
 * @param a - заданная константа - 2.5
 * @param x - переменная
 * @return 0, если программа завершена успешно
 */
double function(const double a, const double x);

/**
 * @brief Точка входа
 * @return 0, если программа завершена успешно
 */
int main()
{
    const double a = 2.5;
    printf("Enter x ");
    const double x = getValue();
    printf("y = %.2lf", function(a, x));
    return 0;
}

double getValue()
{
    double value = 0;
    if (!scanf_s("%lf", &value))
    {
        printf("Error\n");
        exit(1);
    }
    return value;
}


double function(const double a, const double x)
{
    if (!(x>a))
    {   
        return x * sin(a) * x;
        
    }
    else
    {
        return x * pow((x-a), 1.0 / 3.0);
    }
}
