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
double function(const int a, const int x);
/**
 * @brief Точка входа
 * @return 0, если программа завершена успешно
 */

int main()
{
	const float a = 2.5;
    printf("Enter x ");
    const float x = getValue();
	printf("function = %.2lf", function(x, a));
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


double function(const int a, const int x)
{

    if (fabs(x - a) < DBL_EPSILON || x < a)
    {
        return x * sin(a) * x;
    }
    else
    {
        return x * (x - a) ^ (1 / 3);
    }
}
