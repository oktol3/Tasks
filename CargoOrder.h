#pragma once

#include <string>
#include "Client.h"
#include "Route.h"
#include "Transport.h"

/**
 * @brief  ласс заказа на перевозку груза
 */
class CargoOrder
{
private:
    int id;
    const Client* client;
    const Route* route;
    const Transport* transport;
    std::string cargoName;
    double weightTons;

public:
    CargoOrder();
    CargoOrder(int id,
        const Client* client,
        const Route* route,
        const Transport* transport,
        const std::string& cargoName,
        double weightTons);
    ~CargoOrder() = default;

    CargoOrder(const CargoOrder& other);
    CargoOrder& operator=(const CargoOrder& other);
    CargoOrder(CargoOrder&& other) noexcept;
    CargoOrder& operator=(CargoOrder&& other) noexcept;

    int GetId() const;
    const Client* GetClient() const;
    const Route* GetRoute() const;
    const Transport* GetTransport() const;
    const std::string& GetCargoName() const;
    double GetWeightTons() const;

    /**
     * @brief –ассчитать итоговую стоимость перевозки с учетом скидки посто€нного клиента
     * @return »тогова€ стоимость в рубл€х
     */
    double CalculateCost() const;

    /**
     * @brief –ассчитать грузооборот по данному заказу (масса * рассто€ние, т*км)
     * @return √рузооборот в тонно-километрах
     */
    double GetFreightTurnover() const;

    std::string ToString() const;

    bool operator==(const CargoOrder& other) const;
    bool operator!=(const CargoOrder& other) const;
};