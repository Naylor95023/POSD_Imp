#ifndef DESCRIPTIONVISITOR_H_INCLUDED
#define DESCRIPTIONVISITOR_H_INCLUDED

#include <vector>
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "GraphicsVisitor.h"

class DescriptionVisitor : public GraphicsVisitor {
public:
    DescriptionVisitor():d("") {}
    void visitSimpleGraphics(SimpleGraphics *s);
    void visitCompositeGraphics(CompositeGraphics *c);
    std::string getDescription();
    //int area() {return a;}
private:
    std::string d;
    int level = 0;
    std::vector<int> childs;
};

#endif // DESCRIPTIONVISITOR_H_INCLUDED
