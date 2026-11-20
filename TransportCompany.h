#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include "CargoOrder.h"
#include "Client.h"
#include "Route.h"
#include "Transport.h"

/**
 * @brief Класс управления транспортной компанией
 */
class TransportCompany
{
private:
    std::string name;
    std::vector<Route*> routes;
    std::vector<Transport*> transports;
    std::map<std::string, std::vector<Transport*>> routeTransports;
    std::vector<Client*> clients;
    std::vector<CargoOrder> orders;

    bool IsTransportAssignedToRoute(const std::string& routeId, const Transport* transport) const;

public:
    TransportCompany();
    explicit TransportCompany(const std::string& name);
    ~TransportCompany() = default;

    TransportCompany(const TransportCompany& other);
    TransportCompany& operator=(const TransportCompany& other);
    TransportCompany(TransportCompany&& other) noexcept;
    TransportCompany& operator=(TransportCompany&& other) noexcept;

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    void AddRoute(Route* route);
    void AddTransport(Transport* transport);
    void AssignTransportToRoute(const std::string& routeId, Transport* transport);
    void AddClient(Client* client);
    void RegisterOrder(const CargoOrder& order);

    Route* FindRouteById(const std::string& routeId) const;
    Transport* FindTransportById(const std::string& transportId) const;
    Client* FindClientById(const std::string& clientId) const;

    /**
     * @brief Задание 1: Получить список маршрутов и базовую цену на них
     * @return Вектор пар <Описание маршрута, Базовая цена>
     */
    std::vector<std::pair<std::string, double>> GetRoutesWithPrices() const;

    /**
     * @brief Задание 1: Текстовый отчет по обслуживаемым маршрутам и ценам
     */
    std::string GetRoutesWithPricesReport() const;

    /**
     * @brief Задание 2: Получить список транспорта, занятого на данном маршруте
     * @param routeId Идентификатор маршрута
     * @return Вектор указателей на базовый класс Transport
     */
    std::vector<Transport*> GetTransportsByRoute(const std::string& routeId) const;

    /**
     * @brief Задание 2: Текстовый отчет по транспорту на маршруте
     * @param routeId Идентификатор маршрута
     */
    std::string GetTransportsByRouteReport(const std::string& routeId) const;

    /**
     * @brief Задание 3: Получить список уникальных вариантов проезда по маршруту (морской, воздушный и т. д.)
     * @param routeId Идентификатор маршрута
     * @return Отсортированный список уникальных видов транспорта
     */
    std::vector<std::string> GetDeliveryOptionsByRoute(const std::string& routeId) const;

    /**
     * @brief Задание 3: Текстовый отчет по вариантам проезда на маршруте
     * @param routeId Идентификатор маршрута
     */
    std::string GetDeliveryOptionsByRouteReport(const std::string& routeId) const;

    /**
     * @brief Задание 4: Рассчитать стоимость перевозки груза с учетом скидки постоянного клиента
     * @param routeId Идентификатор маршрута
     * @param transport Выбранный транспорт
     * @param client Клиент
     * @param weightTons Масса груза (т)
     * @return Итоговая стоимость перевозки
     */
    double CalculateCargoDeliveryCost(const std::string& routeId,
        const Transport* transport,
        const Client* client,
        double weightTons) const;

    /**
     * @brief Задание 4: Получить стоимость зарегистрированного заказа по ID
     * @param orderId Идентификатор заказа
     * @return Итоговая стоимость перевозки
     */
    double CalculateOrderCost(int orderId) const;

    /**
     * @brief Задание 5: Получить суммарный грузооборот по данному маршруту (т*км)
     * @param routeId Идентификатор маршрута
     * @return Грузооборот в тонно-километрах
     */
    double GetRouteFreightTurnover(const std::string& routeId) const;

    /**
     * @brief Получить суммарную массу перевезенных грузов по маршруту (т)
     * @param routeId Идентификатор маршрута
     * @return Масса грузов в тоннах
     */
    double GetRouteTotalCargoWeight(const std::string& routeId) const;

    /**
     * @brief Задание 5: Текстовый отчет по грузообороту на маршруте
     * @param routeId Идентификатор маршрута
     */
    std::string GetRouteFreightTurnoverReport(const std::string& routeId) const;

    const std::vector<Route*>& GetRoutes() const;
    const std::vector<Transport*>& GetTransports() const;
    const std::vector<Client*>& GetClients() const;
    const std::vector<CargoOrder>& GetOrders() const;
};