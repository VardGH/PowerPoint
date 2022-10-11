#pragma once

#include <iostream>
#include <vector>
#include "point.h"

class Line
{
public:
    Line() =default;
    ~Line() =default;

    inline void add_line(Point& StraightLine);
    inline std::vector<Point> get_line() const;
    inline void print_line();

private:
    std::vector<Point> m_line;
};

inline void Line::add_line(Point& line)
{
    m_line.push_back(line);
}

inline std::vector<Point> Line::get_line() const
{
    return m_line;
}

inline void Line::print_line()
{
    for(int i = 0; i < m_line.size(); ++i) {
        std::cout << "Cordinate " << i + 1 << " is: ("
        << m_line[i].get_x() << "," << m_line[i].get_y() << ")"<< std::endl;
    }
}
