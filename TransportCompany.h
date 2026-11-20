#pragma once

#include <map>
#include <memory>
#include <optional>
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
    /**
     * @brief Название транспортной компании
     */
    std::string name;

    /**
     * @brief Коллекция обслуживаемых маршрутов
     */
    std::vector<Route> routes;

    /**
     * @brief Полиморфная коллекция транспортных средств компании
     */
    std::vector<std::shared_ptr<Transport>> transports;

    /**
     * @brief Соответствие идентификатора маршрута списку идентификаторов назначенного транспорта
     */
    std::map<std::string, std::vector<std::string>> routeTransportIds;

    /**
     * @brief Коллекция зарегистрированных клиентов
     */
    std::vector<Client> clients;

    /**
     * @brief Коллекция зарегистрированных заказов на перевозку
     */
    std::vector<CargoOrder> orders;

    /**
     * @brief Проверить, назначен ли транспорт с указанным ID на заданный маршрут
     * @param routeId Идентификатор маршрута
     * @param transportId Идентификатор транспорта
     * @return true, если транспорт назначен на маршрут, иначе false
     */
    bool IsTransportAssignedToRoute(const std::string& routeId, const std::string& transportId) const;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    TransportCompany();

    /**
     * @brief Конструктор с параметром названия компании
     * @param name Название транспортной компании
     */
    explicit TransportCompany(const std::string& name);

    /**
     * @brief Деструктор по умолчанию
     */
    ~TransportCompany() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект компании
     */
    TransportCompany(const TransportCompany& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект компании
     * @return Ссылка на текущий объект
     */
    TransportCompany& operator=(const TransportCompany& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект компании
     */
    TransportCompany(TransportCompany&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект компании
     * @return Ссылка на текущий объект
     */
    TransportCompany& operator=(TransportCompany&& other) noexcept;

    /**
     * @brief Получить название компании
     * @return Константная ссылка на название компании
     */
    const std::string& GetName() const;

    /**
     * @brief Установить новое название компании
     * @param newName Новое название компании
     */
    void SetName(const std::string& newName);

    /**
     * @brief Добавить новый маршрут в список обслуживаемых компанией
     * @param route Объект маршрута
     */
    void AddRoute(const Route& route);

    /**
     * @brief Зарегистрировать транспортное средство в парке компании
     * @param transport Объект транспортного средства
     */
    void AddTransport(const Transport& transport);

    /**
     * @brief Назначить зарегистрированный транспорт на маршрут по его идентификатору
     * @param routeId Идентификатор маршрута
     * @param transportId Идентификатор транспорта
     */
    void AssignTransportToRoute(const std::string& routeId, const std::string& transportId);

    /**
     * @brief Назначить транспорт на маршрут
     * @param routeId Идентификатор маршрута
     * @param transport Объект транспортного средства
     */
    void AssignTransportToRoute(const std::string& routeId, const Transport& transport);

    /**
     * @brief Зарегистрировать нового клиента компании
     * @param client Объект клиента
     */
    void AddClient(const Client& client);

    /**
     * @brief Зарегистрировать заказ на перевозку груза
     * @param order Объект заказа
     */
    void RegisterOrder(const CargoOrder& order);

    /**
     * @brief Проверить наличие маршрута по идентификатору
     * @param routeId Идентификатор маршрута
     * @return true, если маршрут обслуживается компанией
     */
    bool HasRoute(const std::string& routeId) const;

    /**
     * @brief Проверить наличие транспорта в парке по идентификатору
     * @param transportId Идентификатор транспорта
     * @return true, если транспорт зарегистрирован
     */
    bool HasTransport(const std::string& transportId) const;

    /**
     * @brief Проверить наличие клиента по идентификатору
     * @param clientId Идентификатор клиента
     * @return true, если клиент зарегистрирован
     */
    bool HasClient(const std::string& clientId) const;

    /**
     * @brief Найти маршрут по идентификатору
     * @param routeId Идентификатор маршрута
     * @return Найденный объект маршрута или std::nullopt
     */
    std::optional<Route> FindRouteById(const std::string& routeId) const;

    /**
     * @brief Найти транспортное средство по идентификатору
     * @param transportId Идентификатор транспорта
     * @return Умный указатель на константный транспорт или пустой shared_ptr
     */
    std::shared_ptr<const Transport> FindTransportById(const std::string& transportId) const;

    /**
     * @brief Найти клиента по идентификатору
     * @param clientId Идентификатор клиента
     * @return Найденный объект клиента или std::nullopt
     */
    std::optional<Client> FindClientById(const std::string& clientId) const;

    /**
     * @brief Получить список маршрутов, обслуживаемых компанией, и базовую цену на них
     * @return Вектор пар <Описание маршрута, Базовая цена>
     */
    std::vector<std::pair<std::string, double>> GetRoutesWithPrices() const;

    /**
     * @brief Сформировать текстовый отчет по обслуживаемым маршрутам и ценам
     * @return Строка отчета
     */
    std::string GetRoutesWithPricesReport() const;

    /**
     * @brief Получить список транспорта, занятого на данном маршруте
     * @param routeId Идентификатор маршрута
     * @return Вектор умных указателей на константный базовый класс Transport
     */
    std::vector<std::shared_ptr<const Transport>> GetTransportsByRoute(const std::string& routeId) const;

    /**
     * @brief Сформировать текстовый отчет по транспорту, занятому на маршруте
     * @param routeId Идентификатор маршрута
     * @return Строка отчета
     */
    std::string GetTransportsByRouteReport(const std::string& routeId) const;

    /**
     * @brief Получить список уникальных вариантов проезда по данному маршруту
     * @param routeId Идентификатор маршрута
     * @return Отсортированный вектор названий доступных видов транспорта
     */
    std::vector<std::string> GetDeliveryOptionsByRoute(const std::string& routeId) const;

    /**
     * @brief Сформировать текстовый отчет по вариантам проезда на маршруте
     * @param routeId Идентификатор маршрута
     * @return Строка отчета
     */
    std::string GetDeliveryOptionsByRouteReport(const std::string& routeId) const;

    /**
     * @brief Рассчитать стоимость перевозки груза с учетом скидки постоянного клиента
     * @param routeId Идентификатор маршрута
     * @param transport Выбранное транспортное средство
     * @param client Клиент, оформляющий перевозку
     * @param weightTons Масса груза (т)
     * @return Итоговая стоимость перевозки в рублях
     */
    double CalculateCargoDeliveryCost(const std::string& routeId,
                                      const Transport& transport,
                                      const Client& client,
                                      const double weightTons) const;

    /**
     * @brief Получить итоговую стоимость ранее зарегистрированного заказа по ID
     * @param orderId Идентификатор заказа
     * @return Стоимость перевозки в рублях
     */
    double CalculateOrderCost(const int orderId) const;

    /**
     * @brief Получить суммарный грузооборот по данному маршруту (т*км)
     * @param routeId Идентификатор маршрута
     * @return Грузооборот в тонно-километрах
     */
    double GetRouteFreightTurnover(const std::string& routeId) const;

    /**
     * @brief Получить суммарную массу перевезенных грузов по маршруту (т)
     * @param routeId Идентификатор маршрута
     * @return Суммарная масса грузов в тоннах
     */
    double GetRouteTotalCargoWeight(const std::string& routeId) const;

    /**
     * @brief Сформировать текстовый отчет по грузообороту на маршруте
     * @param routeId Идентификатор маршрута
     * @return Строка отчета
     */
    std::string GetRouteFreightTurnoverReport(const std::string& routeId) const;

    /**
     * @brief Получить коллекцию всех маршрутов компании
     * @return Константная ссылка на вектор объектов Route
     */
    const std::vector<Route>& GetRoutes() const;

    /**
     * @brief Получить коллекцию всего транспорта компании
     * @return Константная ссылка на вектор умных указателей на Transport
     */
    const std::vector<std::shared_ptr<Transport>>& GetTransports() const;

    /**
     * @brief Получить коллекцию всех клиентов компании
     * @return Константная ссылка на вектор объектов Client
     */
    const std::vector<Client>& GetClients() const;

    /**
     * @brief Получить коллекцию всех заказов компании
     * @return Константная ссылка на вектор объектов CargoOrder
     */
    const std::vector<CargoOrder>& GetOrders() const;
};
