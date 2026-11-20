#include "CargoOrder.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace
{
    constexpr double kOrderEpsilon = 1e-6;
}

CargoOrder::CargoOrder()
    : id(0), client(nullptr), route(nullptr), transport(nullptr), cargoName(""), weightTons(0.0)
{
}

CargoOrder::CargoOrder(const int id,
    const Client* client,
    const Route* route,
    const Transport* transport,
    const std::string& cargoName,
    const double weightTons)
    : id(id),
    client(client),
    route(route),
    transport(transport),
    cargoName(cargoName),
    weightTons(weightTons)
{
    if (this->id <= 0)
    {
        throw std::invalid_argument("ID заказа должен быть больше нуля");
    }
    if (this->client == nullptr)
    {
        throw std::invalid_argument("Клиент не может быть nullptr");
    }
    if (this->route == nullptr)
    {
        throw std::invalid_argument("Маршрут не может быть nullptr");
    }
    if (this->transport == nullptr)
    {
        throw std::invalid_argument("Транспорт не может быть nullptr");
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
    transport(other.transport),
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
        transport = other.transport;
        cargoName = other.cargoName;
        weightTons = other.weightTons;
    }
    return *this;
}

CargoOrder::CargoOrder(CargoOrder&& other) noexcept
    : id(other.id),
    client(other.client),
    route(other.route),
    transport(other.transport),
    cargoName(std::move(other.cargoName)),
    weightTons(other.weightTons)
{
    other.id = 0;
    other.client = nullptr;
    other.route = nullptr;
    other.transport = nullptr;
    other.weightTons = 0.0;
}

CargoOrder& CargoOrder::operator=(CargoOrder&& other) noexcept
{
    if (this != &other)
    {
        id = other.id;
        client = other.client;
        route = other.route;
        transport = other.transport;
        cargoName = std::move(other.cargoName);
        weightTons = other.weightTons;
        other.id = 0;
        other.client = nullptr;
        other.route = nullptr;
        other.transport = nullptr;
        other.weightTons = 0.0;
    }
    return *this;
}

int CargoOrder::GetId() const
{
    return id;
}

const Client* CargoOrder::GetClient() const
{
    return client;
}

const Route* CargoOrder::GetRoute() const
{
    return route;
}

const Transport* CargoOrder::GetTransport() const
{
    return transport;
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
    if (client == nullptr || route == nullptr || transport == nullptr)
    {
        throw std::logic_error("Невозможно рассчитать стоимость незаполненного заказа");
    }
    const double rawCost = route->GetBasePrice() +
        transport->CalculateDeliveryCost(route->GetDistanceKm(), weightTons);
    const double discountFactor = 1.0 - client->GetEffectiveDiscountPercent() / 100.0;
    return rawCost * discountFactor;
}

double CargoOrder::GetFreightTurnover() const
{
    if (route == nullptr)
    {
        return 0.0;
    }
    return weightTons * route->GetDistanceKm();
}

std::string CargoOrder::ToString() const
{
    if (client == nullptr || route == nullptr || transport == nullptr)
    {
        return "Заказ #" + std::to_string(id) + " (не заполнен)";
    }
    return "Заказ #" + std::to_string(id) +
        " | Груз: " + cargoName + " (" + Transport::FormatDouble(weightTons) + " т)" +
        " | Маршрут: " + route->GetRouteName() +
        " | Транспорт: " + transport->GetSummary() +
        " | Клиент: " + client->GetName() +
        " | Стоимость: " + Transport::FormatDouble(CalculateCost()) + " руб.";
}

bool CargoOrder::operator==(const CargoOrder& other) const
{
    return id == other.id &&
        client == other.client &&
        route == other.route &&
        transport == other.transport &&
        cargoName == other.cargoName &&
        std::fabs(weightTons - other.weightTons) < kOrderEpsilon;
}

bool CargoOrder::operator!=(const CargoOrder& other) const
{
    return !(*this == other);
}