#include "drawVistor.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "Rectangle.h"
#include <typeinfo>

drawVistor::drawVistor(QWidget * w, QGraphicsScene * s, Presentation * p)
    :widget(w),scene(s),present(p){}

void drawVistor::visitSimpleGraphics(SimpleGraphics *sg){
    Painter *item = new Painter(sg, widget, present);
    sg->setPainter(item);
    painters.push_back(item);
}

void drawVistor::visitCompositeGraphics(CompositeGraphics *cg){
    Painter *item = new Painter(cg, widget, present);
    cg->setPainter(item);
    painters.push_back(item);
}

void drawVistor::setScene(){
    scene->clear();
    std::reverse(std::begin(painters),std::end(painters));
    for (auto p:painters)
        scene->addItem(p);
}
