#include "ConstGenerator.h"

/**
 * @brief Конструктор
 * @param value значение, которое будет возвращать генератор
 */
miit::algebra::ConstGenerator::ConstGenerator(const int value)
    : value{ value }
{
}

/**
 * @brief Вернуть заданное значение
 * @return значение, переданное в конструктор
 */
int miit::algebra::ConstGenerator::generate()
{
    return this->value;
}
