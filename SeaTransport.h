#pragma once

#include "Transport.h"

/**
 * @brief Класс морского грузового транспорта
 */
class SeaTransport : public Transport
{
private:
    /**
     * @brief Контейнеровместимость морского судна (в единицах TEU)
     */
    int containerCapacityTeu;

    /**
     * @brief Фиксированный портовый сбор за рейс (руб.)
     */
    double portFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    SeaTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор морского судна
     * @param name Название морского судна
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     * @param containerCapacityTeu Контейнеровместимость (TEU)
     * @param portFee Портовый сбор (руб.)
     */
    SeaTransport(const std::string& id,
                 const std::string& name,
                 const double capacityTons,
                 const double speedKmH,
                 const double ratePerTonKm,
                 const int containerCapacityTeu,
                 const double portFee);

    /**
     * @brief Деструктор по умолчанию
     */
    ~SeaTransport() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    SeaTransport(const SeaTransport& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    SeaTransport& operator=(const SeaTransport& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    SeaTransport(SeaTransport&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    SeaTransport& operator=(SeaTransport&& other) noexcept;

    /**
     * @brief Получить контейнеровместимость (TEU)
     * @return Вместимость в TEU
     */
    int GetContainerCapacityTeu() const;

    /**
     * @brief Установить контейнеровместимость (TEU)
     * @param capacityTeu Новая контейнеровместимость
     */
    void SetContainerCapacityTeu(const int capacityTeu);

    /**
     * @brief Получить портовый сбор (руб.)
     * @return Сумма портового сбора
     */
    double GetPortFee() const;

    /**
     * @brief Установить портовый сбор (руб.)
     * @param fee Новый портовый сбор
     */
    void SetPortFee(const double fee);

    /**
     * @brief Получить вид транспорта ("Морской")
     * @return Строка "Морской"
     */
    std::string GetTransportType() const override;

    /**
     * @brief Создать полиморфную копию морского транспорта
     * @return Умный указатель на копию объекта
     */
    std::unique_ptr<Transport> Clone() const override;

    /**
     * @brief Полиморфное сравнение с другим объектом транспорта
     * @param other Объект транспорта для сравнения
     * @return true, если объекты равны
     */
    bool Equals(const Transport& other) const override;

    /**
     * @brief Рассчитать стоимость морской перевозки с учетом портового сбора
     * @param distanceKm Протяженность маршрута (км)
     * @param weightTons Масса груза (т)
     * @return Стоимость перевозки (руб.)
     */
    double CalculateDeliveryCost(const double distanceKm, const double weightTons) const override;

    /**
     * @brief Получить полное строковое описание морского судна
     * @return Строка с характеристиками
     */
    std::string ToString() const override;

    /**
     * @brief Оператор равенства двух объектов SeaTransport
     * @param other Объект для сравнения
     * @return true, если объекты равны
     */
    bool operator==(const SeaTransport& other) const;

    /**
     * @brief Оператор неравенства двух объектов SeaTransport
     * @param other Объект для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const SeaTransport& other) const;
};
