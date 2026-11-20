#pragma once

#include <memory>
#include <string>

/**
 * @brief Абстрактный базовый класс для представления транспортного средства
 */
class Transport
{
protected:
    /**
     * @brief Уникальный идентификатор транспортного средства
     */
    std::string id;

    /**
     * @brief Название или модель транспортного средства
     */
    std::string name;

    /**
     * @brief Максимальная грузоподъемность в тоннах
     */
    double capacityTons;

    /**
     * @brief Средняя эксплуатационная скорость (км/ч)
     */
    double speedKmH;

    /**
     * @brief Тариф перевозки за один тонно-километр (руб.)
     */
    double ratePerTonKm;

    /**
     * @brief Проверка, что строка не пустая и не состоит только из пробельных символов
     * @param value Проверяемая строка
     * @param fieldName Название поля для формирования текста исключения
     */
    static void ValidateNonEmpty(const std::string& value, const std::string& fieldName);

    /**
     * @brief Сравнение двух вещественных чисел с заданной погрешностью
     * @param lhs Первое число
     * @param rhs Второе число
     * @return true, если числа равны с точностью 1e-6, иначе false
     */
    static bool AreEqual(const double lhs, const double rhs);

    /**
     * @brief Конструктор по умолчанию
     */
    Transport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор транспорта
     * @param name Название / модель транспорта
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     */
    Transport(const std::string& id,
              const std::string& name,
              const double capacityTons,
              const double speedKmH,
              const double ratePerTonKm);

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
     * @brief Виртуальный деструктор по умолчанию
     */
    virtual ~Transport() = default;

    /**
     * @brief Форматирование вещественного числа с двумя знаками после запятой
     * @param value Вещественное число
     * @return Отформатированная строка
     */
    static std::string FormatDouble(const double value);

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
    void SetCapacityTons(const double capacity);

    /**
     * @brief Получить среднюю скорость (км/ч)
     * @return Средняя скорость
     */
    double GetSpeedKmH() const;

    /**
     * @brief Установить среднюю скорость (км/ч)
     * @param speed Новая скорость
     */
    void SetSpeedKmH(const double speed);

    /**
     * @brief Получить тариф за тонно-километр
     * @return Тариф в рублях за тонно-километр
     */
    double GetRatePerTonKm() const;

    /**
     * @brief Установить тариф за тонно-километр
     * @param rate Новый тариф
     */
    void SetRatePerTonKm(const double rate);

    /**
     * @brief Получить вид (способ) доставки транспорта
     * @return Название вида транспорта
     */
    virtual std::string GetTransportType() const = 0;

    /**
     * @brief Полиморфное клонирование текущего объекта транспорта
     * @return Умный указатель на глубокую копию объекта
     */
    virtual std::unique_ptr<Transport> Clone() const = 0;

    /**
     * @brief Полиморфное сравнение с другим объектом транспорта
     * @param other Транспорт для сравнения
     * @return true, если объекты имеют одинаковый тип и равные поля
     */
    virtual bool Equals(const Transport& other) const = 0;

    /**
     * @brief Рассчитать транспортную составляющую стоимости перевозки груза
     * @param distanceKm Протяженность маршрута (км)
     * @param weightTons Масса груза (т)
     * @return Стоимость перевозки транспортом (руб.)
     */
    virtual double CalculateDeliveryCost(const double distanceKm, const double weightTons) const;

    /**
     * @brief Получить полную строковую информацию о транспортном средстве
     * @return Строка с подробным описанием транспорта
     */
    virtual std::string ToString() const;

    /**
     * @brief Получить краткую сводку о транспортном средстве
     * @return Краткая строка с описанием транспорта
     */
    virtual std::string GetSummary() const;

    /**
     * @brief Оператор сравнения базовых характеристик транспорта
     * @param other Транспорт для сравнения
     * @return true, если базовые поля и тип транспорта равны
     */
    bool operator==(const Transport& other) const;

    /**
     * @brief Оператор неравенства базовых характеристик транспорта
     * @param other Транспорт для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const Transport& other) const;
};
