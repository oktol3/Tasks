#pragma once
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Абстрактное упражнение (задача)
         */
        class Exercise
        {
        public:
            /**
             * @brief Виртуальный деструктор
             */
            virtual ~Exercise() = default;

            /**
             * @brief Решить задачу
             */
            virtual void solve() = 0;

            /**
             * @brief Получить текстовое описание задачи
             * @return строка с описанием
             */
            virtual std::string description() const = 0;
        };
    }
}