#ifndef SIMPLEGRAPHICS_H_INCLUDED
#define SIMPLEGRAPHICS_H_INCLUDED

#include "Graphics.h"
#include "Shape.h"
class AreaVisitor;

class SimpleGraphics : public Graphics {
public:
    SimpleGraphics (Shape *shape_inst):s(shape_inst) {}
    Rectangle getBoundingBox() {return s->getBoundingBox();}
    Shape * getShape() {return s;}
    void accept(GraphicsVisitor &v) ;
private:
    Shape * s;
};


#endif // SIMPLEGRAPHICS_H_INCLUDED
