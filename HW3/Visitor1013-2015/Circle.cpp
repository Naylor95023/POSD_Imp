#include "Circle.h"
#include "Rectangle.h"



const int PI=3;

Circle::Circle(int center_x, int center_y, int radius)
    :cx(center_x),cy(center_y),r(radius) {d=new int[10];}

int Circle::area() {return PI*r*r;}
Rectangle Circle::getBoundingBox() {return Rectangle(cx-r,cy-r,2*r,2*r);}

std::string Circle::describe() {
    std::string s;
    std::stringstream ss;
    ss << "C(" << cx << "," << cy << "," << r <<")";
    ss >> s;
    return s;

}


