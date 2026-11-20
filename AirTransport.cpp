#include "AirTransport.h"

#include <stdexcept>
#include <utility>

AirTransport::AirTransport()
    : Transport(), maxAltitudeMeters(10000.0), airportFee(0.0)
{
}

AirTransport::AirTransport(const std::string& id,
    const std::string& name,
    const double capacityTons,
    const double speedKmH,
    const double ratePerTonKm,
    const double maxAltitudeMeters,
    const double airportFee)
    : Transport(id, name, capacityTons, speedKmH, ratePerTonKm),
    maxAltitudeMeters(maxAltitudeMeters),
    airportFee(airportFee)
{
    if (this->maxAltitudeMeters <= 0.0)
    {
        throw std::invalid_argument("Максимальная высота полета должна быть больше нуля");
    }
    if (this->airportFee < 0.0)
    {
        throw std::invalid_argument("Аэропортовый сбор не может быть отрицательным");
    }
}

AirTransport::AirTransport(const AirTransport& other)
    : Transport(other),
    maxAltitudeMeters(other.maxAltitudeMeters),
    airportFee(other.airportFee)
{
}

AirTransport& AirTransport::operator=(const AirTransport& other)
{
    if (this != &other)
    {
        Transport::operator=(other);
        maxAltitudeMeters = other.maxAltitudeMeters;
        airportFee = other.airportFee;
    }
    return *this;
}

AirTransport::AirTransport(AirTransport&& other) noexcept
    : Transport(std::move(other)),
    maxAltitudeMeters(other.maxAltitudeMeters),
    airportFee(other.airportFee)
{
    other.maxAltitudeMeters = 0.0;
    other.airportFee = 0.0;
}

AirTransport& AirTransport::operator=(AirTransport&& other) noexcept
{
    if (this != &other)
    {
        Transport::operator=(std::move(other));
        maxAltitudeMeters = other.maxAltitudeMeters;
        airportFee = other.airportFee;
        other.maxAltitudeMeters = 0.0;
        other.airportFee = 0.0;
    }
    return *this;
}

double AirTransport::GetMaxAltitudeMeters() const
{
    return maxAltitudeMeters;
}

void AirTransport::SetMaxAltitudeMeters(const double altitude)
{
    if (altitude <= 0.0)
    {
        throw std::invalid_argument("Максимальная высота полета должна быть больше нуля");
    }
    maxAltitudeMeters = altitude;
}

double AirTransport::GetAirportFee() const
{
    return airportFee;
}

void AirTransport::SetAirportFee(const double fee)
{
    if (fee < 0.0)
    {
        throw std::invalid_argument("Аэропортовый сбор не может быть отрицательным");
    }
    airportFee = fee;
}

std::string AirTransport::GetTransportType() const
{
    return "Воздушный";
}

double AirTransport::CalculateDeliveryCost(const double distanceKm, const double weightTons) const
{
    return Transport::CalculateDeliveryCost(distanceKm, weightTons) + airportFee;
}

std::string AirTransport::ToString() const
{
    return Transport::ToString() +
        " | Макс. высота: " + FormatDouble(maxAltitudeMeters) + " м" +
        " | Аэропортовый сбор: " + FormatDouble(airportFee) + " руб.";
}

bool AirTransport::operator==(const AirTransport& other) const
{
    return Transport::operator==(other) &&
        AreEqual(maxAltitudeMeters, other.maxAltitudeMeters) &&
        AreEqual(airportFee, other.airportFee);
}

bool AirTransport::operator!=(const AirTransport& other) const
{
    return !(*this == other);
}