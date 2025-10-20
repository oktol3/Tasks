#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>


/**
 * @brief Ввод переменной типа double
 * @return переменная типа double
 */
double Value();
/**
 * @breif считает y относительно x для заданной функции
 * @param x - аргумент
 * @return значение y
 */
double getY(const double x);
/**
 * @breif Проверка пренадлежит ли аргумент ООФ
 * @param x - аргумент функции
 * @return True, если аргумент пренадлежит ООФ, иначе False
 */
bool defineOOF(const double x);
/**
 * @breif точка входа
 * @return 0, если программа завершина без ошибок
 */
int main()
{
	printf("start ");
	double start = Value();
	printf("end ");
	double end = Value();
	printf("step ");
	double step = Value();
	for (double x = start; x < end+DBL_EPSILON; x = x+ step)
	{
		if (defineOOF(x))
		{
			printf("x = %.2lf, y = %.4lf\n", x, getY(x));
		}
		else
		{
			printf("x = %.2lf not in OOF\n", x);
		}
	}
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

bool defineOOF(const double x)
{
	return x >= 0;
}

double getY(const double x)
{
	return 3*sin(pow(x, 0.5)) + 0.39*x-3.8;
}
