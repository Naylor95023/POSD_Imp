#ifndef DRAWVISTOR_H_INCLUDED
#define DRAWVISTOR_H_INCLUDED

#include "GraphicsVisitor.h"
#include "Painter.h"
#include "Presentation.h"

#include <QGraphicsScene>
#include <QtWidgets/QMainWindow>
#include <vector>


class drawVistor : public GraphicsVisitor{
public:
    drawVistor(QWidget * w, QGraphicsScene * s, Presentation * p);
    void visitSimpleGraphics(SimpleGraphics *sg);
    void visitCompositeGraphics(CompositeGraphics *cg);
    void enter(){}
    void leave(){}
    void setScene();
private:
    std::vector<Painter *> painters;
    QGraphicsScene *scene;
    QWidget *widget;
    Presentation * present;
};


#endif // DRAWVISTOR_H_INCLUDED
