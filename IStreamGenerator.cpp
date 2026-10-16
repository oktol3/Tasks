#include "IStreamGenerator.h"

/**
 * @brief Конструктор
 * @param in поток ввода
 */
miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in{ in }
{
}

/**
 * @brief Считать очередное число из потока
 * @return считанное целое число
 */
int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;
    this->in >> value;
    return value;
}
