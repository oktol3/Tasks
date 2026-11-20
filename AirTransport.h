#pragma once

#include "Transport.h"

/**
 * @brief Класс воздушного грузового транспорта
 */
class AirTransport : public Transport
{
private:
    double maxAltitudeMeters;
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
     * @param ratePerTonKm Тариф за тонно-километр
     * @param maxAltitudeMeters Максимальная высота полета (м)
     * @param airportFee Аэропортовый сбор (руб.)
     */
    AirTransport(const std::string& id,
        const std::string& name,
        double capacityTons,
        double speedKmH,
        double ratePerTonKm,
        double maxAltitudeMeters,
        double airportFee);

    ~AirTransport() override = default;

    AirTransport(const AirTransport& other);
    AirTransport& operator=(const AirTransport& other);
    AirTransport(AirTransport&& other) noexcept;
    AirTransport& operator=(AirTransport&& other) noexcept;

    /**
     * @brief Получить максимальную высоту полета (м)
     */
    double GetMaxAltitudeMeters() const;

    /**
     * @brief Установить максимальную высоту полета (м)
     */
    void SetMaxAltitudeMeters(double altitude);

    /**
     * @brief Получить аэропортовый сбор (руб.)
     */
    double GetAirportFee() const;

    /**
     * @brief Установить аэропортовый сбор (руб.)
     */
    void SetAirportFee(double fee);

    std::string GetTransportType() const override;
    double CalculateDeliveryCost(double distanceKm, double weightTons) const override;
    std::string ToString() const override;

    bool operator==(const AirTransport& other) const;
    bool operator!=(const AirTransport& other) const;
};