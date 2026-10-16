#include <iostream>
#include <memory>
#include <clocale>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

/**
 * @brief Способ заполнения матрицы
 */
enum class Choice
{
    Random = 1,     //случайными числами
    Keyboard = 2,   //с клавиатуры
    Constant = 3    //константным значением
};

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0, если программа выполнена корректно
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    size_t n = 0, m = 0;
    std::cout << "Введите размеры матрицы n m: ";
    std::cin >> n >> m;

    std::cout << "Выберите способ заполнения:\n" 
        << Choice::Random
        << " - случайными числами\n"
        << Choice::Keyboard
        << " - с клавиатуры\n"
        << Choice::Constant
        << "3 - константным значением\n"
        << "Ваш выбор: ";

    int input = 0;
    std::cin >> input;
    Choice choice = static_cast<Choice>(input);

    std::unique_ptr<Generator> gen;

    switch (choice)
    {
    case Choice::Random:
    {
        int minV = 0, maxV = 0;
        std::cout << "Введите min и max: ";
        std::cin >> minV >> maxV;
        gen = std::unique_ptr<Generator>(new RandomGenerator(minV, maxV));
        break;
    }
    case Choice::Keyboard:
    {
        gen = std::unique_ptr<Generator>(new IStreamGenerator(std::cin));
        std::cout << "Введите " << n * m << " чисел:\n";
        break;
    }
    case Choice::Constant:
    {
        int value = 0;
        std::cout << "Введите константу: ";
        std::cin >> value;
        gen = std::unique_ptr<Generator>(new ConstGenerator(value));
        break;
    }
    default:
    {
        std::cout << "Неверный выбор\n";
        exit(1);
        break;
    }
    }
    Matrix<int> matrix(n, m, *gen);

    std::cout << "\nИсходная матрица:\n" << matrix.toString() << "\n\n";

    // Задача 1
    Matrix<int> m1 = matrix;
    Task1 task1(m1);
    std::cout << "Задача 1: " << task1.description() << "\n";
    task1.solve();
    std::cout << task1.getMatrix().toString() << "\n\n";

    // Задача 2
    Matrix<int> m2 = matrix;
    Task2 task2(m2);
    std::cout << "Задача 2: " << task2.description() << "\n";
    task2.solve();
    std::cout << task2.getMatrix().toString() << "\n";

    return 0;
}
