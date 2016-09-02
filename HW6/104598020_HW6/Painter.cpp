#include "Painter.h"
#include <typeinfo>

Painter::Painter(Graphics * g, QWidget *_widget, Presentation * p):
    _outterborderColor(Qt::black),_outterborderPen(),
    _location(0,0),_dragStart(0,0),isSelected(false)
{
    //ctor
    this->g = g;
    this->p = p;
    //get Graphics and set x,y,w,h
    int width = g->getBoundingBox().urx()- g->getBoundingBox().llx();
    int heigh = g->getBoundingBox().ury()- g->getBoundingBox().lly();
    posx = g->getBoundingBox().llx();
    posy = g->getBoundingBox().lly();
    _bwidth = this->width = width;
    _bheight = this->heigh = heigh;
    widget = _widget;
   /////////////////////////////////////////////////////////////////
    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);
    this->setAcceptHoverEvents(true);
}

Painter::~Painter(){//dtor

}

//if g is simple , cast to simple *,judge is circle
//else paint by blue pen
void Painter::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    if(typeid((*g)) == typeid(SimpleGraphics)){
        QPen pen(Qt::blue);
        painter->setPen(pen);
        QPainterPath path;
        SimpleGraphics * sg = reinterpret_cast<SimpleGraphics *>(g);
        if(typeid(*sg->shape()) == typeid(Circle)){
            path.addEllipse(QRectF(posx, posy, width, heigh));
            painter->drawEllipse(posx, posy, width, heigh);
            painter->fillPath(path, Qt::blue);
        }else{
            path.addRect(QRectF(posx, posy, width, heigh));
            painter->drawRect(posx, posy, width, heigh);
            painter->fillPath(path, Qt::blue);
        }
    }else{
        QPen pen(Qt::green);
        painter->setPen(pen);
        painter->drawRect(posx, posy, width, heigh);
    }
    /////////////////////////////////////////////////////////////////
     //draw upper left corner
    _outterborderPen.setColor( _outterborderColor );
    _outterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(_outterborderPen);
    painter->drawRect(posx, posy, width, heigh);
}


void Painter::setSelected(){
    isSelected = true;
    _outterborderColor = Qt::red;
    this->update(posx, posy, _bwidth, _bheight);

}

void Painter::setNotSelected(){
    isSelected = false;
    _outterborderColor = Qt::black;
    this->update(posx, posy, _bwidth, _bheight);
}

void Painter::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void Painter::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void Painter::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    event->setAccepted(true);// tell the base class we are handling this event
    this->setPos(_location);
    int moveX = _location.x() - _dragStartLocation.x();
    int moveY = _location.y() - _dragStartLocation.y();

    //if No moving change state else update data
    if(moveX == 0 && isSelected == true){
        _outterborderColor = Qt::black;
        isSelected = false;
        //DeSelected cg childs
        if(typeid((*g)) == typeid(CompositeGraphics)){
            CompositeGraphics * cg = reinterpret_cast<CompositeGraphics *>(g);
            p->DeSelectedChild(cg);
        }
        cout << "No Moving" << endl;
    }
    else{
        isSelected = true;
        p->moveGraphics(g, moveX, moveY);
        cout << "New->X:" << _location.x() << "/Y:" << _location.y() << endl;
    }
    this->update(posx, posy,_bwidth,_bheight);
}

void Painter::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    // allow the user to drag the box, capture the starting position on mouse-down
    event->setAccepted(true);
    _dragStart = event->pos();
    _dragStartLocation = _location;
//     cout << "Org->X:" << _dragStartLocation.x() << "/Y:" << _dragStartLocation.y() << endl;
     cout << "Mouse X : " << _dragStart.x() << " /Y : " << _dragStart.y()<< endl;

    //selected and change color
    if(!isSelected){
        _outterborderColor = Qt::red;
        //Selected cg child
        if(typeid((*g)) == typeid(CompositeGraphics)){
            CompositeGraphics * cg = reinterpret_cast<CompositeGraphics *>(g);
            _dragStart += this->pos();
            p->SelectedChild(cg, _dragStart.x(), _dragStart.y());
        }
    }

    this->update(posx, posy, _bwidth, _bheight);
}

void Painter::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    // user have moved the mouse, move the location of the box
    QPointF newPos = event->pos() ;
    g->ChangePainter((newPos - _dragStart));
}

void Painter::hoverLeaveEvent ( QGraphicsSceneHoverEvent * )
{
    // return the box color to black when the mouse is no longer hovering
}

void Painter::hoverEnterEvent ( QGraphicsSceneHoverEvent * )
{
    // draw the box in red if the mouse is hovering over it
}
// boundingRect must be re-implemented from the base class to provide the scene with
// size info about this custom GraphicsItem
QRectF Painter::boundingRect() const
{
    return QRectF(posx, posy, _bwidth, _bheight);
}

