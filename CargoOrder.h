#pragma once

#include <memory>
#include <string>
#include "Client.h"
#include "Route.h"
#include "Transport.h"

/**
 * @brief Класс заказа на перевозку груза
 */
class CargoOrder
{
private:
    /**
     * @brief Уникальный идентификатор заказа
     */
    int id;

    /**
     * @brief Объект клиента, оформившего заказ
     */
    Client client;

    /**
     * @brief Объект маршрута перевозки
     */
    Route route;

    /**
     * @brief Полиморфный экземпляр транспортного средства, выполняющего заказ
     */
    std::unique_ptr<Transport> transport;

    /**
     * @brief Наименование перевозимого груза
     */
    std::string cargoName;

    /**
     * @brief Масса перевозимого груза (т)
     */
    double weightTons;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    CargoOrder();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор заказа
     * @param client Клиент, оформивший заказ
     * @param route Маршрут доставки
     * @param transport Транспортное средство
     * @param cargoName Наименование груза
     * @param weightTons Масса груза (т)
     */
    CargoOrder(const int id,
               const Client& client,
               const Route& route,
               const Transport& transport,
               const std::string& cargoName,
               const double weightTons);

    /**
     * @brief Деструктор по умолчанию
     */
    ~CargoOrder() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый заказ
     */
    CargoOrder(const CargoOrder& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый заказ
     * @return Ссылка на текущий объект
     */
    CargoOrder& operator=(const CargoOrder& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый заказ
     */
    CargoOrder(CargoOrder&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый заказ
     * @return Ссылка на текущий объект
     */
    CargoOrder& operator=(CargoOrder&& other) noexcept;

    /**
     * @brief Получить идентификатор заказа
     * @return Идентификатор заказа
     */
    int GetId() const;

    /**
     * @brief Получить клиента заказа
     * @return Константная ссылка на объект клиента
     */
    const Client& GetClient() const;

    /**
     * @brief Получить маршрут заказа
     * @return Константная ссылка на объект маршрута
     */
    const Route& GetRoute() const;

    /**
     * @brief Проверить, назначен ли транспорт заказу
     * @return true, если заказ содержит транспорт, иначе false
     */
    bool HasTransport() const;

    /**
     * @brief Получить транспортное средство заказа
     * @return Константная ссылка на базовый класс Transport
     */
    const Transport& GetTransport() const;

    /**
     * @brief Получить наименование груза
     * @return Константная ссылка на наименование груза
     */
    const std::string& GetCargoName() const;

    /**
     * @brief Получить массу груза (т)
     * @return Масса груза в тоннах
     */
    double GetWeightTons() const;

    /**
     * @brief Рассчитать итоговую стоимость перевозки с учетом скидки постоянного клиента
     * @return Итоговая стоимость в рублях
     */
    double CalculateCost() const;

    /**
     * @brief Рассчитать грузооборот по данному заказу (т*км)
     * @return Грузооборот в тонно-километрах
     */
    double GetFreightTurnover() const;

    /**
     * @brief Получить строковое описание заказа
     * @return Строка с информацией о заказе
     */
    std::string ToString() const;

    /**
     * @brief Оператор сравнения заказов на равенство
     * @param other Заказ для сравнения
     * @return true, если заказы равны
     */
    bool operator==(const CargoOrder& other) const;

    /**
     * @brief Оператор сравнения заказов на неравенство
     * @param other Заказ для сравнения
     * @return true, если заказы не равны
     */
    bool operator!=(const CargoOrder& other) const;
};
