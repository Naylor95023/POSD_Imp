#include "SimpleGraphics.h"
#include "Rectangle.h"
#include "AreaVisitor.h"
#include "Painter.h"

SimpleGraphics::SimpleGraphics (Shape *shape_inst):s(shape_inst) {
}
Rectangle SimpleGraphics::getBoundingBox() {return s->getBoundingBox();}
void SimpleGraphics::accept(GraphicsVisitor &av) {av.visitSimpleGraphics(this);}
Shape * SimpleGraphics::shape() {return s;}
void SimpleGraphics::moveGraphics(int posX, int posY){
    this->s->setNewPos(posX, posY);
}

void SimpleGraphics::ChangePainter(QPointF x){
    painter->setLocation(x);
}
