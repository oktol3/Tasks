#pragma once

#include "Transport.h"

/**
 * @brief Класс речного грузового транспорта
 */
class RiverTransport : public Transport
{
private:
    /**
     * @brief Осадка речного судна (м)
     */
    double draftMeters;

    /**
     * @brief Сбор за прохождение шлюзов (руб.)
     */
    double lockPassageFee;

public:
    /**
     * @brief Конструктор по умолчанию
     */
    RiverTransport();

    /**
     * @brief Конструктор с параметрами
     * @param id Идентификатор речного судна
     * @param name Название речного судна
     * @param capacityTons Грузоподъемность (т)
     * @param speedKmH Средняя скорость (км/ч)
     * @param ratePerTonKm Тариф за тонно-километр (руб.)
     * @param draftMeters Осадка судна (м)
     * @param lockPassageFee Сбор за прохождение шлюзов (руб.)
     */
    RiverTransport(const std::string& id,
                   const std::string& name,
                   const double capacityTons,
                   const double speedKmH,
                   const double ratePerTonKm,
                   const double draftMeters,
                   const double lockPassageFee);

    /**
     * @brief Деструктор по умолчанию
     */
    ~RiverTransport() override = default;

    /**
     * @brief Конструктор копирования
     * @param other Копируемый объект
     */
    RiverTransport(const RiverTransport& other);

    /**
     * @brief Оператор присваивания копированием
     * @param other Присваиваемый объект
     * @return Ссылка на текущий объект
     */
    RiverTransport& operator=(const RiverTransport& other);

    /**
     * @brief Конструктор перемещения
     * @param other Перемещаемый объект
     */
    RiverTransport(RiverTransport&& other) noexcept;

    /**
     * @brief Оператор присваивания перемещением
     * @param other Перемещаемый объект
     * @return Ссылка на текущий объект
     */
    RiverTransport& operator=(RiverTransport&& other) noexcept;

    /**
     * @brief Получить осадку судна (м)
     * @return Осадка судна в метрах
     */
    double GetDraftMeters() const;

    /**
     * @brief Установить осадку судна (м)
     * @param draft Новая осадка судна
     */
    void SetDraftMeters(const double draft);

    /**
     * @brief Получить сбор за прохождение шлюзов (руб.)
     * @return Сумма шлюзового сбора
     */
    double GetLockPassageFee() const;

    /**
     * @brief Установить сбор за прохождение шлюзов (руб.)
     * @param fee Новый шлюзовой сбор
     */
    void SetLockPassageFee(const double fee);

    /**
     * @brief Получить вид транспорта ("Речной")
     * @return Строка "Речной"
     */
    std::string GetTransportType() const override;

    /**
     * @brief Создать полиморфную копию речного транспорта
     * @return Умный указатель на копию объекта
     */
    std::unique_ptr<Transport> Clone() const override;

    /**
     * @brief Полиморфное сравнение с другим объектом транспорта
     * @param other Объект транспорта для сравнения
     * @return true, если объекты равны
     */
    bool Equals(const Transport& other) const override;

    /**
     * @brief Рассчитать стоимость речной перевозки с учетом шлюзового сбора
     * @param distanceKm Протяженность маршрута (км)
     * @param weightTons Масса груза (т)
     * @return Стоимость перевозки (руб.)
     */
    double CalculateDeliveryCost(const double distanceKm, const double weightTons) const override;

    /**
     * @brief Получить полное строковое описание речного судна
     * @return Строка с характеристиками
     */
    std::string ToString() const override;

    /**
     * @brief Оператор равенства двух объектов RiverTransport
     * @param other Объект для сравнения
     * @return true, если объекты равны
     */
    bool operator==(const RiverTransport& other) const;

    /**
     * @brief Оператор неравенства двух объектов RiverTransport
     * @param other Объект для сравнения
     * @return true, если объекты не равны
     */
    bool operator!=(const RiverTransport& other) const;
};
