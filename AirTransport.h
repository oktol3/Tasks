#pragma once

#include "Transport.h"

/**
 * @brief Класс воздушного грузового транспорта
 */
class AirTransport : public Transport
{
private:
    /**
     * @brief Максимальная высота полета (м)
     */
    double maxAltitudeMeters;

    /**
     * @brief Фиксированный аэропортовый сбор за рейс (руб.)
     */
    double airportFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    AirTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор воздушного судна
     * @param name Модель воздушного судна
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Крейсерская скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     * @param maxAltitudeMeters Максимальная высота полета (м)
     * @param airportFee Аэропортовый сбор (руб.)
     */
    AirTransport(const std::string& id,
                 const std::string& name,
                 const double capacityTons,
                 const double speedKmH,
                 const double ratePerTonKm,
                 const double maxAltitudeMeters,
                 const double airportFee);

    /**
     * @brief Деструктор по умолчанию
     */
    ~AirTransport() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    AirTransport(const AirTransport& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    AirTransport& operator=(const AirTransport& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    AirTransport(AirTransport&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    AirTransport& operator=(AirTransport&& other) noexcept;

    /**
     * @brief Получить максимальную высоту полета (м)
     * @return Максимальная высота полета
     */
    double GetMaxAltitudeMeters() const;

    /**
     * @brief Установить максимальную высоту полета (м)
     * @param altitude Новая максимальная высота полета
     */
    void SetMaxAltitudeMeters(const double altitude);

    /**
     * @brief Получить аэропортовый сбор (руб.)
     * @return Сумма аэропортового сбора
     */
    double GetAirportFee() const;

    /**
     * @brief Установить аэропортовый сбор (руб.)
     * @param fee Новый аэропортовый сбор
     */
    void SetAirportFee(const double fee);

    /**
     * @brief Получить вид транспорта ("Воздушный")
     * @return Строка "Воздушный"
     */
    std::string GetTransportType() const override;

    /**
     * @brief Создать полиморфную копию воздушного транспорта
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
     * @brief Рассчитать стоимость воздушной перевозки с учетом аэропортового сбора
     * @param distanceKm Протяженность маршрута (км)
     * @param weightTons Масса груза (т)
     * @return Стоимость перевозки (руб.)
     */
    double CalculateDeliveryCost(const double distanceKm, const double weightTons) const override;

    /**
     * @brief Получить полное строковое описание воздушного судна
     * @return Строка с характеристиками
     */
    std::string ToString() const override;

    /**
     * @brief Оператор равенства двух объектов AirTransport
     * @param other Объект для сравнения
     * @return true, если объекты равны
     */
    bool operator==(const AirTransport& other) const;

    /**
     * @brief Оператор неравенства двух объектов AirTransport
     * @param other Объект для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const AirTransport& other) const;
};
