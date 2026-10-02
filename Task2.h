#pragma once
#include "Exercise.h"
#include "Matrix.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Задача 2
         */
        class Task2 : public Exercise
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
            Task2(Matrix<int> matrix);

            /**
             * @brief Выполнить вставку строк
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
