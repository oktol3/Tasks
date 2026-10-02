#include "RandomGenerator.h"

/**
 * @brief Конструктор
 * @param min нижняя граница диапазона (включительно)
 * @param max верхняя граница диапазона (включительно)
 */
miit::algebra::RandomGenerator::RandomGenerator(const int min, const int max)
{
    this->generator = std::mt19937(std::random_device{}());
    this->distribution = std::uniform_int_distribution<int>(min, max);
}

/**
 * @brief Сгенерировать случайное число
 * @return случайное число из диапазона [min, max]
 */
int miit::algebra::RandomGenerator::generate()
{
    return this->distribution(this->generator);
}#include "RandomGenerator.h"

/**
 * @brief Êîíñòðóêòîð
 * @param min íèæíÿÿ ãðàíèöà äèàïàçîíà (âêëþ÷èòåëüíî)
 * @param max âåðõíÿÿ ãðàíèöà äèàïàçîíà (âêëþ÷èòåëüíî)
 */
miit::algebra::RandomGenerator::RandomGenerator(const int min, const int max)
{
    this->generator = std::mt19937(std::random_device{}());
    this->distribution = std::uniform_int_distribution<int>(min, max);
}

/**
 * @brief Ñãåíåðèðîâàòü ñëó÷àéíîå ÷èñëî
 * @return ñëó÷àéíîå ÷èñëî èç äèàïàçîíà [min, max]
 */
int miit::algebra::RandomGenerator::generate()
{
    return this->distribution(this->generator);
}
