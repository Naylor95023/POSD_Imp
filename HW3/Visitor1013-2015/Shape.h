#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include <string>
#include <iostream>
#include <sstream>


class Rectangle;

class Shape {
public:
    virtual ~Shape(){}
    virtual int area() = 0;
    virtual Rectangle getBoundingBox()=0;
    virtual std::string describe()=0;
};


#endif // SHAPE_H_INCLUDED
