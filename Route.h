#pragma once

#include <string>

/**
 * @brief Класс маршрута доставки грузов
 */
class Route
{
private:
    std::string id;
    std::string origin;
    std::string destination;
    double distanceKm;
    double basePrice;

    static void ValidateNonEmpty(const std::string& value, const std::string& fieldName);

public:
    Route();
    Route(const std::string& id,
        const std::string& origin,
        const std::string& destination,
        double distanceKm,
        double basePrice);
    ~Route() = default;

    Route(const Route& other);
    Route& operator=(const Route& other);
    Route(Route&& other) noexcept;
    Route& operator=(Route&& other) noexcept;

    const std::string& GetId() const;
    void SetId(const std::string& newId);

    const std::string& GetOrigin() const;
    void SetOrigin(const std::string& newOrigin);

    const std::string& GetDestination() const;
    void SetDestination(const std::string& newDestination);

    double GetDistanceKm() const;
    void SetDistanceKm(double distance);

    double GetBasePrice() const;
    void SetBasePrice(double price);

    /**
     * @brief Получить краткое название маршрута ("Пункт А -> Пункт Б")
     */
    std::string GetRouteName() const;

    /**
     * @brief Полное строковое описание маршрута
     */
    std::string ToString() const;

    bool operator==(const Route& other) const;
    bool operator!=(const Route& other) const;
};