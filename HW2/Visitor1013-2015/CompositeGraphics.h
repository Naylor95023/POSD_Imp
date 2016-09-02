#ifndef COMPOSITEGRAPHICS_H_INCLUDED
#define COMPOSITEGRAPHICS_H_INCLUDED

#include "Graphics.h"
#include <vector>
class AreaVisitor;

class CompositeGraphics : public Graphics {
public:
    CompositeGraphics();
    void add (Graphics *g);
    Rectangle getBoundingBox();
    void accept(AreaVisitor & v);
private:
    std::vector<Graphics *> g_obj;
};

#endif // COMPOSITEGRAPHICS_H_INCLUDED
