#include "SimpleGraphics.h"
#include "AreaVisitor.h"

void SimpleGraphics::accept(GraphicsVisitor &v){
        v.visitSimpleGraphics(this);
}
