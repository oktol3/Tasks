#pragma once

#include "Transport.h"

/**
 * @brief Класс морского грузового транспорта
 */
class SeaTransport : public Transport
{
private:
    int containerCapacityTeu;
    double portFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    SeaTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор морского судна
     * @param name Название судна
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр
     * @param containerCapacityTeu Контейнеровместимость (TEU)
     * @param portFee Портовый сбор (руб.)
     */
    SeaTransport(const std::string& id,
        const std::string& name,
        double capacityTons,
        double speedKmH,
        double ratePerTonKm,
        int containerCapacityTeu,
        double portFee);

    ~SeaTransport() override = default;

    SeaTransport(const SeaTransport& other);
    SeaTransport& operator=(const SeaTransport& other);
    SeaTransport(SeaTransport&& other) noexcept;
    SeaTransport& operator=(SeaTransport&& other) noexcept;

    int GetContainerCapacityTeu() const;
    void SetContainerCapacityTeu(int capacityTeu);

    double GetPortFee() const;
    void SetPortFee(double fee);

    std::string GetTransportType() const override;
    double CalculateDeliveryCost(double distanceKm, double weightTons) const override;
    std::string ToString() const override;

    bool operator==(const SeaTransport& other) const;
    bool operator!=(const SeaTransport& other) const;
};