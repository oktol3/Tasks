#pragma once

#include "Transport.h"

/**
 * @brief Класс железнодорожного грузового транспорта
 */
class RailTransport : public Transport
{
private:
    /**
     * @brief Количество грузовых вагонов в составе
     */
    int wagonCount;

    /**
     * @brief Станционный сбор за формирование и обработку состава (руб.)
     */
    double stationHandlingFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    RailTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор состава
     * @param name Серия локомотива / название состава
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     * @param wagonCount Количество вагонов
     * @param stationHandlingFee Станционный сбор (руб.)
     */
    RailTransport(const std::string& id,
                  const std::string& name,
                  const double capacityTons,
                  const double speedKmH,
                  const double ratePerTonKm,
                  const int wagonCount,
                  const double stationHandlingFee);

    /**
     * @brief Деструктор по умолчанию
     */
    ~RailTransport() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    RailTransport(const RailTransport& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    RailTransport& operator=(const RailTransport& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    RailTransport(RailTransport&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    RailTransport& operator=(RailTransport&& other) noexcept;

    /**
     * @brief Получить количество вагонов в составе
     * @return Количество вагонов
     */
    int GetWagonCount() const;

    /**
     * @brief Установить количество вагонов в составе
     * @param count Новое количество вагонов
     */
    void SetWagonCount(const int count);

    /**
     * @brief Получить станционный сбор (руб.)
     * @return Сумма станционного сбора
     */
    double GetStationHandlingFee() const;

    /**
     * @brief Установить станционный сбор (руб.)
     * @param fee Новый станционный сбор
     */
    void SetStationHandlingFee(const double fee);

    /**
     * @brief Получить вид транспорта ("Железнодорожный")
     * @return Строка "Железнодорожный"
     */
    std::string GetTransportType() const override;

    /**
     * @brief Создать полиморфную копию железнодорожного транспорта
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
     * @brief Рассчитать стоимость железнодорожной перевозки с учетом станционного сбора
     * @param distanceKm Протяженность маршрута (км)
     * @param weightTons Масса груза (т)
     * @return Стоимость перевозки (руб.)
     */
    double CalculateDeliveryCost(const double distanceKm, const double weightTons) const override;

    /**
     * @brief Получить полное строковое описание железнодорожного состава
     * @return Строка с характеристиками
     */
    std::string ToString() const override;

    /**
     * @brief Оператор равенства двух объектов RailTransport
     * @param other Объект для сравнения
     * @return true, если объекты равны
     */
    bool operator==(const RailTransport& other) const;

    /**
     * @brief Оператор неравенства двух объектов RailTransport
     * @param other Объект для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const RailTransport& other) const;
};
