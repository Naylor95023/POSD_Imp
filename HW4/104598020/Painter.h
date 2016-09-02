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

#include "Graphics.h"
#include "CompositeGraphics.h"
#include "SimpleGraphics.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
using namespace std;
class Painter:public QGraphicsItem
{
    public:
        Painter(Graphics * g,QWidget *_widget);
        virtual ~Painter();

        QWidget *widget;
        const QRectF *rectptr;
        qreal posx;
        qreal posy;
        qreal width;
        qreal heigh;
        QRectF boundingRect() const;//必須實做的virtual function，但目前用不到
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    protected:
    private:
        Graphics * g;
};

#endif // PAINTER_H
