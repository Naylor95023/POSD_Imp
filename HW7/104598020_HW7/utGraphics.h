#ifndef UTGRAPHICS_H_INCLUDED
#define UTGRAPHICS_H_INCLUDED

#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "util.h"
#include <string>
#include <vector>

TEST (CompositeGraphics, defaultBoundingBox) {
    CompositeGraphics g;
    // CompositeGraphics object has a default bounding box of
    // rectangle (0,0,0,0)
    LONGS_EQUAL(0,g.getBoundingBox().llx());
    LONGS_EQUAL(0,g.getBoundingBox().lly());
    LONGS_EQUAL(0,g.getBoundingBox().urx());
    LONGS_EQUAL(0,g.getBoundingBox().ury());
    LONGS_EQUAL(0,g.getBoundingBox().area());
}

TEST(SimpleGraphics, ctor_BoundingBox) {
    // SimpleGraphics object points to a Shape object
    Graphics *g1 = new SimpleGraphics(new Circle(0,0,1));
    Graphics *g2 = new SimpleGraphics(new Square(0,0,2));
    Graphics *g3 = new SimpleGraphics(new Rectangle(5,6,3,4));

    LONGS_EQUAL(-1,g1->getBoundingBox().llx());
    LONGS_EQUAL(-1,g1->getBoundingBox().lly());
    LONGS_EQUAL(1,g1->getBoundingBox().urx());
    LONGS_EQUAL(1,g1->getBoundingBox().ury());

    LONGS_EQUAL(0,g2->getBoundingBox().llx());
    LONGS_EQUAL(0,g2->getBoundingBox().lly());
    LONGS_EQUAL(2,g2->getBoundingBox().urx());
    LONGS_EQUAL(2,g2->getBoundingBox().ury());

    LONGS_EQUAL(5,g3->getBoundingBox().llx());
    LONGS_EQUAL(6,g3->getBoundingBox().lly());
    LONGS_EQUAL(8,g3->getBoundingBox().urx());
    LONGS_EQUAL(10,g3->getBoundingBox().ury());

}

TEST(SimpleGraphics, AddingGraphicsObjectShouldThrowException) {
    SimpleGraphics g(new Circle(0,0,1));
    // adding Graphics throws an exception
    try {
        g.add(new SimpleGraphics(new Circle(0,0,0)));
    } catch (std::string s) {
        CHECK(std::string("Cannot add child")==s);
    }
    // adding SimpleGraphics throws an exception
    try {
        g.add(new SimpleGraphics(new Circle(0,0,1)));
    } catch (std::string s) {
        CHECK(std::string("Cannot add child")==s);
    }

    // adding CompositeGraphics throws an exception
    try {
        g.add(new CompositeGraphics);
    } catch (std::string s) {
        CHECK(std::string("Cannot add child")==s);
    }
}

TEST(CompositeGraphics, addingOneChild) {
    CompositeGraphics g;

    try {
        g.add(new SimpleGraphics(new Circle(0,0,2)));
    } catch (std::string s) {
        FAIL("Should not throw exception");
    }

    LONGS_EQUAL(16,g.getBoundingBox().area());
}

TEST(CompositeGraphics, addingTwoChildrenAndGetBoundingBox) {
    CompositeGraphics g;

    g.add(new SimpleGraphics(new Circle(0,0,1)));
    g.add(new SimpleGraphics(new Square(-2,-2,2)));

    LONGS_EQUAL(-2,g.getBoundingBox().llx());
    LONGS_EQUAL(-2,g.getBoundingBox().lly());
    LONGS_EQUAL(1,g.getBoundingBox().urx());
    LONGS_EQUAL(1,g.getBoundingBox().ury());
}

TEST(CompositeGraphics, SimpleAndCompositeChildrenAndGetBoundingBox) {
    CompositeGraphics g;
    SimpleGraphics r(new Rectangle (-1,-1,1,3));

    g.add(new SimpleGraphics(new Circle(0,0,1)));
    g.add(new SimpleGraphics(new Square(-2,-2,2)));
    CompositeGraphics h;
    h.add(&g);
    h.add(&r);

    LONGS_EQUAL(-2,h.getBoundingBox().llx());
    LONGS_EQUAL(-2,h.getBoundingBox().lly());
    LONGS_EQUAL(1,h.getBoundingBox().urx());
    LONGS_EQUAL(2,h.getBoundingBox().ury());

}


#endif // UTGRAPHICS_H_INCLUDED
