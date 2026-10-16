#include "CppUnitTest.h"

#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstGenerator.h"
#include "Task1.h"
#include "Task2.h"

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
    TEST_CLASS(MatrixTest)
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
         * @brief Проверка конструктора с генератором
         */
        TEST_METHOD(GeneratorConstructor_ShouldFillMatrix)
        {
            ConstGenerator gen(5);
            Matrix<int> m(2, 2, gen);

            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(2), m.getCols());
            Assert::AreEqual(5, m[0][0]);
            Assert::AreEqual(5, m[0][1]);
            Assert::AreEqual(5, m[1][0]);
            Assert::AreEqual(5, m[1][1]);
        }

        /**
         * @brief Проверка конструктора с IStreamGenerator
         */
        TEST_METHOD(GeneratorConstructor_WithStream_ShouldReadFromStream)
        {
            std::istringstream input("1 2 3 4");
            IStreamGenerator gen(input);
            Matrix<int> m(2, 2, gen);

            Assert::AreEqual(1, m[0][0]);
            Assert::AreEqual(2, m[0][1]);
            Assert::AreEqual(3, m[1][0]);
            Assert::AreEqual(4, m[1][1]);
        }

        /**
         * @brief Проверка конструктора копирования
         */
        TEST_METHOD(CopyConstructor_ShouldCreateDeepCopy)
        {
            ConstGenerator gen(7);
            Matrix<int> original(2, 2, gen);
            Matrix<int> copy(original);

            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original.getCols(), copy.getCols());
            Assert::AreEqual(original[0][0], copy[0][0]);

            original[0][0] = 99;
            Assert::AreEqual(99, original[0][0]);
            Assert::AreEqual(7, copy[0][0]);
        }

        /**
         * @brief Проверка оператора присваивания копированием
         */
        TEST_METHOD(CopyAssignment_ShouldCopyContent)
        {
            ConstGenerator gen(3);
            Matrix<int> original(2, 2, gen);
            Matrix<int> copy;
            copy = original;

            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original[0][0], copy[0][0]);
        }

        /**
         * @brief Проверка самоприсваивания
         */
        TEST_METHOD(SelfAssignment_ShouldNotChange)
        {
            ConstGenerator gen(3);
            Matrix<int> m(2, 2, gen);
            m = m;
            Assert::AreEqual(3, m[0][0]);
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
        }

        /**
         * @brief Проверка оператора доступа по индексу (неконстантный)
         */
        TEST_METHOD(IndexOperator_ShouldReturnMutableRow)
        {
            Matrix<int> m(2, 2, 7);
            Assert::AreEqual(7, m[0][0]);
            m[0][0] = 42;
            Assert::AreEqual(42, m[0][0]);
            Assert::AreEqual(7, m[1][1]);
        }

        /**
         * @brief Проверка константного оператора доступа
         */
        TEST_METHOD(IndexOperator_ConstObject_ShouldReturnConstRow)
        {
            ConstGenerator gen(9);
            const Matrix<int> m(2, 2, gen);
            Assert::AreEqual(9, m[0][0]);
            Assert::AreEqual(9, m[1][1]);
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
         * @brief Проверка константного оператора доступа с выходом за границы
         */
        TEST_METHOD(IndexOperator_ConstOutOfRange_ShouldThrow)
        {
            const Matrix<int> m(2, 2);
            auto func = [&m]() { m[5]; };
            Assert::ExpectException<std::out_of_range>(func);
        }

        /**
         * @brief Проверка сдвига влево (удаление строк)
         */
        TEST_METHOD(ShiftLeft_ShouldRemoveFirstRows)
        {
            ConstGenerator gen(1);
            Matrix<int> m(3, 2, gen);
            m << 1;
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(2), m.getCols());
        }

        /**
         * @brief Проверка сдвига влево больше, чем строк
         */
        TEST_METHOD(ShiftLeft_MoreThanRows_ShouldResultEmpty)
        {
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            m << 5;
            Assert::AreEqual(static_cast<size_t>(0), m.getRows());
        }

        /**
         * @brief Проверка сдвига влево на 0 строк
         */
        TEST_METHOD(ShiftLeft_Zero_ShouldNotChange)
        {
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            m << 0;
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(1, m[0][0]);
        }

        /**
         * @brief Проверка сдвига вправо (добавление пустых строк)
         */
        TEST_METHOD(ShiftRight_ShouldAddEmptyRows)
        {
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            m >> 1;
            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(0, m[0][0]);
            Assert::AreEqual(0, m[0][1]);
            Assert::AreEqual(1, m[1][0]);
        }

        /**
         * @brief Проверка сдвига вправо на 0 строк
         */
        TEST_METHOD(ShiftRight_Zero_ShouldNotChange)
        {
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            m >> 0;
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
        }

        /**
         * @brief Проверка строкового представления
         */
        TEST_METHOD(ToString_ShouldContainAllElements)
        {
            ConstGenerator gen(5);
            Matrix<int> m(2, 2, gen);
            std::string s = m.toString();
            Assert::IsTrue(s.find("5") != std::string::npos);
        }

        /**
         * @brief Проверка toString для пустой матрицы
         */
        TEST_METHOD(ToString_EmptyMatrix_ShouldBeEmpty)
        {
            Matrix<int> m;
            Assert::AreEqual(std::string(""), m.toString());
        }

        /**
         * @brief Проверка метода fill
         */
        TEST_METHOD(Fill_ShouldFillAllCells)
        {
            ConstGenerator gen(8);
            Matrix<int> m(2, 3);
            m.fill(gen);

            for (size_t i = 0; i < m.getRows(); ++i)
                for (size_t j = 0; j < m.getCols(); ++j)
                    Assert::AreEqual(8, m[i][j]);
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
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            std::vector<int> row = { 9, 9 };
            m.insertRow(0, row);

            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(9, m[1][0]);
            Assert::AreEqual(9, m[1][1]);
            Assert::AreEqual(1, m[2][0]);
        }

        /**
         * @brief Проверка вставки строки в конец
         */
        TEST_METHOD(InsertRow_AtLastPosition_Success)
        {
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            std::vector<int> row = { 5, 5 };
            m.insertRow(1, row);

            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(5, m[2][0]);
        }

        /**
         * @brief Проверка вставки с индексом за пределами — ничего не делается
         */
        TEST_METHOD(InsertRow_OutOfRange_ShouldNotChange)
        {
            ConstGenerator gen(1);
            Matrix<int> m(2, 2, gen);
            std::vector<int> row = { 5, 5 };
            m.insertRow(5, row);
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
        }

        /**
         * @brief Проверка работы с типом double
         */
        TEST_METHOD(DoubleMatrix_Success)
        {
            Matrix<double> m(2, 2);
            m[0][0] = 1.5;
            m[1][1] = 2.5;
            Assert::AreEqual(1.5, m[0][0]);
            Assert::AreEqual(2.5, m[1][1]);
        }

        /**
         * @brief Проверка работы с типом std::string
         */
        TEST_METHOD(StringMatrix_Success)
        {
            Matrix<std::string> m(2, 1);
            m[0][0] = "hello";
            m[1][0] = "world";
            Assert::AreEqual(std::string("hello"), m[0][0]);
            Assert::AreEqual(std::string("world"), m[1][0]);
        }
    };

    /**
     * @brief Тесты задачи Task1
     */
    TEST_CLASS(Task1Test)
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
         * @brief Максимум в последнем столбце
         */
        TEST_METHOD(MaxInLastColumn_ShouldReplaceWithLastIndex)
        {
            Matrix<int> m(1, 3);
            m[0][0] = 1; m[0][1] = 2; m[0][2] = 100;

            Task1 task(m);
            task.solve();

            Assert::AreEqual(2, task.getMatrix()[0][2]);
        }

        /**
         * @brief Максимум встречается несколько раз — заменяется первый (слева)
         */
        TEST_METHOD(MultipleMax_ShouldReplaceFirstOccurrence)
        {
            Matrix<int> m(1, 3);
            m[0][0] = 5; m[0][1] = 5; m[0][2] = 1;

            Task1 task(m);
            task.solve();

            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(5, task.getMatrix()[0][1]);
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

        /**
         * @brief Отрицательные значения
         */
        TEST_METHOD(NegativeValues_Success)
        {
            Matrix<int> m(1, 3);
            m[0][0] = -10; m[0][1] = -5; m[0][2] = -20;

            Task1 task(m);
            task.solve();

            // Максимум = -5 в столбце 1, заменяем на 1
            Assert::AreEqual(1, task.getMatrix()[0][1]);
        }
    };

    /**
     * @brief Тесты задачи Task2
     */
    TEST_CLASS(Task2Test)
    {
    public:
        /**
         * @brief Вставка строки 2, 4, 6, ... после строки с минимумом
         */
        TEST_METHOD(InsertEvenRowAfterMinRows)
        {
            Matrix<int> m(2, 3);
            m[0][0] = 1; m[0][1] = 5; m[0][2] = 3;
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
            m[0][0] = 1; m[0][1] = 5;
            m[1][0] = 9; m[1][1] = 8;
            m[2][0] = 7; m[2][1] = 1;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(5), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[1][1]);
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
            m[1][0] = 3; m[1][1] = 8;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[2][0]);
            Assert::AreEqual(4, task.getMatrix()[2][1]);
        }

        /**
         * @brief Минимум в первой строке — вставка сразу после неё
         */
        TEST_METHOD(InsertAfterFirstRow)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 1; m[0][1] = 9;
            m[1][0] = 5; m[1][1] = 7;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[1][1]);
        }

        /**
         * @brief Минимум в последней строке — вставка после неё
         */
        TEST_METHOD(InsertAfterLastRow)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 5; m[0][1] = 7;
            m[1][0] = 1; m[1][1] = 9;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[2][0]);
            Assert::AreEqual(4, task.getMatrix()[2][1]);
        }

        /**
         * @brief Одна строка — вставка после неё
         */
        TEST_METHOD(SingleRow_ShouldInsert)
        {
            Matrix<int> m(1, 2);
            m[0][0] = 1; m[0][1] = 9;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(2), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[1][1]);
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

        /**
         * @brief Отрицательный минимум
         */
        TEST_METHOD(NegativeMin_Success)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 5; m[0][1] = 7;
            m[1][0] = -3; m[1][1] = 9;

            Task2 task(m);
            task.solve();

            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());
            Assert::AreEqual(2, task.getMatrix()[2][0]);
            Assert::AreEqual(4, task.getMatrix()[2][1]);
        }
    };

    /**
     * @brief Тесты генераторов
     */
    TEST_CLASS(GeneratorTest)
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
         * @brief RandomGenerator с диапазоном из одного значения
         */
        TEST_METHOD(RandomGenerator_SingleValueRange_ShouldReturnSame)
        {
            RandomGenerator gen(5, 5);
            for (int i = 0; i < 10; ++i)
                Assert::AreEqual(5, gen.generate());
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

        /**
         * @brief IStreamGenerator с отрицательными числами
         */
        TEST_METHOD(IStreamGenerator_NegativeValues_Success)
        {
            std::istringstream input("-1 -2 -3");
            IStreamGenerator gen(input);

            Assert::AreEqual(-1, gen.generate());
            Assert::AreEqual(-2, gen.generate());
            Assert::AreEqual(-3, gen.generate());
        }

        /**
         * @brief ConstGenerator всегда возвращает одно и то же значение
         */
        TEST_METHOD(ConstGenerator_ShouldAlwaysReturnSameValue)
        {
            ConstGenerator gen(42);

            Assert::AreEqual(42, gen.generate());
            Assert::AreEqual(42, gen.generate());
            Assert::AreEqual(42, gen.generate());
        }

        /**
         * @brief ConstGenerator с отрицательным значением
         */
        TEST_METHOD(ConstGenerator_NegativeValue_Success)
        {
            ConstGenerator gen(-5);
            Assert::AreEqual(-5, gen.generate());
        }

        /**
         * @brief ConstGenerator с нулём
         */
        TEST_METHOD(ConstGenerator_Zero_Success)
        {
            ConstGenerator gen(0);
            Assert::AreEqual(0, gen.generate());
        }

        /**
         * @brief Полиморфизм — вызов через указатель на базовый класс
         */
        TEST_METHOD(Polymorphism_ThroughBasePointer_ShouldCallOverride)
        {
            std::unique_ptr<Generator> gen(new ConstGenerator(11));
            Assert::AreEqual(11, gen->generate());
            Assert::AreEqual(11, gen->generate());
        }

        /**
         * @brief Смена генератора через указатель базового класса
         */
        TEST_METHOD(Polymorphism_SwitchGenerator_Success)
        {
            std::unique_ptr<Generator> gen(new ConstGenerator(1));
            Assert::AreEqual(1, gen->generate());

            gen.reset(new ConstGenerator(2));
            Assert::AreEqual(2, gen->generate());
        }
    };
}
