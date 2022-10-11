#pragma once

#include "point.h"

class Rectangle
{
public:
    Rectangle();
    Rectangle(Point p1, Point p2);

    inline double get_width() const;
    inline double get_height() const;
    inline double get_area() const;
    inline double get_perimeter() const;

    inline bool is_square() const;

private:
    Point top_right;
    Point bottom_left;
};

Rectangle::Rectangle()
{
    bottom_left.set_xy(0, 0);
    top_right.set_xy(1 , 1);
}

Rectangle::Rectangle(Point p1, Point p2)
{
    bottom_left = p1;
    top_right = p2;
}

inline double Rectangle::get_width() const
{
    double temp_max = std::max(top_right.get_y(), bottom_left.get_y());
    double temp_min = std::min(top_right.get_y(), bottom_left.get_y());
    return temp_max - temp_min;
}

inline double Rectangle::get_height() const
{
    double temp_max = std::max(top_right.get_x(), bottom_left.get_x());
    double temp_min = std::min(top_right.get_x(), bottom_left.get_x());
    return temp_max - temp_min;
}

inline double Rectangle::get_area() const
{
    return this -> get_width() * this -> get_height();
}

inline double Rectangle::get_perimeter() const
{
    return 2 * (this -> get_width() + this -> get_height());
}

inline bool Rectangle::is_square() const
{
    return this -> get_width() - this -> get_height() == 0;
}
