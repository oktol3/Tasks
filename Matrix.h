#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Generator.h"

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Шаблонный класс двумерного массива (матрицы)
         * @tparam T тип хранимых элементов
         */
        template <typename T>
        class Matrix
        {
        private:
            /** 
             * @brief Внутреннее хранилище элементов (строки x столбцы)
             */
            std::vector<std::vector<T>> data;

            /**
             * @brief Количество строк
             */
            size_t rows;

            /**
             * @brief Количество столбцов
             */
            size_t cols;

        public:
            /**
             * @brief Конструктор по умолчанию
             */
            Matrix();

            /**
             * @brief Конструктор с размерами
             * @param rows количество строк
             * @param cols количество столбцов
             */
            Matrix(const size_t rows, const size_t cols);

            /**
             * @brief Конструктор с размерами и константным значением
             * @param rows количество строк
             * @param cols количество столбцов
             * @param value значение для заполнения всех элементов
             */
            Matrix(const size_t rows, const size_t cols, const Generator& gen);

            /**
             * @brief Конструктор копирования
             * @param other ссылка на копируемую матрицу
             */
            Matrix(const Matrix& other) = default;

            /**
             * @brief Конструктор перемещения
             * @param other ссылка на перемещаемую матрицу
             */
            Matrix(Matrix&& other) noexcept = default;

            /**
             * @brief Деструктор
             */
            ~Matrix() = default;

            /**
             * @brief Оператор присваивания копированием
             * @param other ссылка на присваиваемую матрицу
             * @return ссылка на текущий объект
             */
            Matrix& operator=(const Matrix& other) = default;

            /**
             * @brief Оператор присваивания перемещением
             * @param other ссылка на перемещаемую матрицу
             * @return ссылка на текущий объект
             */
            Matrix& operator=(Matrix&& other) noexcept = default;

            /**
             * @brief Оператор доступа по индексу (неконстантный)
             * @param index индекс строки
             * @return ссылка на строку матрицы
             */
            std::vector<T>& operator[](const size_t index);

            /**
             * @brief Оператор доступа по индексу (константный)
             * @param index индекс строки
             * @return константная ссылка на строку матрицы
             */
            const std::vector<T>& operator[](const size_t index) const;

            /**
             * @brief Оператор сдвига влево
             * @param shift количество удаляемых строк с начала
             * @return ссылка на текущий объект
             */
            Matrix& operator<<(const size_t shift);

            /**
             * @brief Оператор сдвига вправо
             * @param shift количество добавляемых пустых строк в начало
             * @return ссылка на текущий объект
             */
            Matrix& operator>>(const size_t shift);

            /**
             * @brief Заполнить матрицу с помощью генератора
             * @param gen ссылка на генератор значений
             */
            void fill(const Generator& gen);

            /**
             * @brief Получить количество строк
             * @return количество строк матрицы
             */
            size_t getRows() const { return rows; }

            /**
             * @brief Получить количество столбцов
             * @return количество столбцов матрицы
             */
            size_t getCols() const { return cols; }

            /**
             * @brief Представление матрицы в виде строки
             * @return строка вида "[ a, b ]\n[ c, d ]"
             */
            std::string toString() const;

            /**
             * @brief Вставить строку после указанной позиции
             * @param pos индекс строки, после которой вставить
             * @param row строка для вставки
             */
            void insertRow(const size_t pos, const std::vector<T>& row);
        };


        template <typename T>
        Matrix<T>::Matrix() : rows(0), cols(0) {}

        template <typename T>
        Matrix<T>::Matrix(const size_t rows, const size_t cols)
            : rows(rows), cols(cols), data(rows, std::vector<T>(cols, T{})) {
        }

        template <typename T>
        Matrix<T>::Matrix(const size_t rows, const size_t cols, const Generator& gen)
            : rows(rows), cols(cols), data(rows, std::vector<T>(cols, T{}))
        {
            fill(gen);
        }

        template <typename T>
        std::vector<T>& Matrix<T>::operator[](const size_t index)
        {
            if (index >= rows)
                throw std::out_of_range("Matrix row index out of range");
            return data[index];
        }

        template <typename T>
        const std::vector<T>& Matrix<T>::operator[](const size_t index) const
        {
            if (index >= rows)
                throw std::out_of_range("Matrix row index out of range");
            return data[index];
        }

        template <typename T>
        Matrix<T>& Matrix<T>::operator<<(const size_t shift)
        {
            for (size_t s = 0; s < shift && rows > 0; ++s)
            {
                data.erase(data.begin());
                --rows;
            }
            return *this;
        }

        template <typename T>
        Matrix<T>& Matrix<T>::operator>>(const size_t shift)
        {
            for (size_t s = 0; s < shift; ++s)
            {
                data.insert(data.begin(), std::vector<T>(cols, T{}));
                ++rows;
            }
            return *this;
        }

        template <typename T>
        void Matrix<T>::fill(const Generator& gen)
        {
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    data[i][j] = static_cast<T>(gen.generate());
        }

        template <typename T>
        std::string Matrix<T>::toString() const
        {
            std::ostringstream oss;
            for (size_t i = 0; i < rows; ++i)
            {
                oss << "[ ";
                for (size_t j = 0; j < cols; ++j)
                {
                    oss << data[i][j];
                    if (j + 1 < cols) oss << ", ";
                }
                oss << " ]";
                if (i + 1 < rows) oss << "\n";
            }
            return oss.str();
        }

        template <typename T>
        void Matrix<T>::insertRow(const size_t pos, const std::vector<T>& row)
        {
            if (pos >= rows) return;
            data.insert(data.begin() + pos + 1, row);
            ++rows;
        }
    }
}
