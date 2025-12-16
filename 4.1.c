// 4_1
#include <stdio.h>
#include <stdlib.h>

/**
 * @return Ввод данных типа int
 * @return Введенное значение
 */
int Value();
/**
 * @return Получение переменной типа size_t
 * @return переменная типа size_t
 */
size_t getSize();
/**
 * @breif Заполнение массива вручную
 * @param Массив
 * @param Размер массива
 * @return Заполненный массив
 */
void fillArray(int* arr, const size_t size);
/**
 * @breif Заполнение массива рандомно
 * @param Массив
 * @param Размер массива
 * @return Заполненный массив
 */
void fillRandom(int* arr, const size_t size);
/**
 * @breif Вовод массива
 * @param Массив
 * @param Размер массива
 */
void printArray(const int* arr, const size_t size);
/**
 * @breif Вывод индексов эллементов массив больших чем А
 * @param Массив
 * @param Размер массива
 * @param А
 */
void printBiggerA(const int* arr, const size_t size, const int A);
/**
 * @breif Замена 2-го элемента массива на наибольший максимальный отрицательный эллемент
 * @param Массив
 * @param Размер массива
 */
void replaceMaxNegative(int* arr, const size_t size);
/**
 * @breif Нахождение индекса наибольший максимальный отрицательный эллемент
 * @param Массив
 * @param Размер массива
 */
int findFirstNegative(const int* arr, const size_t size);
/**
 * @breif Суммирование нечетных эллементов
 * @param Массив
 * @param Размер массива
 * @return Сумма нечетных эллементов
 */
int sumOddNumber(const int* arr, const size_t size);

int* get_arr(const size_t size);

/**
 * @breif константы
 * @param RANDOM = 1
 * @param MANUAL = 2
 */
enum { RANDOM = 1, MANUAL };
/**
 * @breif точка входа
 * @return 0, если программа завершена успешно
 */
int main()
{
	printf("enter size ");
	size_t size = getSize();
	int* arr = get_arr(size);
	printf("%d random %d manual ", RANDOM, MANUAL);
	int choice = Value();
	switch (choice)
	{
	case RANDOM:
		fillRandom(arr, size);
		break;
	case MANUAL:
		fillArray(arr, size);
		break;
	default:
		printf("error");
		free(arr);
		exit(1);
		break;
	}

	printArray(arr, size);
	printf("\n%d", sumOddNumber(arr, size));
	printf("\nenter A = ");
	const int A = Value();
	printBiggerA(arr, size, A);
	int* copyArr = get_arr(size);
	replaceMaxNegative(copyArr, size);
	printf("\n");
	printArray(copyArr, size);
	free(arr);
	return 0;
}

int* get_arr(const size_t size)
{
	int* arr = malloc(size * sizeof(int));
	if (arr == NULL)
	{
		printf("ERROR");
		exit(1);
	}
	return arr;
}

int Value()
{
	int value = 0;
	if (!scanf_s("%d", &value))
	{
		printf("ERROR");
		abort();
	}
	return value;
}

size_t getSize()
{
	int value = Value();
	if (value <= 0)
	{
		printf("ERROR");
		abort();

	}
	return (size_t)value;
}

void fillArray(int* arr, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("enter arr[%d] = ", i);
		arr[i] = Value();

	}
}

void fillRandom(int* arr, const size_t size)
{
	srand(time(NULL));
	printf("diapozon start ");
	int start = Value();
	printf("diapozon end ");
	int end = Value();
	if (!(end > start))
	{
		printf("ERROR");
		exit(1);
	}
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = (rand() % (end - start + 1)) + start;
	}
}

void printArray(const int* arr, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
}

int sumOddNumber(const int* arr, const size_t size)
{
	int result = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 1)
		{
			result += arr[i];
		}
	}
	return result;
}

void printBiggerA(const int* arr, const size_t size, const int A)
{

	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] > A)
		{
			printf("%d ", i);
		}
	}
}

void replaceMaxNegative(int* arr, const size_t size)
{
	arr[2] = arr[findFirstNegative(arr, size);
}
int findFirstNegative(const int* arr, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] < 0)
		{
			return i;
		}
	}
}
