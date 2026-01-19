#include <stdio.h>
#include <float.h>
#include <math.h>


/**
 * @breif ручной ввод значений
 * @return введенное число типа int
 */
int Value();

/**
 * @breif ручной ввод значений
 * @return введенное число типа double
 */
double doubleValue();

/**
 * @breif сумма элементов последовательности от 1 до n
 * @param n - последний элемент последовательности
 * @return сумма элементов последовательности
 */
double getSumSequence(const int n);

/**
 * @breif сумма всех элементов последовательности по модулю не меньших заданного числа e
 * @param e - наименьший по модулю элемент для сумирования
 * @return сумма элементов последовательности
 */
double getSumSequenceBigger_e(const double e);

/**
 * @breif проверка n
 * @param n - переменная типа int
 */
void checking_n(const int n);

/**
 * @breif точка входа
 * @return 0, если программа завершена без ошибок
 */
int main()
{
	printf("Enter n ");
	int n = Value();
	checking_n(n);
	printf("Sum Sequence %.2lf", getSumSequence(n));
	printf("\nEnter e ");
	double e = doubleValue();
	printf("Sum Sequence Bigger e %.2lf", getSumSequenceBigger_e(e));
	return 0;
}

int Value()
{
	int value = 0;
	if (!scanf_s("%d", &value))
	{
		printf("ERROR");
		exit(1);
	}
	return value;
}

double doubleValue()
{
	double value = 0.0;
	if (!scanf_s("%lf", &value))
	{
		printf("ERROR");
		exit(1);
	}
	return value;
}

void checking_n(const int n)
{
	if (n < 1)
	{
		printf("ERROR");
		exit(1);
	}
}

double getSumSequence(const int n)
{
	double current = 1.0;
	double result = 0;

	for (int k = 1; k <= n; k++)
	{
		current *= (-1.0 / (k + 3) / (k + 4));
		result += current;
		
	}
	return result;
}

double getSumSequenceBigger_e(const double e)
{
	double current = 1.0;
	double result = 0;

	for (int k = 1; fabs(current) > e; k++)
	{
		result += current;
		current *= (-1.0 / (k + 3) / (k + 4));
	}
	return result;
}
