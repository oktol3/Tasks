#pragma once

#include "Transport.h"

/**
 * @brief Класс автомобильного грузового транспорта
 */
class RoadTransport : public Transport
{
private:
    int axleCount;
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
     * @param ratePerTonKm Тариф за тонно-километр
     * @param axleCount Количество осей
     * @param tollRoadFee Сбор за платные участки дорог (руб.)
     */
    RoadTransport(const std::string& id,
        const std::string& name,
        double capacityTons,
        double speedKmH,
        double ratePerTonKm,
        int axleCount,
        double tollRoadFee);

    ~RoadTransport() override = default;

    RoadTransport(const RoadTransport& other);
    RoadTransport& operator=(const RoadTransport& other);
    RoadTransport(RoadTransport&& other) noexcept;
    RoadTransport& operator=(RoadTransport&& other) noexcept;

    int GetAxleCount() const;
    void SetAxleCount(int count);

    double GetTollRoadFee() const;
    void SetTollRoadFee(double fee);

    std::string GetTransportType() const override;
    double CalculateDeliveryCost(double distanceKm, double weightTons) const override;
    std::string ToString() const override;

    bool operator==(const RoadTransport& other) const;
    bool operator!=(const RoadTransport& other) const;
};
