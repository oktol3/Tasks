#pragma once
#include "Generator.h"

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Генератор константного значения
         */
        class ConstGenerator : public Generator
        {
        private:
            /**
             * @brief Значение, которое возвращает генератор
             */
            int value;

        public:
            /**
             * @brief Конструктор
             * @param value значение, которое будет возвращать генератор
             */
            ConstGenerator(const int value);

            /**
             * @brief Вернуть заданное значение
             * @return значение, переданное в конструктор
             */
            int generate() override;
        };
    }
}
