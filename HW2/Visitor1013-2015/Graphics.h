#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "Rectangle.h"
#include <string>
class AreaVisitor;

class Graphics {
public:
    virtual ~Graphics() {}
    virtual Rectangle getBoundingBox() {return Rectangle(0,0,0,0);}
    virtual void add(Graphics *g) {throw std::string("Cannot add child");}
    virtual void accept(AreaVisitor & v) {}
protected:
    Graphics() {}
};

#endif // GRAPHICS_H_INCLUDED
