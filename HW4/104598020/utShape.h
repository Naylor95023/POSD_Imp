#ifndef UTSHAPE_H_INCLUDED
#define UTSHAPE_H_INCLUDED

#include "cppunitlite/TestHarness.h"
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "util.h"
#include <vector>

TEST(Shapes0915, first_success) {
    CHECK(true);
}

TEST(Circle, area) {
    Circle circle(0,0,1);
    LONGS_EQUAL(3,circle.area());
}

TEST(areaSum, Circle) {
    Circle c1(0,0,1), c2(0,0,2),c3(0,0,3);
    std::vector<Shape *> v;
    v.push_back(&c1);
    v.push_back(&c2);
    v.push_back(&c3);
    LONGS_EQUAL(42,areaSum(v));
}

TEST(areaSum, Square) {
    Square s1(0,0,1), s2(0,0,2),s3(0,0,3);
    std::vector<Shape *> v;
    v.push_back(&s1);
    v.push_back(&s2);
    v.push_back(&s3);
    LONGS_EQUAL(14,areaSum(v));
}

TEST(areaSum, Rectangle) {
    Rectangle r1(0,0,1,2), r2(0,0,2,3),r3(0,0,3,4);
    std::vector<Shape *> v;
    v.push_back(&r1);
    v.push_back(&r2);
    v.push_back(&r3);
    LONGS_EQUAL(20,areaSum(v));
}

TEST(areaSum, allShapes) {
    Circle c(0,0,1);
    Square s(0,0,2);
    Rectangle r(0,0,3,4);
    std::vector<Shape *> v;
    v.push_back(&c);
    v.push_back(&s);
    v.push_back(&r);
    LONGS_EQUAL(19,areaSum(v));
}

TEST(Shape, getBoundingBox) {
    Circle c(0,0,1);
    Rectangle r(1,1,1,2);
    Square s(0,0,3);

    // bounding box of a shape is a rectangle
    LONGS_EQUAL(-1,c.getBoundingBox().llx());
    LONGS_EQUAL(-1,c.getBoundingBox().lly());
    LONGS_EQUAL(1,c.getBoundingBox().urx());
    LONGS_EQUAL(1,c.getBoundingBox().ury());

    LONGS_EQUAL(1,r.getBoundingBox().llx());
    LONGS_EQUAL(1,r.getBoundingBox().lly());
    LONGS_EQUAL(2,r.getBoundingBox().urx());
    LONGS_EQUAL(3,r.getBoundingBox().ury());

    LONGS_EQUAL(0,s.getBoundingBox().llx());
    LONGS_EQUAL(0,s.getBoundingBox().lly());
    LONGS_EQUAL(3,s.getBoundingBox().urx());
    LONGS_EQUAL(3,s.getBoundingBox().ury());

    LONGS_EQUAL(4,c.getBoundingBox().area());
    LONGS_EQUAL(2,r.getBoundingBox().area());
    LONGS_EQUAL(9,s.getBoundingBox().area());
}



#endif // UTSHAPE_H_INCLUDED
