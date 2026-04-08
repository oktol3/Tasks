#pragma once
class point {
private:
    double x1;
    double y1;
    double z1;
public:
    point(const double x1 = 0, const double y1 = 0, const double z1 = 0);
    double x() const;
    double y() const;
    double z() const;

};

