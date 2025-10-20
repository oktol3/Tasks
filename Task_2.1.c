#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

/**
 * @brief Ввод радиуса
 * @return Радиус шара
 */
double Value();
/**
 * @brief Проверка Правильности введеных данных
 * @param value - радиус
 */
void CheckValue(const double value);
/**
 * @brief Рассчет объема шара
 * @param Value - радиус
 * @return Объем шара
 */
double GetV(const double R);
/**
 * @brief Рассчет площади поверхности шара
 * @param Value - радиус
 * @return Площадь шара
 */
double GetS(const double R);

/**
 * @brief Точка Входа
 * @return 0, если программма выполнена корректно
 */
int main()
{
	const double R = Value();
	CheckValue(R);
	printf("V =%.2lf\n", GetV(R));
	printf("S =%.2lf\n", GetS(R));
	return 0;
}

double Value()
{
	double value = 0;
	if (!scanf_s("%lf", &value))
	{
		printf("ERROR");
		abort();
	}
	return value;
}

double GetV(const double R)
{
	return (4 * M_PI * pow(R, 3)) / 3;
}

double GetS(const double R)
{
	return 4 * M_PI * pow(R, 2);
}

void CheckValue(const double value)
{
	if (value <= 0)
	{
		printf("Value have to be positive\n");
		abort();
	}
}
