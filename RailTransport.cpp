#include "RailTransport.h"

#include <stdexcept>
#include <typeinfo>
#include <utility>

RailTransport::RailTransport()
    : Transport(), wagonCount(1), stationHandlingFee(0.0)
{
}

RailTransport::RailTransport(const std::string& id,
                             const std::string& name,
                             const double capacityTons,
                             const double speedKmH,
                             const double ratePerTonKm,
                             const int wagonCount,
                             const double stationHandlingFee)
    : Transport(id, name, capacityTons, speedKmH, ratePerTonKm),
      wagonCount(wagonCount),
      stationHandlingFee(stationHandlingFee)
{
    if (this->wagonCount <= 0)
    {
        throw std::invalid_argument("Количество вагонов должно быть больше нуля");
    }
    if (this->stationHandlingFee < 0.0)
    {
        throw std::invalid_argument("Станционный сбор не может быть отрицательным");
    }
}

RailTransport::RailTransport(const RailTransport& other)
    : Transport(other),
      wagonCount(other.wagonCount),
      stationHandlingFee(other.stationHandlingFee)
{
}

RailTransport& RailTransport::operator=(const RailTransport& other)
{
    if (this != &other)
    {
        Transport::operator=(other);
        wagonCount = other.wagonCount;
        stationHandlingFee = other.stationHandlingFee;
    }
    return *this;
}

RailTransport::RailTransport(RailTransport&& other) noexcept
    : Transport(std::move(other)),
      wagonCount(other.wagonCount),
      stationHandlingFee(other.stationHandlingFee)
{
    other.wagonCount = 0;
    other.stationHandlingFee = 0.0;
}

RailTransport& RailTransport::operator=(RailTransport&& other) noexcept
{
    if (this != &other)
    {
        Transport::operator=(std::move(other));
        wagonCount = other.wagonCount;
        stationHandlingFee = other.stationHandlingFee;
        other.wagonCount = 0;
        other.stationHandlingFee = 0.0;
    }
    return *this;
}

int RailTransport::GetWagonCount() const
{
    return wagonCount;
}

void RailTransport::SetWagonCount(const int count)
{
    if (count <= 0)
    {
        throw std::invalid_argument("Количество вагонов должно быть больше нуля");
    }
    wagonCount = count;
}

double RailTransport::GetStationHandlingFee() const
{
    return stationHandlingFee;
}

void RailTransport::SetStationHandlingFee(const double fee)
{
    if (fee < 0.0)
    {
        throw std::invalid_argument("Станционный сбор не может быть отрицательным");
    }
    stationHandlingFee = fee;
}

std::string RailTransport::GetTransportType() const
{
    return "Железнодорожный";
}

std::unique_ptr<Transport> RailTransport::Clone() const
{
    return std::make_unique<RailTransport>(*this);
}

bool RailTransport::Equals(const Transport& other) const
{
    try
    {
        const RailTransport& derived = dynamic_cast<const RailTransport&>(other);
        return *this == derived;
    }
    catch (const std::bad_cast&)
    {
        return false;
    }
}

double RailTransport::CalculateDeliveryCost(const double distanceKm, const double weightTons) const
{
    return Transport::CalculateDeliveryCost(distanceKm, weightTons) + stationHandlingFee;
}

std::string RailTransport::ToString() const
{
    return Transport::ToString() +
           " | Вагонов: " + std::to_string(wagonCount) +
           " | Станционный сбор: " + FormatDouble(stationHandlingFee) + " руб.";
}

bool RailTransport::operator==(const RailTransport& other) const
{
    return Transport::operator==(other) &&
           wagonCount == other.wagonCount &&
           AreEqual(stationHandlingFee, other.stationHandlingFee);
}

bool RailTransport::operator!=(const RailTransport& other) const
{
    return !(*this == other);
}
