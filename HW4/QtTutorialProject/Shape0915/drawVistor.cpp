#include "drawVistor.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Rectangle.h"
#include <typeinfo>

drawVistor::drawVistor(QWidget * w, QGraphicsScene * s):widget(w),scene(s){}

void drawVistor::visitSimpleGraphics(SimpleGraphics *sg){
    Painter *item = new Painter(sg,widget);
    painters.push_back(item);
}

void drawVistor::visitCompositeGraphics(CompositeGraphics *cg){
    Painter *item = new Painter(cg,widget);
    painters.push_back(item);
}

void drawVistor::setScene(){
    scene->clear();
    for (auto p:painters)
        scene->addItem(p);
}
