#pragma once

#include <string>

/**
 * @brief Класс клиента транспортной компании
 */
class Client
{
private:
    std::string id;
    std::string name;
    bool isRegular;
    double discountPercent;

    static void ValidateNonEmpty(const std::string& value, const std::string& fieldName);

public:
    Client();
    Client(const std::string& id,
        const std::string& name,
        bool isRegular = false,
        double discountPercent = 0.0);
    ~Client() = default;

    Client(const Client& other);
    Client& operator=(const Client& other);
    Client(Client&& other) noexcept;
    Client& operator=(Client&& other) noexcept;

    const std::string& GetId() const;
    void SetId(const std::string& newId);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    bool IsRegular() const;
    void SetRegular(bool regular);

    double GetDiscountPercent() const;
    void SetDiscountPercent(double discount);

    /**
     * @brief Получить действующий процент скидки (0, если клиент не постоянный)
     * @return Действующая скидка в процентах
     */
    double GetEffectiveDiscountPercent() const;

    std::string ToString() const;

    bool operator==(const Client& other) const;
    bool operator!=(const Client& other) const;
};