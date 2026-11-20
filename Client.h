#pragma once

#include <string>

/**
 * @brief Класс клиента транспортной компании
 */
class Client
{
private:
    /**
     * @brief Уникальный идентификатор клиента
     */
    std::string id;

    /**
     * @brief ФИО или наименование организации клиента
     */
    std::string name;

    /**
     * @brief Признак постоянного клиента
     */
    bool isRegular;

    /**
     * @brief Процент скидки постоянного клиента (от 0 до 100)
     */
    double discountPercent;

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
    Client();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор клиента
     * @param name Имя / наименование клиента
     * @param isRegular Флаг постоянного клиента
     * @param discountPercent Размер скидки в процентах (0..100)
     */
    Client(const std::string& id,
           const std::string& name,
           const bool isRegular = false,
           const double discountPercent = 0.0);

    /**
     * @brief Деструктор по умолчанию
     */
    ~Client() = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый клиент
     */
    Client(const Client& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый клиент
     * @return Ссылка на текущий объект
     */
    Client& operator=(const Client& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый клиент
     */
    Client(Client&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый клиент
     * @return Ссылка на текущий объект
     */
    Client& operator=(Client&& other) noexcept;

    /**
     * @brief Получить идентификатор клиента
     * @return Константная ссылка на идентификатор
     */
    const std::string& GetId() const;

    /**
     * @brief Установить идентификатор клиента
     * @param newId Новый идентификатор
     */
    void SetId(const std::string& newId);

    /**
     * @brief Получить имя / наименование клиента
     * @return Константная ссылка на имя клиента
     */
    const std::string& GetName() const;

    /**
     * @brief Установить имя / наименование клиента
     * @param newName Новое имя клиента
     */
    void SetName(const std::string& newName);

    /**
     * @brief Проверить, является ли клиент постоянным
     * @return true, если клиент постоянный, иначе false
     */
    bool IsRegular() const;

    /**
     * @brief Установить статус постоянного клиента
     * @param regular Новое значение флага постоянного клиента
     */
    void SetRegular(const bool regular);

    /**
     * @brief Получить назначенный процент скидки
     * @return Процент скидки
     */
    double GetDiscountPercent() const;

    /**
     * @brief Установить процент скидки
     * @param discount Новый процент скидки (0..100)
     */
    void SetDiscountPercent(const double discount);

    /**
     * @brief Получить действующий процент скидки (0, если клиент не является постоянным)
     * @return Действующая скидка в процентах
     */
    double GetEffectiveDiscountPercent() const;

    /**
     * @brief Получить строковое описание клиента
     * @return Строка с данными о клиенте и его скидке
     */
    std::string ToString() const;

    /**
     * @brief Оператор сравнения клиентов на равенство
     * @param other Клиент для сравнения
     * @return true, если клиенты равны
     */
    bool operator==(const Client& other) const;

    /**
     * @brief Оператор сравнения клиентов на неравенство
     * @param other Клиент для сравнения
     * @return true, если клиенты не равны
     */
    bool operator!=(const Client& other) const;
};
