#pragma once
#include "point.h"

/**
 * @brief   класс Вектор в трехмерном пространстве
 * @details Вектор задается двумя точками класса point
 */
class vector
{
private:
    /**
     * @breif начальная точка вектора
     */
    point A;
    /**
     * @breif конечная точка вектора
     */
    point B;

public:

    /**
     * @brief   Конструктор с параметрами
     * @param   X - начальная точка вектора
     * @param   Y - конечная точка вектора
     */
    vector(const point& X = point(0, 0, 0), const point& Y = point(0, 0, 0));

    /**
     * @brief   Конструктор копирования
     * @param   other - ссылка на копируемый объект
     */
    vector(const vector& other);

    /**
     * @brief   Оператор присваивания копированием
     * @param   other - ссылка на присваиваемый объект
     * @return  ссылка на текущий объект (для цепочечных операций)
     */
    vector& operator=(const vector& other);

    /**
     * @brief   Конструктор перемещения
     * @param   other - ссылка на rvalue перемещаемого объекта
     */
    vector(vector&& other) noexcept;

    /**
     * @brief   Оператор присваивания перемещением
     * @param   other - ссылка на rvalue перемещаемого объекта
     * @return  ссылка на текущий объект
     */
    vector& operator=(vector&& other) noexcept;

    /**
     * @brief   Деструктор
     */
    ~vector();

    /**
     * @brief   Оператор равенства векторов
     * @param   other - ссылка на сравниваемый вектор
     * @return  true - векторы равны, false - не равны
     */
    bool operator==(const vector& other) const;

    /**
     * @brief   Оператор неравенства векторов
     * @param   other - ссылка на сравниваемый вектор
     * @return  true - векторы не равны, false - равны
     */
    bool operator!=(const vector& other) const;

    /**
     * @brief   Оператор сложения векторов
     * @param   other - ссылка на второй вектор
     * @return  новый вектор, равный сумме текущего и other
     */
    vector operator+(const vector& other) const;

    /**
     * @brief   Оператор вычитания векторов
     * @param   other - ссылка на вычитаемый вектор
     * @return  новый вектор, равный разности текущего и other
     */
    vector operator-(const vector& other) const;

    /**
     * @brief   Оператор умножения вектора на скаляр
     * @param   scalar - вещественное число
     * @return  новый вектор, умноженный на scalar
     */
    vector operator*(double scalar) const;

    /**
     * @brief   Дружественная функция для умножения скаляра на вектор
     * @param   scalar - вещественное число
     * @param   v      - ссылка на вектор
     * @return  вектор, умноженный на скаляр
     */
    friend vector operator*(double scalar, const vector& v);

    /**
     * @brief   Получить координату X (i) вектора
     * @return  координата по оси X (разность B.x - A.x)
     */
    double i() const;

    /**
     * @brief   Получить координату Y (j) вектора
     * @return  координата по оси Y (разность B.y - A.y)
     */
    double j() const;

    /**
     * @brief   Получить координату Z (k) вектора
     * @return  координата по оси Z (разность B.z - A.z)
     */
    double k() const;
};
