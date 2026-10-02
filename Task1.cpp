#include "Task1.h"

/**
 * @brief Конструктор
 * @param matrix матрица, с которой работаем
 */
miit::algebra::Task1::Task1(Matrix<int> matrix)
    : matrix(std::move(matrix))
{
}

/**
 * @brief Заменить максимумы в каждой строке номером столбца
 */
void miit::algebra::Task1::solve()
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        int maxVal = matrix[i][0];
        size_t maxCol = 0;

        for (size_t j = 1; j < matrix.getCols(); ++j)
        {
            if (matrix[i][j] > maxVal)
            {
                maxVal = matrix[i][j];
                maxCol = j;
            }
        }

        matrix[i][maxCol] = static_cast<int>(maxCol);
    }
}

/**
 * @brief Описание задачи
 * @return строка с описанием
 */
std::string miit::algebra::Task1::description() const
{
    return "Заменить максимальный элемент каждой строки номером столбца, в котором он находится";
}
