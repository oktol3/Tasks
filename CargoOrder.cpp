#include "CargoOrder.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace
{
    constexpr double kOrderEpsilon = 1e-6;
}

CargoOrder::CargoOrder()
    : id(0), client(), route(), transport(nullptr), cargoName(""), weightTons(0.0)
{
}

CargoOrder::CargoOrder(const int id,
                       const Client& client,
                       const Route& route,
                       const Transport& transport,
                       const std::string& cargoName,
                       const double weightTons)
    : id(id),
      client(client),
      route(route),
      transport(transport.Clone()),
      cargoName(cargoName),
      weightTons(weightTons)
{
    if (this->id <= 0)
    {
        throw std::invalid_argument("ID заказа должен быть больше нуля");
    }
    if (this->cargoName.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("Наименование груза не может быть пустым");
    }
    if (this->weightTons <= 0.0)
    {
        throw std::invalid_argument("Масса груза должна быть больше нуля");
    }
    if (this->weightTons > this->transport->GetCapacityTons())
    {
        throw std::invalid_argument("Масса груза превышает грузоподъемность выбранного транспорта");
    }
}

CargoOrder::CargoOrder(const CargoOrder& other)
    : id(other.id),
      client(other.client),
      route(other.route),
      transport(other.transport ? other.transport->Clone() : nullptr),
      cargoName(other.cargoName),
      weightTons(other.weightTons)
{
}

CargoOrder& CargoOrder::operator=(const CargoOrder& other)
{
    if (this != &other)
    {
        id = other.id;
        client = other.client;
        route = other.route;
        transport = other.transport ? other.transport->Clone() : nullptr;
        cargoName = other.cargoName;
        weightTons = other.weightTons;
    }
    return *this;
}

CargoOrder::CargoOrder(CargoOrder&& other) noexcept
    : id(other.id),
      client(std::move(other.client)),
      route(std::move(other.route)),
      transport(std::move(other.transport)),
      cargoName(std::move(other.cargoName)),
      weightTons(other.weightTons)
{
    other.id = 0;
    other.weightTons = 0.0;
}

CargoOrder& CargoOrder::operator=(CargoOrder&& other) noexcept
{
    if (this != &other)
    {
        id = other.id;
        client = std::move(other.client);
        route = std::move(other.route);
        transport = std::move(other.transport);
        cargoName = std::move(other.cargoName);
        weightTons = other.weightTons;
        other.id = 0;
        other.weightTons = 0.0;
    }
    return *this;
}

int CargoOrder::GetId() const
{
    return id;
}

const Client& CargoOrder::GetClient() const
{
    return client;
}

const Route& CargoOrder::GetRoute() const
{
    return route;
}

bool CargoOrder::HasTransport() const
{
    return static_cast<bool>(transport);
}

const Transport& CargoOrder::GetTransport() const
{
    if (!transport)
    {
        throw std::logic_error("Транспорт в заказе не задан");
    }
    return *transport;
}

const std::string& CargoOrder::GetCargoName() const
{
    return cargoName;
}

double CargoOrder::GetWeightTons() const
{
    return weightTons;
}

double CargoOrder::CalculateCost() const
{
    if (!transport || id <= 0)
    {
        throw std::logic_error("Невозможно рассчитать стоимость незаполненного заказа");
    }
    const double rawCost = route.GetBasePrice() +
                           transport->CalculateDeliveryCost(route.GetDistanceKm(), weightTons);
    const double discountFactor = 1.0 - client.GetEffectiveDiscountPercent() / 100.0;
    return rawCost * discountFactor;
}

double CargoOrder::GetFreightTurnover() const
{
    if (!transport || weightTons <= 0.0)
    {
        return 0.0;
    }
    return weightTons * route.GetDistanceKm();
}

std::string CargoOrder::ToString() const
{
    if (!transport || id <= 0)
    {
        return "Заказ #" + std::to_string(id) + " (не заполнен)";
    }
    return "Заказ #" + std::to_string(id) +
           " | Груз: " + cargoName + " (" + Transport::FormatDouble(weightTons) + " т)" +
           " | Маршрут: " + route.GetRouteName() +
           " | Транспорт: " + transport->GetSummary() +
           " | Клиент: " + client.GetName() +
           " | Стоимость: " + Transport::FormatDouble(CalculateCost()) + " руб.";
}

bool CargoOrder::operator==(const CargoOrder& other) const
{
    const bool sameTransport = (!transport && !other.transport) ||
                               (transport && other.transport && transport->Equals(*other.transport));
    return id == other.id &&
           client == other.client &&
           route == other.route &&
           sameTransport &&
           cargoName == other.cargoName &&
           std::fabs(weightTons - other.weightTons) < kOrderEpsilon;
}

bool CargoOrder::operator!=(const CargoOrder& other) const
{
    return !(*this == other);
}
