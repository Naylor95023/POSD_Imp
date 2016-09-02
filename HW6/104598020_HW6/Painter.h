#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <QPainter>
#include <QGraphicsItem>
#include <QAction>
#include <QStaticText>
#include "qwidget.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QColor>
#include <QPen>
#include <QPointF>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

#include <stdio.h>
#include <vector>
#include "Presentation.h"
#include "Graphics.h"
#include "CompositeGraphics.h"
#include "SimpleGraphics.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class Presentation;

using namespace std;
class Painter:public QGraphicsItem
{
    public:
        Painter(Graphics * g, QWidget *_widget, Presentation * p);
        virtual ~Painter();

        QWidget * widget;
        const QRectF * rectptr;
        qreal posx;
        qreal posy;
        qreal width;
        qreal heigh;

        void setLocation(QPointF x){this->setPos(_location += x);}
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
        bool IsSelected(){return isSelected;}
        void setSelected();
        void setNotSelected();
    protected:

        virtual QRectF boundingRect() const; ///< must be re-implemented in this class to provide the diminsions of the box to the QGraphicsView
        virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events
        virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events
        virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );///< re-implemented to capture events
        virtual void mousePressEvent (QGraphicsSceneMouseEvent * event );///< re-implemented to capture events
        virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );///< re-implemented to capture events
        virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);///< re-implemented to capture events
        virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);///< re-implemented to capture events

        QColor  _outterborderColor; ///< the hover event handlers will toggle this between red and black
        QPen    _outterborderPen; ///< the pen is used to paint the red/black border
        QPointF _location;
        QPointF _dragStartLocation;
        QPointF _dragStart;
        qreal   _bwidth;
        qreal   _bheight;
    private:
        Graphics * g;
        Presentation * p;
        bool isSelected;

};

#endif // PAINTER_H
