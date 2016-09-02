#include "SimpleGraphics.h"
#include "AreaVisitor.h"

void SimpleGraphics::accept(AreaVisitor &v){
        v.visitSimpleGraphics(this);
}
