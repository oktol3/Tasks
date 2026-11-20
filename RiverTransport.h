#pragma once

#include "Transport.h"

/**
 * @brief Класс речного грузового транспорта
 */
class RiverTransport : public Transport
{
private:
    double draftMeters;
    double lockPassageFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    RiverTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор судна
     * @param name Название речного судна
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр
     * @param draftMeters Осадка судна (м)
     * @param lockPassageFee Сбор за прохождение шлюзов (руб.)
     */
    RiverTransport(const std::string& id,
        const std::string& name,
        double capacityTons,
        double speedKmH,
        double ratePerTonKm,
        double draftMeters,
        double lockPassageFee);

    ~RiverTransport() override = default;

    RiverTransport(const RiverTransport& other);
    RiverTransport& operator=(const RiverTransport& other);
    RiverTransport(RiverTransport&& other) noexcept;
    RiverTransport& operator=(RiverTransport&& other) noexcept;

    double GetDraftMeters() const;
    void SetDraftMeters(double draft);

    double GetLockPassageFee() const;
    void SetLockPassageFee(double fee);

    std::string GetTransportType() const override;
    double CalculateDeliveryCost(double distanceKm, double weightTons) const override;
    std::string ToString() const override;

    bool operator==(const RiverTransport& other) const;
    bool operator!=(const RiverTransport& other) const;
};