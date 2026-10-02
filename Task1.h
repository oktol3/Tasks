#pragma once
#include "Exercise.h"
#include "Matrix.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Задача 1
         */
        class Task1 : public Exercise
        {
        private:
            /**
             * @brief Матрица, с которой работает задача
             */
            Matrix<int> matrix;

        public:
            /**
             * @brief Конструктор
             * @param matrix матрица, с которой работаем
             */
            Task1(Matrix<int> matrix);

            /**
             * @brief Заменить максимумы в каждой строке номером столбца
             */
            void solve() override;

            /**
             * @brief Описание задачи
             * @return строка с описанием
             */
            std::string description() const override;

            /**
             * @brief Получить матрицу
             * @return константная ссылка на матрицу
             */
            const Matrix<int>& getMatrix() const { return matrix; }
        };
    }
}