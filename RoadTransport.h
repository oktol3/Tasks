#pragma once

#include <string>

/**
 * @brief Абстрактный базовый класс для представления транспортного средства
 */
class Transport
{
protected:
    std::string id;
    std::string name;
    double capacityTons;
    double speedKmH;
    double ratePerTonKm;

    /**
     * @brief Проверка, что строка не пустая и не состоит только из пробелов
     * @param value Проверяемая строка
     * @param fieldName Название поля для текста исключения
     */
    static void ValidateNonEmpty(const std::string& value, const std::string& fieldName);

    /**
     * @brief Проверка равенства двух вещественных чисел с заданной точностью
     * @param lhs Первое число
     * @param rhs Второе число
     * @return true, если числа равны с точностью 1e-6
     */
    static bool AreEqual(double lhs, double rhs);

    /**
     * @brief Конструктор по умолчанию (для классов-наследников)
     */
    Transport();

    /**
     * @brief Конструктор с параметрами (для классов-наследников)
     * @param id Идентификатор транспорта
     * @param name Название / модель транспорта
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     */
    Transport(const std::string& id,
        const std::string& name,
        double capacityTons,
        double speedKmH,
        double ratePerTonKm);

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    Transport(const Transport& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    Transport& operator=(const Transport& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    Transport(Transport&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    Transport& operator=(Transport&& other) noexcept;

public:
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Transport() = default;

    /**
     * @brief Форматирование вещественного числа с двумя знаками после запятой
     * @param value Вещественное число
     * @return Строковое представление числа
     */
    static std::string FormatDouble(double value);

    /**
     * @brief Получить идентификатор транспорта
     * @return Константная ссылка на идентификатор
     */
    const std::string& GetId() const;

    /**
     * @brief Установить идентификатор транспорта
     * @param newId Новый идентификатор
     */
    void SetId(const std::string& newId);

    /**
     * @brief Получить название транспорта
     * @return Константная ссылка на название
     */
    const std::string& GetName() const;

    /**
     * @brief Установить название транспорта
     * @param newName Новое название
     */
    void SetName(const std::string& newName);

    /**
     * @brief Получить грузоподъемность (т)
     * @return Грузоподъемность в тоннах
     */
    double GetCapacityTons() const;

    /**
     * @brief Установить грузоподъемность (т)
     * @param capacity Новая грузоподъемность
     */
    void SetCapacityTons(double capacity);

    /**
     * @brief Получить среднюю скорость (км/ч)
     * @return Средняя скорость
     */
    double GetSpeedKmH() const;

    /**
     * @brief Установить среднюю скорость (км/ч)
     * @param speed Новая скорость
     */
    void SetSpeedKmH(double speed);

    /**
     * @brief Получить тариф за тонно-километр
     * @return Тариф (руб. / т*км)
     */
    double GetRatePerTonKm() const;

    /**
     * @brief Установить тариф за тонно-километр
     * @param rate Новый тариф
     */
    void SetRatePerTonKm(double rate);

    /**
     * @brief Получить тип (способ) доставки транспорта
     * @return Название вида транспорта (воздушный, морской и т. д.)
     */
    virtual std::string GetTransportType() const = 0;

    /**
     * @brief Рассчитать транспортную составляющую стоимости перевозки груза
     * @param distanceKm Расстояние маршрута (км)
     * @param weightTons Вес груза (т)
     * @return Стоимость перевозки транспортом
     */
    virtual double CalculateDeliveryCost(double distanceKm, double weightTons) const;

    /**
     * @brief Полная строковая информация о транспортном средстве
     * @return Строка с описанием транспорта
     */
    virtual std::string ToString() const;

    /**
     * @brief Краткая сводка о транспортном средстве
     * @return Краткая строка с описанием транспорта
     */
    virtual std::string GetSummary() const;

    /**
     * @brief Оператор сравнения базовых полей транспорта
     * @param other Объект для сравнения
     * @return true, если объекты равны
     */
    bool operator==(const Transport& other) const;

    /**
     * @brief Оператор неравенства
     * @param other Объект для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const Transport& other) const;
};
