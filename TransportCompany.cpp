#include "TransportCompany.h"

#include <algorithm>
#include <set>
#include <stdexcept>
#include <utility>

TransportCompany::TransportCompany()
    : name("Транспортная компания")
{
}

TransportCompany::TransportCompany(const std::string& name)
    : name(name)
{
    if (this->name.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("Название компании не может быть пустым");
    }
}

TransportCompany::TransportCompany(const TransportCompany& other)
    : name(other.name),
    routes(other.routes),
    transports(other.transports),
    routeTransports(other.routeTransports),
    clients(other.clients),
    orders(other.orders)
{
}

TransportCompany& TransportCompany::operator=(const TransportCompany& other)
{
    if (this != &other)
    {
        name = other.name;
        routes = other.routes;
        transports = other.transports;
        routeTransports = other.routeTransports;
        clients = other.clients;
        orders = other.orders;
    }
    return *this;
}

TransportCompany::TransportCompany(TransportCompany&& other) noexcept
    : name(std::move(other.name)),
    routes(std::move(other.routes)),
    transports(std::move(other.transports)),
    routeTransports(std::move(other.routeTransports)),
    clients(std::move(other.clients)),
    orders(std::move(other.orders))
{
}

TransportCompany& TransportCompany::operator=(TransportCompany&& other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        routes = std::move(other.routes);
        transports = std::move(other.transports);
        routeTransports = std::move(other.routeTransports);
        clients = std::move(other.clients);
        orders = std::move(other.orders);
    }
    return *this;
}

const std::string& TransportCompany::GetName() const
{
    return name;
}

void TransportCompany::SetName(const std::string& newName)
{
    if (newName.find_first_not_of(" \t\n\r") == std::string::npos)
    {
        throw std::invalid_argument("Название компании не может быть пустым");
    }
    name = newName;
}

bool TransportCompany::IsTransportAssignedToRoute(const std::string& routeId,
    const Transport* transport) const
{
    const auto it = routeTransports.find(routeId);
    if (it == routeTransports.end())
    {
        return false;
    }
    return std::find(it->second.begin(), it->second.end(), transport) != it->second.end();
}

void TransportCompany::AddRoute(Route* route)
{
    if (route == nullptr)
    {
        throw std::invalid_argument("Нельзя добавить пустой указатель на маршрут");
    }
    if (FindRouteById(route->GetId()) != nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + route->GetId() + " уже существует");
    }
    routes.push_back(route);
    routeTransports[route->GetId()] = {};
}

void TransportCompany::AddTransport(Transport* transport)
{
    if (transport == nullptr)
    {
        throw std::invalid_argument("Нельзя добавить пустой указатель на транспорт");
    }
    if (FindTransportById(transport->GetId()) != nullptr)
    {
        throw std::invalid_argument("Транспорт с ID " + transport->GetId() + " уже зарегистрирован");
    }
    transports.push_back(transport);
}

void TransportCompany::AssignTransportToRoute(const std::string& routeId, Transport* transport)
{
    if (transport == nullptr)
    {
        throw std::invalid_argument("Нельзя назначить пустой указатель на транспорт");
    }
    if (FindRouteById(routeId) == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }
    if (FindTransportById(transport->GetId()) == nullptr)
    {
        transports.push_back(transport);
    }
    if (!IsTransportAssignedToRoute(routeId, transport))
    {
        routeTransports[routeId].push_back(transport);
    }
}

void TransportCompany::AddClient(Client* client)
{
    if (client == nullptr)
    {
        throw std::invalid_argument("Нельзя добавить пустой указатель на клиента");
    }
    if (FindClientById(client->GetId()) != nullptr)
    {
        throw std::invalid_argument("Клиент с ID " + client->GetId() + " уже зарегистрирован");
    }
    clients.push_back(client);
}

void TransportCompany::RegisterOrder(const CargoOrder& order)
{
    if (order.GetRoute() == nullptr || order.GetTransport() == nullptr || order.GetClient() == nullptr)
    {
        throw std::invalid_argument("Заказ должен содержать валидные маршрут, транспорт и клиента");
    }
    const std::string& routeId = order.GetRoute()->GetId();
    if (FindRouteById(routeId) == nullptr)
    {
        throw std::invalid_argument("Маршрут заказа " + routeId + " не обслуживается компанией");
    }
    if (!IsTransportAssignedToRoute(routeId, order.GetTransport()))
    {
        throw std::invalid_argument("Выбранный транспорт не назначен на маршрут " + routeId);
    }
    for (const auto& existing : orders)
    {
        if (existing.GetId() == order.GetId())
        {
            throw std::invalid_argument("Заказ с ID " + std::to_string(order.GetId()) + " уже существует");
        }
    }
    orders.push_back(order);
}

Route* TransportCompany::FindRouteById(const std::string& routeId) const
{
    for (Route* route : routes)
    {
        if (route->GetId() == routeId)
        {
            return route;
        }
    }
    return nullptr;
}

Transport* TransportCompany::FindTransportById(const std::string& transportId) const
{
    for (Transport* transport : transports)
    {
        if (transport->GetId() == transportId)
        {
            return transport;
        }
    }
    return nullptr;
}

Client* TransportCompany::FindClientById(const std::string& clientId) const
{
    for (Client* client : clients)
    {
        if (client->GetId() == clientId)
        {
            return client;
        }
    }
    return nullptr;
}

