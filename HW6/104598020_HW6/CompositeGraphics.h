#ifndef COMPOSITEGRAPHICS_H_INCLUDED
#define COMPOSITEGRAPHICS_H_INCLUDED

#include <vector>
#include "Graphics.h"
#include "GraphicsVisitor.h"


class CompositeGraphics : public Graphics {
public:
    CompositeGraphics();
    void add (Graphics *g);
    Rectangle getBoundingBox();
    void accept(GraphicsVisitor & av);
    void moveGraphics(int posX, int posY);
    void setPainter(Painter * p){painter = p;}
    Painter *  getPainter(){return painter;}
    void ChangePainter (QPointF x);
    int compSize(){return g_obj.size();}
public:
    std::vector<Graphics *> g_obj;
    Painter * painter;
};

#endif // COMPOSITEGRAPHICS_H_INCLUDED
