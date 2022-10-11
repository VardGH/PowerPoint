#include <iostream>
#include "point.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"

int main()
{
    Point ob1(5);
    ob1.print_cordinates();

    Point ob2;
    ob2.set_y(13);
    ob2.print_cordinates();
    std::cout << "distance ob2 and ob1 = " << ob2.get_distance(ob1) << std::endl;

    std::cout << "\n---------\n";
    Line ob_line;
    ob_line.add_line(ob1);
    ob_line.add_line(ob2);
    ob_line.print_line();

    std::cout <<"\n---------\n";
    Circle ob_c;
    ob_c.print_circle();

    std::cout << "\n----------\n";
    Circle ob_c2(4, 6, 7);
    ob_c2.print_circle();

    std::cout << "s = " << ob_c2.get_area() << std::endl;
    std::cout << "l = " << ob_c2.get_circumference() << std::endl;
    std::cout << "d = " << ob_c2.get_diameter() << std::endl;

    std::cout << "\n----------\n";
    Point p1(7, 6);
    Point p2(5, -4);

    Rectangle ob(p1, p2);

    std::cout << "wedth = " << ob.get_width() << std::endl;
    std::cout << "height = " << ob.get_height() << std::endl;
    std::cout << "s = " << ob.get_area() << std::endl;
    std::cout << "p = " << ob.get_perimeter() << std::endl;
    std::cout << "is square? " << std::boolalpha <<ob.is_square() << std::endl;
    std::cout << std::noboolalpha;


    return 0;
}
