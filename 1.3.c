#include <stdio.h>
#include <math.h>
#include <float.h>

/**
 * @breif Рассчет кинетической энергии
 * @param m - масса пули
 * @param v - скорость пули
 * @return Кинетическая энергия
 */
double kineticEnergy(const double m, const double v);
/**
 * @brief Ввод переменной типа double
 * @return переменная типа double
 */
double Value();

/**
 * @breif Проверка массы на положительность 
 * @param m - масса пули
 * @param v - скорость пули
 * @return Кинетическая энергия
 */
void checkPositive(const double m);
/**
 * @breif Точка входа
 * @return 0, если завершено успешно
 */
int main()
{
	printf("enter m, g ");
	double const m = Value();
	checkPositive(m);
	printf("enter v, m/s ");
	double const v = Value();
	printf("Ek = %.2lf", kineticEnergy(m, v));
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

void checkPositive(const double m)
{
	if (!(m-DBL_EPSILON > 0))
	{
		printf("error: m not positive");
		exit(1);
	}
}

double kineticEnergy(const double m, const double v)
{
	printf("%lf\n", m);
	printf("%lf\n", v);
	return ((m/1000)*pow(v,2))/2;
}
