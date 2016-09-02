#include "Rectangle.h"

Rectangle::Rectangle(int ll_x, int ll_y, int length, int width)
    :x(ll_x),y(ll_y),l(length),w(width) {}
int Rectangle::area() {return l*w;}
Rectangle Rectangle::getBoundingBox() {return Rectangle(x,y,l,w);}

std::string Rectangle::describe() {
    std::string s;
    std::stringstream ss;
    ss << "R(" << x << "," << y << "," << l << "," << w <<")";
    ss >> s;
    return s;
}
