#pragma once

#include "Transport.h"

/**
 * @brief Класс автомобильного грузового транспорта
 */
class RoadTransport : public Transport
{
private:
    /**
     * @brief Количество осей грузового автомобиля
     */
    int axleCount;

    /**
     * @brief Сбор за проезд по платным участкам дорог (руб.)
     */
    double tollRoadFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    RoadTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор автомобиля
     * @param name Марка и модель грузовика
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     * @param axleCount Количество осей
     * @param tollRoadFee Сбор за платные участки дорог (руб.)
     */
    RoadTransport(const std::string& id,
                  const std::string& name,
                  const double capacityTons,
                  const double speedKmH,
                  const double ratePerTonKm,
                  const int axleCount,
                  const double tollRoadFee);

    /**
     * @brief Деструктор по умолчанию
     */
    ~RoadTransport() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    RoadTransport(const RoadTransport& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    RoadTransport& operator=(const RoadTransport& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    RoadTransport(RoadTransport&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    RoadTransport& operator=(RoadTransport&& other) noexcept;

    /**
     * @brief Получить количество осей автомобиля
     * @return Количество осей
     */
    int GetAxleCount() const;

    /**
     * @brief Установить количество осей автомобиля
     * @param count Новое количество осей
     */
    void SetAxleCount(const int count);

    /**
     * @brief Получить дорожный сбор за платные участки (руб.)
     * @return Сумма дорожного сбора
     */
    double GetTollRoadFee() const;

    /**
     * @brief Установить дорожный сбор за платные участки (руб.)
     * @param fee Новый дорожный сбор
     */
    void SetTollRoadFee(const double fee);

    /**
     * @brief Получить вид транспорта ("Автомобильный")
     * @return Строка "Автомобильный"
     */
    std::string GetTransportType() const override;

    /**
     * @brief Создать полиморфную копию автомобильного транспорта
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
     * @brief Рассчитать стоимость автомобильной перевозки с учетом платных дорог
     * @param distanceKm Протяженность маршрута (км)
     * @param weightTons Масса груза (т)
     * @return Стоимость перевозки (руб.)
     */
    double CalculateDeliveryCost(const double distanceKm, const double weightTons) const override;

    /**
     * @brief Получить полное строковое описание грузового автомобиля
     * @return Строка с характеристиками
     */
    std::string ToString() const override;

    /**
     * @brief Оператор равенства двух объектов RoadTransport
     * @param other Объект для сравнения
     * @return true, если объекты равны
     */
    bool operator==(const RoadTransport& other) const;

    /**
     * @brief Оператор неравенства двух объектов RoadTransport
     * @param other Объект для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const RoadTransport& other) const;
};
