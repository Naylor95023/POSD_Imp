#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <QPointF>

class Painter;
class Rectangle;
class GraphicsVisitor;

class Graphics {
public:
    virtual ~Graphics();
    virtual Rectangle getBoundingBox();
    virtual void add(Graphics *g);
    virtual void accept(GraphicsVisitor & av);
    virtual void moveGraphics(int posX, int posY);
    virtual void setPainter(Painter * p){}
    virtual Painter * getPainter() = 0;
    virtual void ChangePainter(QPointF x) = 0;

protected:
    Graphics();
};

#endif // GRAPHICS_H_INCLUDED
