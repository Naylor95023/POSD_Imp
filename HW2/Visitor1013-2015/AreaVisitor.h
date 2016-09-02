#ifndef AREAVISITOR_H_INCLUDED
#define AREAVISITOR_H_INCLUDED

#include "CompositeGraphics.h"
#include "SimpleGraphics.h"

class AreaVisitor {
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
