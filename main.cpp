#include <iostream>
#include <memory>
#include <vector>

#include "AirTransport.h"
#include "CargoOrder.h"
#include "Client.h"
#include "RailTransport.h"
#include "RiverTransport.h"
#include "RoadTransport.h"
#include "Route.h"
#include "SeaTransport.h"
#include "Transport.h"
#include "TransportCompany.h"

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0 при успешном завершении
 */
int main()
{
    std::setlocale(LC_ALL, "");

    // Коллекция указателей базового типа Transport, заполненная объектами всех типов-наследников
    std::vector<std::unique_ptr<Transport>> fleet;
    fleet.push_back(std::make_unique<AirTransport>("AIR-1", "Ан-124 Руслан", 120.0, 800.0, 15.0, 11000.0, 5000.0));
    fleet.push_back(std::make_unique<RiverTransport>("RIV-1", "Волго-Дон 5058", 5000.0, 20.0, 2.0, 3.5, 1200.0));
    fleet.push_back(std::make_unique<SeaTransport>("SEA-1", "Контейнеровоз Балтика", 20000.0, 35.0, 1.5, 1500, 8000.0));
    fleet.push_back(std::make_unique<RailTransport>("RAIL-1", "Электровоз ВЛ80", 3000.0, 70.0, 3.0, 50, 2500.0));
    fleet.push_back(std::make_unique<RoadTransport>("ROAD-1", "КАМАЗ-5490", 20.0, 85.0, 5.0, 4, 1500.0));

    // Итерация коллекции как коллекции базового класса Transport с выводом в std::cout
    std::cout << "=== Парк транспорта компании (итерация по базовому классу Transport) ===\n";
    for (const std::unique_ptr<Transport>& item : fleet)
    {
        std::cout << item->ToString() << '\n';
    }
    std::cout << '\n';

    // Настройка транспортной компании, маршрутов и клиентов
    TransportCompany company("Северная Логистика");

    Route routeSpb("R-01", "Москва", "Санкт-Петербург", 700.0, 3500.0);
    Route routeKaliningrad("R-02", "Санкт-Петербург", "Калининград", 1100.0, 6000.0);
    Route routeAstrakhan("R-03", "Нижний Новгород", "Астрахань", 2100.0, 4500.0);

    company.AddRoute(&routeSpb);
    company.AddRoute(&routeKaliningrad);
    company.AddRoute(&routeAstrakhan);

    for (const std::unique_ptr<Transport>& item : fleet)
    {
        company.AddTransport(item.get());
    }

    // Назначение транспорта на маршруты
    company.AssignTransportToRoute("R-01", fleet[0].get()); // Воздушный
    company.AssignTransportToRoute("R-01", fleet[3].get()); // Железнодорожный
    company.AssignTransportToRoute("R-01", fleet[4].get()); // Автомобильный

    company.AssignTransportToRoute("R-02", fleet[0].get()); // Воздушный
    company.AssignTransportToRoute("R-02", fleet[2].get()); // Морской

    company.AssignTransportToRoute("R-03", fleet[1].get()); // Речной
    company.AssignTransportToRoute("R-03", fleet[3].get()); // Железнодорожный

    Client standardClient("CL-1", "ООО Старт", false, 10.0);
    Client regularClient("CL-2", "АО Металлург", true, 15.0);
    company.AddClient(&standardClient);
    company.AddClient(&regularClient);

    // Регистрация заказов
    CargoOrder order1(1, &standardClient, &routeSpb, fleet[4].get(), "Оборудование", 10.0);
    CargoOrder order2(2, &regularClient, &routeSpb, fleet[3].get(), "Металлопрокат", 50.0);
    CargoOrder order3(3, &regularClient, &routeKaliningrad, fleet[2].get(), "Контейнеры", 200.0);

    company.RegisterOrder(order1);
    company.RegisterOrder(order2);
    company.RegisterOrder(order3);

    // Задание 1: Список маршрутов и цены на них
    std::cout << "=== 1. Маршруты и базовые цены ===\n";
    std::cout << company.GetRoutesWithPricesReport() << '\n';

    // Задание 2: Список транспорта на данном маршруте
    std::cout << "=== 2. Транспорт, занятый на маршруте R-01 ===\n";
    std::cout << company.GetTransportsByRouteReport("R-01") << '\n';

    // Задание 3: Варианты проезда по данному маршруту
    std::cout << "=== 3. Варианты проезда по маршрутам ===\n";
    std::cout << company.GetDeliveryOptionsByRouteReport("R-01") << '\n';
    std::cout << company.GetDeliveryOptionsByRouteReport("R-02") << '\n';
    std::cout << company.GetDeliveryOptionsByRouteReport("R-03") << "\n\n";

    // Задание 4: Расчет стоимости перевозки с учетом скидки постоянного клиента
    std::cout << "=== 4. Расчет стоимости перевозки (10 т, маршрут R-01, автомобиль) ===\n";
    const double standardCost = company.CalculateCargoDeliveryCost("R-01", fleet[4].get(), &standardClient, 10.0);
    const double regularCost = company.CalculateCargoDeliveryCost("R-01", fleet[4].get(), &regularClient, 10.0);
    std::cout << standardClient.ToString() << " -> Стоимость: " << Transport::FormatDouble(standardCost) << " руб.\n";
    std::cout << regularClient.ToString() << " -> Стоимость: " << Transport::FormatDouble(regularCost) << " руб.\n\n";

    // Задание 5: Грузооборот по данному маршруту
    std::cout << "=== 5. Грузооборот по маршрутам ===\n";
    std::cout << company.GetRouteFreightTurnoverReport("R-01") << '\n';
    std::cout << company.GetRouteFreightTurnoverReport("R-02") << '\n';
    std::cout << company.GetRouteFreightTurnoverReport("R-03") << '\n';

    return 0;
}
