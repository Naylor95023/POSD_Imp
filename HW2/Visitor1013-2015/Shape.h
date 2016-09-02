#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

class Rectangle;

class Shape {
public:
    virtual ~Shape(){}
    virtual int area() = 0;
    virtual Rectangle getBoundingBox()=0;
};


#endif // SHAPE_H_INCLUDED
