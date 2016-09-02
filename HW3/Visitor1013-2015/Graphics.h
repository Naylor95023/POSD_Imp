#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "Rectangle.h"
#include <string>

//GraphicsVisitor and Graphic's classes depend on each other,
//so having to declare "class GraphicsVisitor" here first,
//because in "method accept" have used GraphicsVisitor.
class GraphicsVisitor;

class Graphics {
public:
    virtual ~Graphics() {}
    virtual Rectangle getBoundingBox() {return Rectangle(0,0,0,0);}
    virtual void add(Graphics *g) {throw std::string("Cannot add child");}
    virtual void accept(GraphicsVisitor & v) {}
protected:
    Graphics() {}
};

#endif // GRAPHICS_H_INCLUDED
