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
      routeTransportIds(other.routeTransportIds),
      clients(other.clients),
      orders(other.orders)
{
    transports.reserve(other.transports.size());
    for (const std::shared_ptr<Transport>& item : other.transports)
    {
        if (item)
        {
            transports.push_back(std::shared_ptr<Transport>(item->Clone()));
        }
    }
}

TransportCompany& TransportCompany::operator=(const TransportCompany& other)
{
    if (this != &other)
    {
        name = other.name;
        routes = other.routes;
        routeTransportIds = other.routeTransportIds;
        clients = other.clients;
        orders = other.orders;

        transports.clear();
        transports.reserve(other.transports.size());
        for (const std::shared_ptr<Transport>& item : other.transports)
        {
            if (item)
            {
                transports.push_back(std::shared_ptr<Transport>(item->Clone()));
            }
        }
    }
    return *this;
}

TransportCompany::TransportCompany(TransportCompany&& other) noexcept
    : name(std::move(other.name)),
      routes(std::move(other.routes)),
      transports(std::move(other.transports)),
      routeTransportIds(std::move(other.routeTransportIds)),
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
        routeTransportIds = std::move(other.routeTransportIds);
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
                                                  const std::string& transportId) const
{
    const auto it = routeTransportIds.find(routeId);
    if (it == routeTransportIds.end())
    {
        return false;
    }
    return std::find(it->second.begin(), it->second.end(), transportId) != it->second.end();
}

void TransportCompany::AddRoute(const Route& route)
{
    if (HasRoute(route.GetId()))
    {
        throw std::invalid_argument("Маршрут с ID " + route.GetId() + " уже существует");
    }
    routes.push_back(route);
    routeTransportIds[route.GetId()] = {};
}

void TransportCompany::AddTransport(const Transport& transport)
{
    if (HasTransport(transport.GetId()))
    {
        throw std::invalid_argument("Транспорт с ID " + transport.GetId() + " уже зарегистрирован");
    }
    transports.push_back(std::shared_ptr<Transport>(transport.Clone()));
}

void TransportCompany::AssignTransportToRoute(const std::string& routeId, const std::string& transportId)
{
    if (!HasRoute(routeId))
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }
    if (!HasTransport(transportId))
    {
        throw std::invalid_argument("Транспорт с ID " + transportId + " не зарегистрирован");
    }
    if (!IsTransportAssignedToRoute(routeId, transportId))
    {
        routeTransportIds[routeId].push_back(transportId);
    }
}

void TransportCompany::AssignTransportToRoute(const std::string& routeId, const Transport& transport)
{
    if (!HasRoute(routeId))
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }
    if (!HasTransport(transport.GetId()))
    {
        transports.push_back(std::shared_ptr<Transport>(transport.Clone()));
    }
    if (!IsTransportAssignedToRoute(routeId, transport.GetId()))
    {
        routeTransportIds[routeId].push_back(transport.GetId());
    }
}

void TransportCompany::AddClient(const Client& client)
{
    if (HasClient(client.GetId()))
    {
        throw std::invalid_argument("Клиент с ID " + client.GetId() + " уже зарегистрирован");
    }
    clients.push_back(client);
}

void TransportCompany::RegisterOrder(const CargoOrder& order)
{
    if (!order.HasTransport() || order.GetId() <= 0)
    {
        throw std::invalid_argument("Заказ должен быть корректно заполнен и содержать транспорт");
    }
    const std::string& routeId = order.GetRoute().GetId();
    if (!HasRoute(routeId))
    {
        throw std::invalid_argument("Маршрут заказа " + routeId + " не обслуживается компанией");
    }
    if (!IsTransportAssignedToRoute(routeId, order.GetTransport().GetId()))
    {
        throw std::invalid_argument("Выбранный транспорт не назначен на маршрут " + routeId);
    }
    for (const CargoOrder& existing : orders)
    {
        if (existing.GetId() == order.GetId())
        {
            throw std::invalid_argument("Заказ с ID " + std::to_string(order.GetId()) + " уже существует");
        }
    }
    orders.push_back(order);
}

bool TransportCompany::HasRoute(const std::string& routeId) const
{
    return FindRouteById(routeId).has_value();
}

bool TransportCompany::HasTransport(const std::string& transportId) const
{
    return static_cast<bool>(FindTransportById(transportId));
}

bool TransportCompany::HasClient(const std::string& clientId) const
{
    return FindClientById(clientId).has_value();
}

std::optional<Route> TransportCompany::FindRouteById(const std::string& routeId) const
{
    for (const Route& route : routes)
    {
        if (route.GetId() == routeId)
        {
            return route;
        }
    }
    return std::nullopt;
}

std::shared_ptr<const Transport> TransportCompany::FindTransportById(const std::string& transportId) const
{
    for (const std::shared_ptr<Transport>& transport : transports)
    {
        if (transport && transport->GetId() == transportId)
        {
            return transport;
        }
    }
    return nullptr;
}

