#include "Square.h"
#include "Rectangle.h"

Square::Square(int ll_x, int ll_y, int length)
    :x(ll_x),y(ll_y),l(length) {}
int Square::area() {return l*l;}
Rectangle Square::getBoundingBox() {return Rectangle(x,y,l,l);}

std::string Square::describe() {
    std::string s;
    std::stringstream ss;
    ss << "S(" << x << "," << y << "," << l <<")";
    ss >> s;
    return s;
}
