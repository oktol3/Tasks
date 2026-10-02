#pragma once
#include "Generator.h"
#include <iostream>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Генератор значений из потока ввода
         */
        class IStreamGenerator : public Generator
        {
        private:
            /**
             * @brief Ссылка на поток ввода
             */
            std::istream& in;

        public:
            /**
             * @brief Конструктор
             * @param in поток ввода (по умолчанию std::cin)
             */
            IStreamGenerator(std::istream& in = std::cin);

            /**
             * @brief Считать очередное число из потока
             * @return считанное целое число
             */
            int generate() override;
        };
    }
}
