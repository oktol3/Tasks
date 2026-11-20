#pragma once

#include "Transport.h"

/**
 * @brief Класс железнодорожного грузового транспорта
 */
class RailTransport : public Transport
{
private:
    int wagonCount;
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
     * @param ratePerTonKm Тариф за тонно-километр
     * @param wagonCount Количество вагонов
     * @param stationHandlingFee Станционный сбор (руб.)
     */
    RailTransport(const std::string& id,
        const std::string& name,
        double capacityTons,
        double speedKmH,
        double ratePerTonKm,
        int wagonCount,
        double stationHandlingFee);

    ~RailTransport() override = default;

    RailTransport(const RailTransport& other);
    RailTransport& operator=(const RailTransport& other);
    RailTransport(RailTransport&& other) noexcept;
    RailTransport& operator=(RailTransport&& other) noexcept;

    int GetWagonCount() const;
    void SetWagonCount(int count);

    double GetStationHandlingFee() const;
    void SetStationHandlingFee(double fee);

    std::string GetTransportType() const override;
    double CalculateDeliveryCost(double distanceKm, double weightTons) const override;
    std::string ToString() const override;

    bool operator==(const RailTransport& other) const;
    bool operator!=(const RailTransport& other) const;
};