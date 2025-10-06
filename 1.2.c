#include <stdio.h>


/**
 * @return Ввод данных типа double
 * @return Введенное значение
 */
double value();

/**
 * @brief Проверка Правильности введеных данных
 * @param value - введенное значение
 */
void checkValue(const double value);

/**
 * @brief Точка Входа
 * @return 0, если программма выполнена корректно
 */
int main()
{
	printf("A = ");
	const double A = value();
	checkValue(A);
	printf("S = ");
	const double N = value();
	checkValue(N);
	printf("S = %.2lf\n", (N / 100.0) * A * A);
	printf("P = %.2lf\n", ((N / 100.0) * A + A))*2;
}

double value()
{
	double value = 0;
	if (!scanf_s("%lf", &value))
	{
		printf("ERROR");
		abort();
	}
	return value;
}

void checkValue(const double value)
{
	if (value <= 0)
	{
		printf("Value have to be positive");
		abort();
	}
}
