#include "RoadTransport.h"

#include <stdexcept>
#include <utility>

RoadTransport::RoadTransport()
    : Transport(), axleCount(2), tollRoadFee(0.0)
{
}

RoadTransport::RoadTransport(const std::string& id,
    const std::string& name,
    const double capacityTons,
    const double speedKmH,
    const double ratePerTonKm,
    const int axleCount,
    const double tollRoadFee)
    : Transport(id, name, capacityTons, speedKmH, ratePerTonKm),
    axleCount(axleCount),
    tollRoadFee(tollRoadFee)
{
    if (this->axleCount < 2)
    {
        throw std::invalid_argument("Количество осей автомобиля должно быть не менее двух");
    }
    if (this->tollRoadFee < 0.0)
    {
        throw std::invalid_argument("Дорожный сбор не может быть отрицательным");
    }
}

RoadTransport::RoadTransport(const RoadTransport& other)
    : Transport(other),
    axleCount(other.axleCount),
    tollRoadFee(other.tollRoadFee)
{
}

RoadTransport& RoadTransport::operator=(const RoadTransport& other)
{
    if (this != &other)
    {
        Transport::operator=(other);
        axleCount = other.axleCount;
        tollRoadFee = other.tollRoadFee;
    }
    return *this;
}

RoadTransport::RoadTransport(RoadTransport&& other) noexcept
    : Transport(std::move(other)),
    axleCount(other.axleCount),
    tollRoadFee(other.tollRoadFee)
{
    other.axleCount = 0;
    other.tollRoadFee = 0.0;
}

RoadTransport& RoadTransport::operator=(RoadTransport&& other) noexcept
{
    if (this != &other)
    {
        Transport::operator=(std::move(other));
        axleCount = other.axleCount;
        tollRoadFee = other.tollRoadFee;
        other.axleCount = 0;
        other.tollRoadFee = 0.0;
    }
    return *this;
}

int RoadTransport::GetAxleCount() const
{
    return axleCount;
}

void RoadTransport::SetAxleCount(const int count)
{
    if (count < 2)
    {
        throw std::invalid_argument("Количество осей автомобиля должно быть не менее двух");
    }
    axleCount = count;
}

double RoadTransport::GetTollRoadFee() const
{
    return tollRoadFee;
}

void RoadTransport::SetTollRoadFee(const double fee)
{
    if (fee < 0.0)
    {
        throw std::invalid_argument("Дорожный сбор не может быть отрицательным");
    }
    tollRoadFee = fee;
}

std::string RoadTransport::GetTransportType() const
{
    return "Автомобильный";
}

double RoadTransport::CalculateDeliveryCost(const double distanceKm, const double weightTons) const
{
    return Transport::CalculateDeliveryCost(distanceKm, weightTons) + tollRoadFee;
}

std::string RoadTransport::ToString() const
{
    return Transport::ToString() +
        " | Осей: " + std::to_string(axleCount) +
        " | Платные дороги: " + FormatDouble(tollRoadFee) + " руб.";
}

bool RoadTransport::operator==(const RoadTransport& other) const
{
    return Transport::operator==(other) &&
        axleCount == other.axleCount &&
        AreEqual(tollRoadFee, other.tollRoadFee);
}

bool RoadTransport::operator!=(const RoadTransport& other) const
{
    return !(*this == other);
}