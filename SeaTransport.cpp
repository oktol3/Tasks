#include "SeaTransport.h"

#include <stdexcept>
#include <typeinfo>
#include <utility>

SeaTransport::SeaTransport()
    : Transport(), containerCapacityTeu(100), portFee(0.0)
{
}

SeaTransport::SeaTransport(const std::string& id,
                           const std::string& name,
                           const double capacityTons,
                           const double speedKmH,
                           const double ratePerTonKm,
                           const int containerCapacityTeu,
                           const double portFee)
    : Transport(id, name, capacityTons, speedKmH, ratePerTonKm),
      containerCapacityTeu(containerCapacityTeu),
      portFee(portFee)
{
    if (this->containerCapacityTeu <= 0)
    {
        throw std::invalid_argument("Контейнеровместимость должна быть больше нуля");
    }
    if (this->portFee < 0.0)
    {
        throw std::invalid_argument("Портовый сбор не может быть отрицательным");
    }
}

SeaTransport::SeaTransport(const SeaTransport& other)
    : Transport(other),
      containerCapacityTeu(other.containerCapacityTeu),
      portFee(other.portFee)
{
}

SeaTransport& SeaTransport::operator=(const SeaTransport& other)
{
    if (this != &other)
    {
        Transport::operator=(other);
        containerCapacityTeu = other.containerCapacityTeu;
        portFee = other.portFee;
    }
    return *this;
}

SeaTransport::SeaTransport(SeaTransport&& other) noexcept
    : Transport(std::move(other)),
      containerCapacityTeu(other.containerCapacityTeu),
      portFee(other.portFee)
{
    other.containerCapacityTeu = 0;
    other.portFee = 0.0;
}

SeaTransport& SeaTransport::operator=(SeaTransport&& other) noexcept
{
    if (this != &other)
    {
        Transport::operator=(std::move(other));
        containerCapacityTeu = other.containerCapacityTeu;
        portFee = other.portFee;
        other.containerCapacityTeu = 0;
        other.portFee = 0.0;
    }
    return *this;
}

int SeaTransport::GetContainerCapacityTeu() const
{
    return containerCapacityTeu;
}

void SeaTransport::SetContainerCapacityTeu(const int capacityTeu)
{
    if (capacityTeu <= 0)
    {
        throw std::invalid_argument("Контейнеровместимость должна быть больше нуля");
    }
    containerCapacityTeu = capacityTeu;
}

double SeaTransport::GetPortFee() const
{
    return portFee;
}

void SeaTransport::SetPortFee(const double fee)
{
    if (fee < 0.0)
    {
        throw std::invalid_argument("Портовый сбор не может быть отрицательным");
    }
    portFee = fee;
}

std::string SeaTransport::GetTransportType() const
{
    return "Морской";
}

std::unique_ptr<Transport> SeaTransport::Clone() const
{
    return std::make_unique<SeaTransport>(*this);
}

bool SeaTransport::Equals(const Transport& other) const
{
    try
    {
        const SeaTransport& derived = dynamic_cast<const SeaTransport&>(other);
        return *this == derived;
    }
    catch (const std::bad_cast&)
    {
        return false;
    }
}

double SeaTransport::CalculateDeliveryCost(const double distanceKm, const double weightTons) const
{
    return Transport::CalculateDeliveryCost(distanceKm, weightTons) + portFee;
}

std::string SeaTransport::ToString() const
{
    return Transport::ToString() +
           " | Вместимость: " + std::to_string(containerCapacityTeu) + " TEU" +
           " | Портовый сбор: " + FormatDouble(portFee) + " руб.";
}

bool SeaTransport::operator==(const SeaTransport& other) const
{
    return Transport::operator==(other) &&
           containerCapacityTeu == other.containerCapacityTeu &&
           AreEqual(portFee, other.portFee);
}

bool SeaTransport::operator!=(const SeaTransport& other) const
{
    return !(*this == other);
}
