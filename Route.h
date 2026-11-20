#pragma once

#include <string>

/**
 * @brief Класс маршрута доставки грузов
 */
class Route
{
private:
    /**
     * @brief Уникальный идентификатор маршрута
     */
    std::string id;

    /**
     * @brief Пункт отправления
     */
    std::string origin;

    /**
     * @brief Пункт назначения
     */
    std::string destination;

    /**
     * @brief Протяженность маршрута (км)
     */
    double distanceKm;

    /**
     * @brief Базовая стоимость обслуживания маршрута (руб.)
     */
    double basePrice;

    /**
     * @brief Проверка строки на пустоту и пробелы
     * @param value Проверяемая строка
     * @param fieldName Название поля для текста исключения
     */
    static void ValidateNonEmpty(const std::string& value, const std::string& fieldName);

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Route();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор маршрута
     * @param origin Пункт отправления
     * @param destination Пункт назначения
     * @param distanceKm Протяженность маршрута (км)
     * @param basePrice Базовая стоимость маршрута (руб.)
     */
    Route(const std::string& id,
          const std::string& origin,
          const std::string& destination,
          const double distanceKm,
          const double basePrice);

    /**
     * @brief Деструктор по умолчанию
     */
    ~Route() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый маршрут
     */
    Route(const Route& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый маршрут
     * @return Ссылка на текущий объект
     */
    Route& operator=(const Route& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый маршрут
     */
    Route(Route&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый маршрут
     * @return Ссылка на текущий объект
     */
    Route& operator=(Route&& other) noexcept;

    /**
     * @brief Получить идентификатор маршрута
     * @return Константная ссылка на идентификатор
     */
    const std::string& GetId() const;

    /**
     * @brief Установить идентификатор маршрута
     * @param newId Новый идентификатор
     */
    void SetId(const std::string& newId);

    /**
     * @brief Получить пункт отправления
     * @return Константная ссылка на пункт отправления
     */
    const std::string& GetOrigin() const;

    /**
     * @brief Установить пункт отправления
     * @param newOrigin Новый пункт отправления
     */
    void SetOrigin(const std::string& newOrigin);

    /**
     * @brief Получить пункт назначения
     * @return Константная ссылка на пункт назначения
     */
    const std::string& GetDestination() const;

    /**
     * @brief Установить пункт назначения
     * @param newDestination Новый пункт назначения
     */
    void SetDestination(const std::string& newDestination);

    /**
     * @brief Получить протяженность маршрута (км)
     * @return Протяженность в километрах
     */
    double GetDistanceKm() const;

    /**
     * @brief Установить протяженность маршрута (км)
     * @param distance Новая протяженность
     */
    void SetDistanceKm(const double distance);

    /**
     * @brief Получить базовую цену маршрута (руб.)
     * @return Базовая цена маршрута
     */
    double GetBasePrice() const;

    /**
     * @brief Установить базовую цену маршрута (руб.)
     * @param price Новая базовая цена
     */
    void SetBasePrice(const double price);

    /**
     * @brief Получить краткое название маршрута в формате "Пункт А -> Пункт Б"
     * @return Строка направления маршрута
     */
    std::string GetRouteName() const;

    /**
     * @brief Получить полное строковое описание маршрута
     * @return Строка с характеристиками маршрута
     */
    std::string ToString() const;

    /**
     * @brief Оператор сравнения маршрутов на равенство
     * @param other Маршрут для сравнения
     * @return true, если маршруты равны
     */
    bool operator==(const Route& other) const;

    /**
     * @brief Оператор сравнения маршрутов на неравенство
     * @param other Маршрут для сравнения
     * @return true, если маршруты не равны
     */
    bool operator!=(const Route& other) const;
};
