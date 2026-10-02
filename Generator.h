#pragma once

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Абстрактный генератор значений
         */
        class Generator
        {
        public:
            /**
             * @brief Виртуальный деструктор
             */
            virtual ~Generator() = default;

            /**
             * @brief Сгенерировать очередное значение
             * @return сгенерированное целое число
             */
            virtual int generate() = 0;
        };
    }
}