std::optional<Client> TransportCompany::FindClientById(const std::string& clientId) const
{
    for (const Client& client : clients)
    {
        if (client.GetId() == clientId)
        {
            return client;
        }
    }
    return std::nullopt;
}

std::vector<std::pair<std::string, double>> TransportCompany::GetRoutesWithPrices() const
{
    std::vector<std::pair<std::string, double>> result;
    result.reserve(routes.size());
    for (const Route& route : routes)
    {
        result.emplace_back("[" + route.GetId() + "] " + route.GetRouteName(), route.GetBasePrice());
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
    for (const Route& route : routes)
    {
        report += "  - " + route.ToString() + "\n";
    }
    return report;
}

std::vector<std::shared_ptr<const Transport>> TransportCompany::GetTransportsByRoute(const std::string& routeId) const
{
    if (!HasRoute(routeId))
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    std::vector<std::shared_ptr<const Transport>> result;
    const auto it = routeTransportIds.find(routeId);
    if (it == routeTransportIds.end())
    {
        return result;
    }

    result.reserve(it->second.size());
    for (const std::string& transportId : it->second)
    {
        const std::shared_ptr<const Transport> found = FindTransportById(transportId);
        if (found)
        {
            result.push_back(found);
        }
    }
    return result;
}

std::string TransportCompany::GetTransportsByRouteReport(const std::string& routeId) const
{
    const std::optional<Route> route = FindRouteById(routeId);
    if (!route.has_value())
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    const std::vector<std::shared_ptr<const Transport>> assigned = GetTransportsByRoute(routeId);
    std::string report = "Транспорт на маршруте [" + route->GetId() + "] " + route->GetRouteName() + ":\n";
    if (assigned.empty())
    {
        report += "  (нет назначенного транспорта)\n";
        return report;
    }
    for (const std::shared_ptr<const Transport>& transport : assigned)
    {
        report += "  - " + transport->ToString() + "\n";
    }
    return report;
}

std::vector<std::string> TransportCompany::GetDeliveryOptionsByRoute(const std::string& routeId) const
{
    const std::vector<std::shared_ptr<const Transport>> assigned = GetTransportsByRoute(routeId);
    std::set<std::string> uniqueOptions;
    for (const std::shared_ptr<const Transport>& transport : assigned)
    {
        uniqueOptions.insert(transport->GetTransportType());
    }
    return std::vector<std::string>(uniqueOptions.begin(), uniqueOptions.end());
}

std::string TransportCompany::GetDeliveryOptionsByRouteReport(const std::string& routeId) const
{
    const std::optional<Route> route = FindRouteById(routeId);
    if (!route.has_value())
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
                                                    const Transport& transport,
                                                    const Client& client,
                                                    const double weightTons) const
{
    const std::optional<Route> route = FindRouteById(routeId);
    if (!route.has_value())
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }
    if (!IsTransportAssignedToRoute(routeId, transport.GetId()))
    {
        throw std::invalid_argument("Транспорт " + transport.GetId() + " не обслуживает маршрут " + routeId);
    }

    const double rawCost = route->GetBasePrice() +
                           transport.CalculateDeliveryCost(route->GetDistanceKm(), weightTons);
    const double discountFactor = 1.0 - client.GetEffectiveDiscountPercent() / 100.0;
    return rawCost * discountFactor;
}

double TransportCompany::CalculateOrderCost(const int orderId) const
{
    for (const CargoOrder& order : orders)
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
    if (!HasRoute(routeId))
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    double totalTurnover = 0.0;
    for (const CargoOrder& order : orders)
    {
        if (order.GetRoute().GetId() == routeId)
        {
            totalTurnover += order.GetFreightTurnover();
        }
    }
    return totalTurnover;
}

double TransportCompany::GetRouteTotalCargoWeight(const std::string& routeId) const
{
    if (!HasRoute(routeId))
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    double totalWeight = 0.0;
    for (const CargoOrder& order : orders)
    {
        if (order.GetRoute().GetId() == routeId)
        {
            totalWeight += order.GetWeightTons();
        }
    }
    return totalWeight;
}

std::string TransportCompany::GetRouteFreightTurnoverReport(const std::string& routeId) const
{
    const std::optional<Route> route = FindRouteById(routeId);
    if (!route.has_value())
    {
        throw std::invalid_argument("Маршрут с ID " + routeId + " не найден");
    }

    return "Грузооборот по маршруту [" + route->GetId() + "] " + route->GetRouteName() +
           ": " + Transport::FormatDouble(GetRouteFreightTurnover(routeId)) + " т*км" +
           " (перевезено грузов: " + Transport::FormatDouble(GetRouteTotalCargoWeight(routeId)) + " т)";
}

const std::vector<Route>& TransportCompany::GetRoutes() const
{
    return routes;
}

const std::vector<std::shared_ptr<Transport>>& TransportCompany::GetTransports() const
{
    return transports;
}

const std::vector<Client>& TransportCompany::GetClients() const
{
    return clients;
}

const std::vector<CargoOrder>& TransportCompany::GetOrders() const
{
    return orders;
}
