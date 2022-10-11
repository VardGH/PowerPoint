#pragma once

#include <iostream>
#include <cmath>

class Point
{
public:
    Point() : m_x(0), m_y(0) {}
    Point(double x, double y = 0) : m_x(x), m_y(y) {}

    inline double get_x() const;
    inline double get_y() const;
    inline double get_distance(Point) const;

    inline void set_x(const double);
    inline void set_y(const double);
    inline void set_xy(const double, const double);

    inline void print_cordinates();

private:
    double m_x;
    double m_y;
};

inline void Point::print_cordinates()
{
    std::cout << "Cordinates are: (" << m_x << "," << m_y << ")" << std::endl;
}

inline double Point::get_x() const
{
    return m_x;
}

inline double Point::get_y() const
{
    return m_y;
}

inline double Point::get_distance(Point p) const
{
    return sqrt(pow(this -> get_x() - p.get_x(), 2) + pow(this ->get_y() - p.get_y(), 2));
}

inline void Point::set_x(const double x)
{
    m_x = x;
}

inline void Point::set_y(const double y)
{
    m_y = y;
}

inline void Point::set_xy(const double x, const double y)
{
    m_x = x;
    m_y = y;
}
