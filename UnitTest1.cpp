#include "CppUnitTest.h"

#include "../ConsoleApplication18/Matrix.h"
#include "../ConsoleApplication18/RandomGenerator.h"
#include "../ConsoleApplication18/Task1.h"
#include "../ConsoleApplication18/Task2.h"

#include <sstream>
#include <string>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace MatrixTests
{
    /**
     * @brief Тесты класса Matrix
     */
    TEST_CLASS(MatrixTests)
    {
    public:
        /**
         * @brief Проверка конструктора по умолчанию
         */
        TEST_METHOD(DefaultConstructor_ShouldCreateEmptyMatrix)
        {
            Matrix<int> m;
            Assert::AreEqual(static_cast<size_t>(0), m.getRows());
            Assert::AreEqual(static_cast<size_t>(0), m.getCols());
            Assert::AreEqual(std::string(""), m.toString());
        }

        /**
         * @brief Проверка конструктора с размерами (нулевая матрица)
         */
        TEST_METHOD(SizeConstructor_ShouldCreateZeroMatrix)
        {
            Matrix<int> m(2, 3);
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(3), m.getCols());
            Assert::AreEqual(0, m[0][0]);
            Assert::AreEqual(0, m[0][2]);
            Assert::AreEqual(0, m[1][0]);
            Assert::AreEqual(0, m[1][2]);
        }

        /**
         * @brief Проверка конструктора с константным значением
         */
        TEST_METHOD(ValueConstructor_ShouldFillWithValue)
        {
            Matrix<int> m(2, 2, 5);
            Assert::AreEqual(5, m[0][0]);
            Assert::AreEqual(5, m[0][1]);
            Assert::AreEqual(5, m[1][0]);
            Assert::AreEqual(5, m[1][1]);
        }

        /**
         * @brief Проверка конструктора копирования
         */
        TEST_METHOD(CopyConstructor_ShouldCreateDeepCopy)
        {
            Matrix<int> original(2, 2, 7);
            Matrix<int> copy(original);

            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original.getCols(), copy.getCols());
            Assert::AreEqual(original[0][0], copy[0][0]);

            // Меняем оригинал — копия не должна измениться
            original[0][0] = 99;
            Assert::AreEqual(99, original[0][0]);
            Assert::AreEqual(7, copy[0][0]);
        }

        /**
         * @brief Проверка оператора присваивания копированием
         */
        TEST_METHOD(CopyAssignment_ShouldCopyContent)
        {
            Matrix<int> original(2, 2, 3);
            Matrix<int> copy;
            copy = original;

            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original[0][0], copy[0][0]);

            // Самоприсваивание
            copy = copy;
            Assert::AreEqual(3, copy[0][0]);
        }

        /**
         * @brief Проверка оператора доступа по индексу
         */
        TEST_METHOD(IndexOperator_ShouldReturnRow)
        {
            Matrix<int> m(2, 2, 7);
            Assert::AreEqual(7, m[0][0]);
            m[0][0] = 42;
            Assert::AreEqual(42, m[0][0]);
            Assert::AreEqual(7, m[1][1]);
        }

        /**
         * @brief Проверка выхода за границы при доступе по индексу
         */
        TEST_METHOD(IndexOperator_OutOfRange_ShouldThrow)
        {
            Matrix<int> m(2, 2);
            auto func = [&m]() { m[5]; };
            Assert::ExpectException<std::out_of_range>(func);
        }

        /**
         * @brief Проверка сдвига влево (удаление строк)
         */
        TEST_METHOD(ShiftLeft_ShouldRemoveFirstRows)
        {
            Matrix<int> m(3, 2, 1);
            m << 1;
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(2), m.getCols());
        }

        /**
         * @brief Проверка сдвига влево на количество больше, чем строк
         */
        TEST_METHOD(ShiftLeft_MoreThanRows_ShouldResultEmpty)
        {
            Matrix<int> m(2, 2, 1);
            m << 5;
            Assert::AreEqual(static_cast<size_t>(0), m.getRows());
        }

        /**
         * @brief Проверка сдвига вправо (добавление пустых строк)
         */
        TEST_METHOD(ShiftRight_ShouldAddEmptyRows)
        {
            Matrix<int> m(2, 2, 1);
            m >> 1;
            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(0, m[0][0]);
            Assert::AreEqual(0, m[0][1]);
            Assert::AreEqual(1, m[1][0]);
        }

        /**
         * @brief Проверка строкового представления
         */
        TEST_METHOD(ToString_ShouldContainAllElements)
        {
            Matrix<int> m(2, 2, 5);
            std::string s = m.toString();
            Assert::IsTrue(s.find("5") != std::string::npos);
        }

        /**
         * @brief Проверка заполнения через IStreamGenerator
         */
        TEST_METHOD(Fill_WithIStreamGenerator_ShouldFillFromStream)
        {
            std::istringstream input("1 2 3 4");
            IStreamGenerator gen(input);
            Matrix<int> m(2, 2);
            m.fill(gen);

            Assert::AreEqual(1, m[0][0]);
            Assert::AreEqual(2, m[0][1]);
            Assert::AreEqual(3, m[1][0]);
            Assert::AreEqual(4, m[1][1]);
        }

        /**
         * @brief Проверка вставки строки
         */
        TEST_METHOD(InsertRow_ShouldInsertAfterPosition)
        {
            Matrix<int> m(2, 2, 1);
            std::vector<int> row = { 9, 9 };
            m.insertRow(0, row);

            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(9, m[1][0]);
            Assert::AreEqual(9, m[1][1]);
            Assert::AreEqual(1, m[2][0]);
        }
    };

    /**
     * @brief Тесты задачи Task1
     */
    TEST_CLASS(Task1Tests)
    {
    public:
        /**
         * @brief Замена максимума на номер столбца
         */
        TEST_METHOD(ReplaceMaxWithColumnIndex)
        {
            Matrix<int> m(2, 3);
            m[0][0] = 1; m[0][1] = 5; m[0][2] = 3;
            m[1][0] = 9; m[1][1] = 2; m[1][2] = 4;

            Task1 task(m);
            task.solve();

            Assert::AreEqual(1, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[1][0]);
            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(3, task.getMatrix()[0][2]);
            Assert::AreEqual(2, task.getMatrix()[1][1]);
            Assert::AreEqual(4, task.getMatrix()[1][2]);
        }

        /**
         * @brief Максимум в первом столбце — заменяется на 0
         */
        TEST_METHOD(MaxInFirstColumn_ShouldReplaceWithZero)
        {
            Matrix<int> m(1, 3);
            m[0][0] = 100; m[0][1] = 1; m[0][2] = 2;

            Task1 task(m);
            task.solve();

            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(1, task.getMatrix()[0][1]);
            Assert::AreEqual(2, task.getMatrix()[0][2]);
        }

        /**
         * @brief Описание задачи не пустое
         */
        TEST_METHOD(Description_ShouldNotBeEmpty)
        {
            Matrix<int> m(1, 1);
            Task1 task(m);
            Assert::IsFalse(task.description().empty());
        }

        /**
         * @brief Работа с пустой матрицей
         */
        TEST_METHOD(EmptyMatrix_ShouldNotChange)
        {
            Matrix<int> m;
            Task1 task(m);
            task.solve();
            Assert::AreEqual(static_cast<size_t>(0), task.getMatrix().getRows());
        }
    };

    /**
     * @brief Тесты задачи Task2
     */
    TEST_CLASS(Task2Tests)
    {
    public:
        /**
         * @brief Вставка строки 2, 4, 6, ... после строки с минимумом
         */
        TEST_METHOD(InsertEvenRowAfterMinRows)
        {
            Matrix<int> m(2, 3);
            m[0][0] = 1; m[0][1] = 5; m[0][2] = 3;  // минимум = 1 здесь
            m[1][0] = 9; m[1][1] = 2; m[1][2] = 4;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[1][1]);
            Assert::AreEqual(6, task.getMatrix()[1][2]);
        }

        /**
         * @brief Минимум в нескольких строках — вставка после каждой
         */
        TEST_METHOD(InsertAfterMultipleRowsWithMin)
        {
            Matrix<int> m(3, 2);
            m[0][0] = 1; m[0][1] = 5;  // содержит минимум (1)
            m[1][0] = 9; m[1][1] = 8;  // нет минимума
            m[2][0] = 7; m[2][1] = 1;  // содержит минимум (1)

            Task2 task(m);
            task.solve();

            // Было 3 строки, стало 5 (после 0-й и 2-й)
            Assert::AreEqual(static_cast<size_t>(5), task.getMatrix().getRows());
            // После 0-й строки: 2, 4
            Assert::AreEqual(2, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[1][1]);
            // После 2-й (теперь она с индексом 4): 2, 4
            Assert::AreEqual(2, task.getMatrix()[4][0]);
            Assert::AreEqual(4, task.getMatrix()[4][1]);
        }

        /**
         * @brief Минимум только в одной строке
         */
        TEST_METHOD(InsertAfterSingleRowWithMin)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 5; m[0][1] = 4;
            m[1][0] = 3; m[1][1] = 8;  // минимум = 3

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[2][0]);
            Assert::AreEqual(4, task.getMatrix()[2][1]);
        }

        /**
         * @brief Описание задачи не пустое
         */
        TEST_METHOD(Description_ShouldNotBeEmpty)
        {
            Matrix<int> m(1, 1);
            Task2 task(m);
            Assert::IsFalse(task.description().empty());
        }

        /**
         * @brief Работа с пустой матрицей
         */
        TEST_METHOD(EmptyMatrix_ShouldNotChange)
        {
            Matrix<int> m;
            Task2 task(m);
            task.solve();
            Assert::AreEqual(static_cast<size_t>(0), task.getMatrix().getRows());
        }
    };

    /**
     * @brief Тесты генераторов
     */
    TEST_CLASS(GeneratorTests)
    {
    public:
        /**
         * @brief RandomGenerator возвращает значение в диапазоне
         */
        TEST_METHOD(RandomGenerator_ShouldReturnValueInRange)
        {
            RandomGenerator gen(1, 10);
            for (int i = 0; i < 100; ++i)
            {
                int v = gen.generate();
                Assert::IsTrue(v >= 1 && v <= 10);
            }
        }

        /**
         * @brief IStreamGenerator считывает числа из потока
         */
        TEST_METHOD(IStreamGenerator_ShouldReadFromStream)
        {
            std::istringstream input("42 7 13");
            IStreamGenerator gen(input);

            Assert::AreEqual(42, gen.generate());
            Assert::AreEqual(7, gen.generate());
            Assert::AreEqual(13, gen.generate());
        }
    };
}
