#pragma once
#include <iostream>
#include "point.h"

#define PI 3.14

class Circle
{
public:
    Circle();
    Circle(Point& center, double radius);
    Circle(double x, double y, double radius);

    inline double get_radius() const;
    inline Point get_center() const;

    inline double get_area() const;
    inline double get_circumference() const;
    inline double get_diameter() const;

    inline void print_circle();

private:
    Point m_center;
    double m_radius;
};

Circle::Circle()
{
    m_center.set_xy(0, 0);
    m_radius = 1;
}

Circle::Circle(Point& center, double radius)
{
    m_center = center;
    m_radius = radius;
}

Circle::Circle(double x, double y, double radius)
{
    m_center.set_xy(x, y);
    m_radius = radius;
}

inline Point Circle::get_center() const
{
    return m_center;
}

inline double Circle::get_radius() const
{
    return m_radius;
}

inline double Circle::get_area() const
{
    return PI * m_radius * m_radius;
}

inline double Circle::get_circumference() const
{
    return 2 * PI * m_radius;
}

inline double Circle::get_diameter() const
{
    return 2 * m_radius;
}

inline void Circle::print_circle()
{
    std::cout << "radius = " << m_radius;
    std::cout << "\nthe coordinate of the center is (" << m_center.get_x() << "," << m_center.get_y() << ")" << std::endl;
}
