#pragma once
/**
    @brief   класс точка
**/
class point {
private:
    double x1;
    double y1;
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

