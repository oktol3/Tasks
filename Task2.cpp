#include "Task2.h"

/**
 * @brief Конструктор
 * @param matrix матрица, с которой работаем
 */
miit::algebra::Task2::Task2(Matrix<int> matrix)
    : matrix(std::move(matrix))
{
}

/**
 * @brief Выполнить вставку строк
 */
void miit::algebra::Task2::solve()
{
    if (matrix.getRows() == 0 || matrix.getCols() == 0) return;

    // 1. Находим минимальный элемент
    int minVal = matrix[0][0];
    for (size_t i = 0; i < matrix.getRows(); ++i)
        for (size_t j = 0; j < matrix.getCols(); ++j)
            if (matrix[i][j] < minVal) minVal = matrix[i][j];

    // 2. Формируем строку 2, 4, 6, ... длины cols
    std::vector<int> evenRow(matrix.getCols());
    for (size_t j = 0; j < matrix.getCols(); ++j)
        evenRow[j] = static_cast<int>((j + 1) * 2);

    // 3. Идём с конца, чтобы вставка не сбила индексы
    for (size_t i = matrix.getRows(); i-- > 0; )
    {
        bool hasMin = false;
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            if (matrix[i][j] == minVal)
            {
                hasMin = true;
                break;
            }
        }
        if (hasMin)
        {
            matrix.insertRow(i, evenRow);
        }
    }
}

/**
 * @brief Описание задачи
 * @return строка с описанием
 */
std::string miit::algebra::Task2::description() const
{
    return "Вставить после всех строк, содержащих минимальный элемент, строку 2, 4, 6, ...";
}
