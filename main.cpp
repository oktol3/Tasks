#include <iostream>
#include <memory>
#include <clocale>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

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

    Matrix<int> matrix(n, m);

    std::cout << "Выберите способ заполнения:\n"
        << "1 - случайными числами\n"
        << "2 - с клавиатуры\n"
        << "Ваш выбор: ";
    int choice = 0;
    std::cin >> choice;

    std::unique_ptr<Generator> gen;
    if (choice == 1)
    {
        int minV = 0, maxV = 0;
        std::cout << "Введите min и max: ";
        std::cin >> minV >> maxV;
        gen = std::make_unique<RandomGenerator>(minV, maxV);
    }
    else
    {
        gen = std::make_unique<IStreamGenerator>(std::cin);
        std::cout << "Введите " << n * m << " чисел:\n";
    }

    matrix.fill(*gen);

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