std::vector<std::pair<std::string, double>> TransportCompany::GetRoutesWithPrices() const
{
    std::vector<std::pair<std::string, double>> result;
    result.reserve(routes.size());
    for (const Route* route : routes)
    {
        result.emplace_back("[" + route->GetId() + "] " + route->GetRouteName(), route->GetBasePrice());
    }
    return result;
}

std::string TransportCompany::GetRoutesWithPricesReport() const
{
    if (routes.empty())
    {
        return "Компания не обслуживает маршруты.";
    }
    std::string report = "Маршруты компании \"" + name + "\":\n";
    for (const Route* route : routes)
    {
        report += "  - " + route->ToString() + "\n";
    }
    return report;
}

std::vector<Transport*> TransportCompany::GetTransportsByRoute(const std::string& routeId) const
{
    if (FindRouteById(routeId) == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }
    const auto it = routeTransports.find(routeId);
    if (it == routeTransports.end())
    {
        return {};
    }
    return it->second;
}

std::string TransportCompany::GetTransportsByRouteReport(const std::string& routeId) const
{
    const Route* route = FindRouteById(routeId);
    if (route == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    const std::vector<Transport*> assigned = GetTransportsByRoute(routeId);
    std::string report = "Транспорт на маршруте [" + route->GetId() + "] " + route->GetRouteName() + ":\n";
    if (assigned.empty())
    {
        report += "  (нет назначенного транспорта)\n";
        return report;
    }
    for (const Transport* transport : assigned)
    {
        report += "  - " + transport->ToString() + "\n";
    }
    return report;
}

std::vector<std::string> TransportCompany::GetDeliveryOptionsByRoute(const std::string& routeId) const
{
    const std::vector<Transport*> assigned = GetTransportsByRoute(routeId);
    std::set<std::string> uniqueOptions;
    for (const Transport* transport : assigned)
    {
        uniqueOptions.insert(transport->GetTransportType());
    }
    return std::vector<std::string>(uniqueOptions.begin(), uniqueOptions.end());
}

std::string TransportCompany::GetDeliveryOptionsByRouteReport(const std::string& routeId) const
{
    const Route* route = FindRouteById(routeId);
    if (route == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    const std::vector<std::string> options = GetDeliveryOptionsByRoute(routeId);
    std::string report = "Варианты доставки по маршруту [" + route->GetId() + "] " + route->GetRouteName() + ": ";
    if (options.empty())
    {
        return report + "нет доступных вариантов.";
    }
    for (size_t i = 0; i < options.size(); ++i)
    {
        report += options[i];
        if (i + 1 < options.size())
        {
            report += ", ";
        }
    }
    return report;
}

double TransportCompany::CalculateCargoDeliveryCost(const std::string& routeId,
    const Transport* transport,
    const Client* client,
    const double weightTons) const
{
    const Route* route = FindRouteById(routeId);
    if (route == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }
    if (transport == nullptr)
    {
        throw std::invalid_argument("Транспорт не может быть nullptr");
    }
    if (client == nullptr)
    {
        throw std::invalid_argument("Клиент не может быть nullptr");
    }
    if (!IsTransportAssignedToRoute(routeId, transport))
    {
        throw std::invalid_argument("Транспорт " + transport->GetId() + " не обслуживает маршрут " + routeId);
    }

    const double rawCost = route->GetBasePrice() +
        transport->CalculateDeliveryCost(route->GetDistanceKm(), weightTons);
    const double discountFactor = 1.0 - client->GetEffectiveDiscountPercent() / 100.0;
    return rawCost * discountFactor;
}

double TransportCompany::CalculateOrderCost(const int orderId) const
{
    for (const auto& order : orders)
    {
        if (order.GetId() == orderId)
        {
            return order.CalculateCost();
        }
    }
    throw std::invalid_argument("Заказ с ID " + std::to_string(orderId) + " не найден");
}

double TransportCompany::GetRouteFreightTurnover(const std::string& routeId) const
{
    if (FindRouteById(routeId) == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    double totalTurnover = 0.0;
    for (const auto& order : orders)
    {
        if (order.GetRoute() != nullptr && order.GetRoute()->GetId() == routeId)
        {
            totalTurnover += order.GetFreightTurnover();
        }
    }
    return totalTurnover;
}

double TransportCompany::GetRouteTotalCargoWeight(const std::string& routeId) const
{
    if (FindRouteById(routeId) == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    double totalWeight = 0.0;
    for (const auto& order : orders)
    {
        if (order.GetRoute() != nullptr && order.GetRoute()->GetId() == routeId)
        {
            totalWeight += order.GetWeightTons();
        }
    }
    return totalWeight;
}

std::string TransportCompany::GetRouteFreightTurnoverReport(const std::string& routeId) const
{
    const Route* route = FindRouteById(routeId);
    if (route == nullptr)
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    return "Грузооборот по маршруту [" + route->GetId() + "] " + route->GetRouteName() +
        ": " + Transport::FormatDouble(GetRouteFreightTurnover(routeId)) + " т*км" +
        " (перевезено грузов: " + Transport::FormatDouble(GetRouteTotalCargoWeight(routeId)) + " т)";
}

const std::vector<Route*>& TransportCompany::GetRoutes() const
{
    return routes;
}

const std::vector<Transport*>& TransportCompany::GetTransports() const
{
    return transports;
}

const std::vector<Client*>& TransportCompany::GetClients() const
{
    return clients;
}

const std::vector<CargoOrder>& TransportCompany::GetOrders() const
{
    return orders;
}