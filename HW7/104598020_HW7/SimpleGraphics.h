#ifndef SIMPLEGRAPHICS_H_INCLUDED
#define SIMPLEGRAPHICS_H_INCLUDED

#include "Graphics.h"
#include "Shape.h"
#include <iostream>


class SimpleGraphics : public Graphics {
public:
    SimpleGraphics (Shape *shape_inst);
    Rectangle getBoundingBox();
    void accept(GraphicsVisitor &av);
    void moveGraphics(int posX, int posY);
    void setPainter(Painter * p){painter = p;}
    Painter * getPainter(){return painter;}
    void ChangePainter(QPointF x);
    Shape * shape();
private:
    Shape * s;
    Painter * painter;
};


#endif // SIMPLEGRAPHICS_H_INCLUDED
