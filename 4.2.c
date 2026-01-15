/**
 * @brief Заполняет массив случайными числами в пределах введённого пользователем диапазона
 * @param arr массив
 * @param size размер массива
 */
void fillRandom(int* arr, const size_t size);

/**
 * @brief Создаёт копию массива
 * @param arr массив
 * @param size размер массива
 * @return полученный массив
 */
int* copyArray(const int* arr, const size_t size);

/**
 * @brief Заменяет второй элемент массива на максимальный среди отрицательных
 * @param arr массив
 * @param Copyarr копия массива
 * @param size размер массива
 */
void replaceMaxNegative(int* copyArr, const size_t size);

/**
 * @brief ищет единицу в числе
 * @param сopyarr копия массива
 */
bool OneFound(int* copyArr);

/**
 * @brief вставляет число К перед элеменами в которых есть единица 
 * @param сopyarr копия массива
 * @param size размер массива
 */
int* InsertK(int* copyArr, const size_t size);



/**
 * @brief Формирует новый массив А на основе элементов старого массива D.
 * @param Copyarr копия массива
 * @param size размер массива
 */
void NewArrayA(int* copyArr, const size_t size);


/**
 * @brief RANDOM - заполнение массива случайными числами в пределах введённого пользователем диапазона
 * @brief MANUAL - заполнение массива вручную
 */
enum { RANDOM = 1, MANUAL };


/**
 * @brief Точка входа в программу
 * @return 0, если программа выполнена корректно, иначе 1.
 */
int main()
{
    size_t size = getSize("Введите размер массива:  ");
    int* arr = malloc(size * sizeof(int));

    if (arr == NULL)
    {
        printf("error");
        exit(1);
    }

    printf("Выберите способ заполнения массива:\n""%d-случайными числами %d-вручную ", RANDOM, MANUAL);
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
    }


    printArray(arr, size);
    int* copyArr = copyArray(arr, size);

    replaceMaxNegative(copyArr, size);
    printArray(copyArr, size);

    InsertK(copyArr, size);


    NewArrayA(copyArr, size);


    free(copyArr);
    free(arr);

    return 0;
}


int Value()
{
    int value = 0;
    if (!scanf_s("%d", &value))
    {
        fprintf(stderr, "Error\n");
        exit(1);
    }
    return value;
}


size_t getSize(char* message)
{
    printf("%s", message);
    int value = Value();
    if (value <= 0)
    {
        fprintf(stderr, "Error");
        exit(1);
    }
    return (size_t)value;
}



void fillArray(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("Введите A = ");
        arr[i] = Value();
    }
}



void printArray(int* arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



void fillRandom(int* arr, const size_t size)
{
    printf("начальное значение диапазона: ");
    const int start = Value();
    printf("конечное значение диапазона: ");
    const int end = Value();
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % (end - start + 1)) + start;
    }
}


int* copyArray(const int* arr, const size_t size)
{
    int* copyArr = malloc(sizeof(int) * size);

    if (copyArr == NULL)
    {
        fprintf(stderr, "Error");
        exit(1);
    }

    for (size_t i = 0; i < size; i++)
    {
        copyArr[i] = arr[i];
    }
    return copyArr;
}


void replaceMaxNegative(int* copyArr, const size_t size)
{
    int minNegativeElement = INT_MIN;
    size_t minIndex = 0;
    int SecondElem = 0;
    bool FindNegative = false;

    for (size_t i = 0; i < size; i++)
    {
        if ((copyArr[i] > minNegativeElement) && (copyArr[i] < 0)) {
            minNegativeElement = copyArr[i];
            FindNegative = true;
            minIndex = i;
        }
    }
    if (FindNegative != true) {
        printf("Отрицательных элементов элементов не найдено, текущий массив: ");
    }

    else {
        printf("Замена произведена: ");
        copyArr[1] = minNegativeElement;
    }
}

bool OneFound(int* copyArr) {
    bool OneFound = false;
    int Number = abs(copyArr);
    while (Number > 0) {
        if (Number % 10 == 1) return true;
        Number /= 10;
    }
    return false;
}

int* InsertK(int* copyArr, const size_t size) {
    printf("Введите значение K: ");
    int K = Value();

    size_t count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (OneFound(copyArr[i]) == true)
        {
            count++;
        }
    }
    if (count == 0)
    {
        printf("Элементов, в которых есть цифра 1 нет. Текущий массив: ");
        return copyArr;
    }

    size_t newSize = size + count;
    int* newArr = malloc(newSize * sizeof(int));

    if (newArr == NULL)
    {
        printf("Error\n");
        exit(1);
    }

    size_t j = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (OneFound(copyArr[i]) == true)
        {
            newArr[j++] = K;
            newArr[j++] = copyArr[i];
        }

        else
        {
            newArr[j++] = copyArr[i];
        }
    }

    printf("Новый массив с К: ");
    printArray(newArr, newSize);

    free(newArr);
    return newArr;

}


void NewArrayA(int* copyArr, const size_t size) {
    if (size == 0) {
        printf("Массив D пуст, нельзя сформировать новый массив!\n");
        abort();
    }

    int* A = (int*)malloc(size * sizeof(int));
    if (A == NULL) {
        fprintf(stderr, "Error");
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        int Num = (int)i;
        if (Num % 2 == 0) {
            A[i] = pow(copyArr[i],2);
        }
        else {
            A[i] = copyArr[i]/Num;
        }
    }

    printf("Массив А: ");
    printArray(A, size);
    free(A);
}
