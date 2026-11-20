#include "Route.h"
#include "Transport.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace
{
    constexpr double kRouteEpsilon = 1e-6;
}

void Route::ValidateNonEmpty(const std::string& value, const std::string& fieldName)
{
    if (value.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument(fieldName + " не может быть пустым");
    }
}

Route::Route()
    : id("R-0"), origin("Не указан"), destination("Не указан"), distanceKm(1.0), basePrice(0.0)
{
}

Route::Route(const std::string& id,
    const std::string& origin,
    const std::string& destination,
    const double distanceKm,
    const double basePrice)
    : id(id),
    origin(origin),
    destination(destination),
    distanceKm(distanceKm),
    basePrice(basePrice)
{
    ValidateNonEmpty(this->id, "ID маршрута");
    ValidateNonEmpty(this->origin, "Пункт отправления");
    ValidateNonEmpty(this->destination, "Пункт назначения");
    if (this->distanceKm <= 0.0)
    {
        throw std::invalid_argument("Протяженность маршрута должна быть больше нуля");
    }
    if (this->basePrice < 0.0)
    {
        throw std::invalid_argument("Базовая цена маршрута не может быть отрицательной");
    }
}

Route::Route(const Route& other)
    : id(other.id),
    origin(other.origin),
    destination(other.destination),
    distanceKm(other.distanceKm),
    basePrice(other.basePrice)
{
}

Route& Route::operator=(const Route& other)
{
    if (this != &other)
    {
        id = other.id;
        origin = other.origin;
        destination = other.destination;
        distanceKm = other.distanceKm;
        basePrice = other.basePrice;
    }
    return *this;
}

Route::Route(Route&& other) noexcept
    : id(std::move(other.id)),
    origin(std::move(other.origin)),
    destination(std::move(other.destination)),
    distanceKm(other.distanceKm),
    basePrice(other.basePrice)
{
    other.distanceKm = 0.0;
    other.basePrice = 0.0;
}

Route& Route::operator=(Route&& other) noexcept
{
    if (this != &other)
    {
        id = std::move(other.id);
        origin = std::move(other.origin);
        destination = std::move(other.destination);
        distanceKm = other.distanceKm;
        basePrice = other.basePrice;
        other.distanceKm = 0.0;
        other.basePrice = 0.0;
    }
    return *this;
}

const std::string& Route::GetId() const
{
    return id;
}

void Route::SetId(const std::string& newId)
{
    ValidateNonEmpty(newId, "ID маршрута");
    id = newId;
}

const std::string& Route::GetOrigin() const
{
    return origin;
}

void Route::SetOrigin(const std::string& newOrigin)
{
    ValidateNonEmpty(newOrigin, "Пункт отправления");
    origin = newOrigin;
}

const std::string& Route::GetDestination() const
{
    return destination;
}

void Route::SetDestination(const std::string& newDestination)
{
    ValidateNonEmpty(newDestination, "Пункт назначения");
    destination = newDestination;
}

double Route::GetDistanceKm() const
{
    return distanceKm;
}

void Route::SetDistanceKm(const double distance)
{
    if (distance <= 0.0)
    {
        throw std::invalid_argument("Протяженность маршрута должна быть больше нуля");
    }
    distanceKm = distance;
}

double Route::GetBasePrice() const
{
    return basePrice;
}

void Route::SetBasePrice(const double price)
{
    if (price < 0.0)
    {
        throw std::invalid_argument("Базовая цена маршрута не может быть отрицательной");
    }
    basePrice = price;
}

std::string Route::GetRouteName() const
{
    return origin + " -> " + destination;
}

std::string Route::ToString() const
{
    return "[" + id + "] " + GetRouteName() +
        " | Расстояние: " + Transport::FormatDouble(distanceKm) + " км" +
        " | Базовая цена: " + Transport::FormatDouble(basePrice) + " руб.";
}

bool Route::operator==(const Route& other) const
{
    return id == other.id &&
        origin == other.origin &&
        destination == other.destination &&
        std::fabs(distanceKm - other.distanceKm) < kRouteEpsilon &&
        std::fabs(basePrice - other.basePrice) < kRouteEpsilon;
}

bool Route::operator!=(const Route& other) const
{
    return !(*this == other);
}