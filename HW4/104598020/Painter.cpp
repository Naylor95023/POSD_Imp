#include "Painter.h"
#include <typeinfo>

Painter::Painter(Graphics * g,QWidget *_widget)
{
    //ctor
    this->g = g;
    //get Graphics and set x,y,w,h
    int width = g->getBoundingBox().urx()- g->getBoundingBox().llx();
    int heigh = g->getBoundingBox().ury()- g->getBoundingBox().lly();
    posx = g->getBoundingBox().llx();
    posy = g->getBoundingBox().lly();
    this->width = width;
    this->heigh = heigh;
    widget = _widget;
}

Painter::~Painter()
{
    //dtor
}

QRectF Painter::boundingRect() const
{
    return QRectF(posx,posy,width,heigh);
}

//if g is simple , cast to simple *,judge is circle
//else paint by blue pen
void Painter::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    if(typeid((*g)) == typeid(SimpleGraphics)){
        QPen pen(Qt::blue);
        painter->setPen(pen);
        SimpleGraphics * sg = reinterpret_cast<SimpleGraphics *>(g);
        if(typeid(*sg->shape()) == typeid(Circle)){
            painter->drawEllipse(posx, posy, width, heigh);
        }else{
            painter->drawRect(posx, posy, width, heigh);
        }
    }else{
        QPen pen(Qt::green);
        painter->setPen(pen);
        painter->drawRect(posx, posy, width, heigh);
    }
}




