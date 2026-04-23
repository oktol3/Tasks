#pragma once
/**
    @brief   класс точка
**/
class point {
private:
    /**
        @brief переменная x
    **/
    double x1;
    /**
        @brief переменная y
    **/
    double y1;
    /**
        @brief переменная z
    **/
    double z1;
public:
    /**
        @brief конструктор
        @param x - координата точки
        @param y - координата точки
        @param z - координата точки
    **/
    point(const double x1 = 0, const double y1 = 0, const double z1 = 0);
    /**
     * @breif получить координату точки
     * @return - координата x
     */
    double x() const;
    /**
     * @breif получить координату точки
     * @return - координата y
     */
    double y() const;
    /**
     * @breif получить координату точки
     * @return - координата z
     */
    double z() const;

};
