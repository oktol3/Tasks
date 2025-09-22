#include <math.h>
#include <stdio.h>

/**
* @breif - Рассчитывает функцию A по заданной формуле
* @param x - переменная со значением x
* @param y - переменная со значением y
* @param z - переменная со значением z
* @return рассчитанное значение
*/
double getA(const double x, const double y, const double z);
/**
* @breif - Рассчитывает функцию B по заданной формуле
* @param x - переменная со значением x
* @param y - переменная со значением y
* @param z - переменная со значением z
* @return рассчитанное значение
*/
double getB(const double x, const double y, const double z);

/**
 * @breif Точка входа
 * @return 0, если ошибок нет
 */
int main()
{
	const double x = 0.78;
	const double y = 1.24;
	const double z = 0.5;
	printf("A = %lf\n", getA(x, y, z));
	printf("B = %lf\n", getB(x, y, z));
	return 0;
}

double getA(const double x, const double y, const double z)
{
	return (2 * pow(z, x))/(pow(pow(y, x) * pow(cos(x+y),2), 0.5) - 3*z);
}

double getB(const double x, const double y, const double z)
{
	return x * exp(pow(z, 0.5)) * cos(pow(x, 2 / (y * z)));
}
