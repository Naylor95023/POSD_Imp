#ifndef GRAPHICSVISITOR_H_INCLUDED
#define GRAPHICSVISITOR_H_INCLUDED

#include "Graphics.h"

class GraphicsVisitor{
public:
    virtual void visitSimpleGraphics(SimpleGraphics *s) {}
    virtual void visitCompositeGraphics(CompositeGraphics *c) {}
};

#endif // GRAPHICSVISITOR_H_INCLUDED
