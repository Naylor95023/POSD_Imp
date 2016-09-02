#ifndef DRAWVISTOR_H_INCLUDED
#define DRAWVISTOR_H_INCLUDED

#include "GraphicsVisitor.h"
#include "Painter.h"

#include <QGraphicsScene>
#include <QtWidgets/QMainWindow>
#include <vector>


class drawVistor : public GraphicsVisitor{
public:
    drawVistor(QWidget * w, QGraphicsScene * s);
    void visitSimpleGraphics(SimpleGraphics *sg);
    void visitCompositeGraphics(CompositeGraphics *cg);
    void enter(){}
    void leave(){}
    void setScene();
private:
    std::vector<Painter *> painters;
    QGraphicsScene *scene;
    QWidget *widget;
};


#endif // DRAWVISTOR_H_INCLUDED
