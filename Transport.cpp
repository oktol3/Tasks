#include "Transport.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace
{
    constexpr double kEpsilon = 1e-6;
}

void Transport::ValidateNonEmpty(const std::string& value, const std::string& fieldName)
{
    const bool hasVisibleChar = value.find_first_not_of(" \t\n\r") != std::string::npos;
    if (!hasVisibleChar)
    {
        throw std::invalid_argument(fieldName + " не может быть пустым");
    }
}

bool Transport::AreEqual(const double lhs, const double rhs)
{
    return std::fabs(lhs - rhs) < kEpsilon;
}

std::string Transport::FormatDouble(const double value)
{
    const long long scaled = std::llround(value * 100.0);
    const bool negative = scaled < 0;
    const unsigned long long absScaled = negative
        ? static_cast<unsigned long long>(-(scaled + 1)) + 1ULL
        : static_cast<unsigned long long>(scaled);
    const unsigned long long whole = absScaled / 100ULL;
    const unsigned long long frac = absScaled % 100ULL;

    std::string result = negative ? "-" : "";
    result += std::to_string(whole) + ".";
    if (frac < 10ULL)
    {
        result += "0";
    }
    result += std::to_string(frac);
    return result;
}

Transport::Transport()
    : id("TR-0"),
    name("Не указано"),
    capacityTons(1.0),
    speedKmH(1.0),
    ratePerTonKm(0.0)
{
}

Transport::Transport(const std::string& id,
    const std::string& name,
    const double capacityTons,
    const double speedKmH,
    const double ratePerTonKm)
    : id(id),
    name(name),
    capacityTons(capacityTons),
    speedKmH(speedKmH),
    ratePerTonKm(ratePerTonKm)
{
    ValidateNonEmpty(this->id, "ID транспорта");
    ValidateNonEmpty(this->name, "Название транспорта");
    if (this->capacityTons <= 0.0)
    {
        throw std::invalid_argument("Грузоподъемность должна быть больше нуля");
    }
    if (this->speedKmH <= 0.0)
    {
        throw std::invalid_argument("Скорость должна быть больше нуля");
    }
    if (this->ratePerTonKm < 0.0)
    {
        throw std::invalid_argument("Тариф за тонно-километр не может быть отрицательным");
    }
}

Transport::Transport(const Transport& other)
    : id(other.id),
    name(other.name),
    capacityTons(other.capacityTons),
    speedKmH(other.speedKmH),
    ratePerTonKm(other.ratePerTonKm)
{
}

Transport& Transport::operator=(const Transport& other)
{
    if (this != &other)
    {
        id = other.id;
        name = other.name;
        capacityTons = other.capacityTons;
        speedKmH = other.speedKmH;
        ratePerTonKm = other.ratePerTonKm;
    }
    return *this;
}

Transport::Transport(Transport&& other) noexcept
    : id(std::move(other.id)),
    name(std::move(other.name)),
    capacityTons(other.capacityTons),
    speedKmH(other.speedKmH),
    ratePerTonKm(other.ratePerTonKm)
{
    other.capacityTons = 0.0;
    other.speedKmH = 0.0;
    other.ratePerTonKm = 0.0;
}

Transport& Transport::operator=(Transport&& other) noexcept
{
    if (this != &other)
    {
        id = std::move(other.id);
        name = std::move(other.name);
        capacityTons = other.capacityTons;
        speedKmH = other.speedKmH;
        ratePerTonKm = other.ratePerTonKm;
        other.capacityTons = 0.0;
        other.speedKmH = 0.0;
        other.ratePerTonKm = 0.0;
    }
    return *this;
}

const std::string& Transport::GetId() const
{
    return id;
}

void Transport::SetId(const std::string& newId)
{
    ValidateNonEmpty(newId, "ID транспорта");
    id = newId;
}

const std::string& Transport::GetName() const
{
    return name;
}

void Transport::SetName(const std::string& newName)
{
    ValidateNonEmpty(newName, "Название транспорта");
    name = newName;
}

double Transport::GetCapacityTons() const
{
    return capacityTons;
}

void Transport::SetCapacityTons(const double capacity)
{
    if (capacity <= 0.0)
    {
        throw std::invalid_argument("Грузоподъемность должна быть больше нуля");
    }
    capacityTons = capacity;
}

double Transport::GetSpeedKmH() const
{
    return speedKmH;
}

void Transport::SetSpeedKmH(const double speed)
{
    if (speed <= 0.0)
    {
        throw std::invalid_argument("Скорость должна быть больше нуля");
    }
    speedKmH = speed;
}

double Transport::GetRatePerTonKm() const
{
    return ratePerTonKm;
}

void Transport::SetRatePerTonKm(const double rate)
{
    if (rate < 0.0)
    {
        throw std::invalid_argument("Тариф за тонно-километр не может быть отрицательным");
    }
    ratePerTonKm = rate;
}

double Transport::CalculateDeliveryCost(const double distanceKm, const double weightTons) const
{
    if (distanceKm <= 0.0)
    {
        throw std::invalid_argument("Расстояние должно быть больше нуля");
    }
    if (weightTons <= 0.0)
    {
        throw std::invalid_argument("Масса груза должна быть больше нуля");
    }
    if (weightTons > capacityTons)
    {
        throw std::invalid_argument("Масса груза превышает грузоподъемность транспорта");
    }
    return distanceKm * weightTons * ratePerTonKm;
}

std::string Transport::ToString() const
{
    return "[" + GetTransportType() + "] " + name +
        " (ID: " + id + ")" +
        " | Грузоподъемность: " + FormatDouble(capacityTons) + " т" +
        " | Скорость: " + FormatDouble(speedKmH) + " км/ч" +
        " | Тариф: " + FormatDouble(ratePerTonKm) + " руб./(т*км)";
}

std::string Transport::GetSummary() const
{
    return GetTransportType() + ": " + name + " (ID: " + id + ", до " + FormatDouble(capacityTons) + " т)";
}

bool Transport::operator==(const Transport& other) const
{
    return id == other.id &&
        name == other.name &&
        GetTransportType() == other.GetTransportType() &&
        AreEqual(capacityTons, other.capacityTons) &&
        AreEqual(speedKmH, other.speedKmH) &&
        AreEqual(ratePerTonKm, other.ratePerTonKm);
}

bool Transport::operator!=(const Transport& other) const
{
    return !(*this == other);
}