#include "Client.h"
#include "Transport.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace
{
    constexpr double kClientEpsilon = 1e-6;
}

void Client::ValidateNonEmpty(const std::string& value, const std::string& fieldName)
{
    if (value.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument(fieldName + " не может быть пустым");
    }
}

Client::Client()
    : id("CL-0"), name("Не указан"), isRegular(false), discountPercent(0.0)
{
}

Client::Client(const std::string& id,
               const std::string& name,
               const bool isRegular,
               const double discountPercent)
    : id(id),
      name(name),
      isRegular(isRegular),
      discountPercent(discountPercent)
{
    ValidateNonEmpty(this->id, "ID клиента");
    ValidateNonEmpty(this->name, "Имя клиента");
    if (this->discountPercent < 0.0 || this->discountPercent > 100.0)
    {
        throw std::invalid_argument("Скидка должна находиться в диапазоне от 0 до 100%");
    }
}

Client::Client(const Client& other)
    : id(other.id),
      name(other.name),
      isRegular(other.isRegular),
      discountPercent(other.discountPercent)
{
}

Client& Client::operator=(const Client& other)
{
    if (this != &other)
    {
        id = other.id;
        name = other.name;
        isRegular = other.isRegular;
        discountPercent = other.discountPercent;
    }
    return *this;
}

Client::Client(Client&& other) noexcept
    : id(std::move(other.id)),
      name(std::move(other.name)),
      isRegular(other.isRegular),
      discountPercent(other.discountPercent)
{
    other.isRegular = false;
    other.discountPercent = 0.0;
}

Client& Client::operator=(Client&& other) noexcept
{
    if (this != &other)
    {
        id = std::move(other.id);
        name = std::move(other.name);
        isRegular = other.isRegular;
        discountPercent = other.discountPercent;
        other.isRegular = false;
        other.discountPercent = 0.0;
    }
    return *this;
}

const std::string& Client::GetId() const
{
    return id;
}

void Client::SetId(const std::string& newId)
{
    ValidateNonEmpty(newId, "ID клиента");
    id = newId;
}

const std::string& Client::GetName() const
{
    return name;
}

void Client::SetName(const std::string& newName)
{
    ValidateNonEmpty(newName, "Имя клиента");
    name = newName;
}

bool Client::IsRegular() const
{
    return isRegular;
}

void Client::SetRegular(const bool regular)
{
    isRegular = regular;
}

double Client::GetDiscountPercent() const
{
    return discountPercent;
}

void Client::SetDiscountPercent(const double discount)
{
    if (discount < 0.0 || discount > 100.0)
    {
        throw std::invalid_argument("Скидка должна находиться в диапазоне от 0 до 100%");
    }
    discountPercent = discount;
}

double Client::GetEffectiveDiscountPercent() const
{
    return isRegular ? discountPercent : 0.0;
}

std::string Client::ToString() const
{
    return "[Клиент " + id + "] " + name +
           " | Статус: " + (isRegular ? "Постоянный" : "Обычный") +
           " | Скидка: " + Transport::FormatDouble(GetEffectiveDiscountPercent()) + "%";
}

bool Client::operator==(const Client& other) const
{
    return id == other.id &&
           name == other.name &&
           isRegular == other.isRegular &&
           std::fabs(discountPercent - other.discountPercent) < kClientEpsilon;
}

bool Client::operator!=(const Client& other) const
{
    return !(*this == other);
}
