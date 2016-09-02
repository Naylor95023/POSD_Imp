#ifndef AREAVISITOR_H_INCLUDED
#define AREAVISITOR_H_INCLUDED

#include "CompositeGraphics.h"
#include "SimpleGraphics.h"
#include "GraphicsVisitor.h"

class AreaVisitor : public GraphicsVisitor {
public:
    AreaVisitor():a(0) {}
    void visitSimpleGraphics(SimpleGraphics *s) {
      a += s->getShape()->area();
    }
    void visitCompositeGraphics(CompositeGraphics *c) {}
    int area() {return a;}
private:
    int a;
};

#endif // AREAVISITOR_H_INCLUDED
