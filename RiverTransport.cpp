#include "RiverTransport.h"

#include <stdexcept>
#include <typeinfo>
#include <utility>

RiverTransport::RiverTransport()
    : Transport(), draftMeters(2.0), lockPassageFee(0.0)
{
}

RiverTransport::RiverTransport(const std::string& id,
                               const std::string& name,
                               const double capacityTons,
                               const double speedKmH,
                               const double ratePerTonKm,
                               const double draftMeters,
                               const double lockPassageFee)
    : Transport(id, name, capacityTons, speedKmH, ratePerTonKm),
      draftMeters(draftMeters),
      lockPassageFee(lockPassageFee)
{
    if (this->draftMeters <= 0.0)
    {
        throw std::invalid_argument("Осадка судна должна быть больше нуля");
    }
    if (this->lockPassageFee < 0.0)
    {
        throw std::invalid_argument("Сбор за шлюзование не может быть отрицательным");
    }
}

RiverTransport::RiverTransport(const RiverTransport& other)
    : Transport(other),
      draftMeters(other.draftMeters),
      lockPassageFee(other.lockPassageFee)
{
}

RiverTransport& RiverTransport::operator=(const RiverTransport& other)
{
    if (this != &other)
    {
        Transport::operator=(other);
        draftMeters = other.draftMeters;
        lockPassageFee = other.lockPassageFee;
    }
    return *this;
}

RiverTransport::RiverTransport(RiverTransport&& other) noexcept
    : Transport(std::move(other)),
      draftMeters(other.draftMeters),
      lockPassageFee(other.lockPassageFee)
{
    other.draftMeters = 0.0;
    other.lockPassageFee = 0.0;
}

RiverTransport& RiverTransport::operator=(RiverTransport&& other) noexcept
{
    if (this != &other)
    {
        Transport::operator=(std::move(other));
        draftMeters = other.draftMeters;
        lockPassageFee = other.lockPassageFee;
        other.draftMeters = 0.0;
        other.lockPassageFee = 0.0;
    }
    return *this;
}

double RiverTransport::GetDraftMeters() const
{
    return draftMeters;
}

void RiverTransport::SetDraftMeters(const double draft)
{
    if (draft <= 0.0)
    {
        throw std::invalid_argument("Осадка судна должна быть больше нуля");
    }
    draftMeters = draft;
}

double RiverTransport::GetLockPassageFee() const
{
    return lockPassageFee;
}

void RiverTransport::SetLockPassageFee(const double fee)
{
    if (fee < 0.0)
    {
        throw std::invalid_argument("Сбор за шлюзование не может быть отрицательным");
    }
    lockPassageFee = fee;
}

std::string RiverTransport::GetTransportType() const
{
    return "Речной";
}

std::unique_ptr<Transport> RiverTransport::Clone() const
{
    return std::make_unique<RiverTransport>(*this);
}

bool RiverTransport::Equals(const Transport& other) const
{
    try
    {
        const RiverTransport& derived = dynamic_cast<const RiverTransport&>(other);
        return *this == derived;
    }
    catch (const std::bad_cast&)
    {
        return false;
    }
}

double RiverTransport::CalculateDeliveryCost(const double distanceKm, const double weightTons) const
{
    return Transport::CalculateDeliveryCost(distanceKm, weightTons) + lockPassageFee;
}

std::string RiverTransport::ToString() const
{
    return Transport::ToString() +
           " | Осадка: " + FormatDouble(draftMeters) + " м" +
           " | Шлюзовой сбор: " + FormatDouble(lockPassageFee) + " руб.";
}

bool RiverTransport::operator==(const RiverTransport& other) const
{
    return Transport::operator==(other) &&
           AreEqual(draftMeters, other.draftMeters) &&
           AreEqual(lockPassageFee, other.lockPassageFee);
}

bool RiverTransport::operator!=(const RiverTransport& other) const
{
    return !(*this == other);
}
