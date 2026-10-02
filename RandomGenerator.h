#pragma once
#include "Generator.h"
#include <random>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Генератор случайных целых чисел
         */
        class RandomGenerator : public Generator
        {
        private:
            /**
             * @brief Распределение для генерации чисел в диапазоне
             */
            std::uniform_int_distribution<int> distribution;

            /**
             * @brief Генератор псевдослучайных чисел
             */
            std::mt19937 generator;

        public:
            /**
             * @brief Конструктор
             * @param min нижняя граница диапазона (включительно)
             * @param max верхняя граница диапазона (включительно)
             */
            RandomGenerator(const int min, const int max);

            /**
             * @brief Сгенерировать случайное число
             * @return случайное число из диапазона [min, max]
             */
            int generate() override;
        };
    }
}
