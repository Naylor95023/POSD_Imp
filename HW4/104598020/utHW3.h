#ifndef UTHW3_H_INCLUDED
#define UTHW3_H_INCLUDED

#include "cppunitlite/TestHarness.h"
#include <string>
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "SimpleGraphics.h"
#include "CompositeGraphics.h"
#include "util.h"
#include <string>
#include <vector>
#include "AreaVisitor.h"
#include "DescriptionVisitor.h"
#include "GraphicsFactory.h"

using namespace std;

TEST (GraphicsFactory, compose_1) {
    GraphicsFactory gf;
    gf.pda.push(make_pair (0,new CompositeGraphics));
    gf.pda.push(make_pair (1,new CompositeGraphics));
    gf.pda.push(make_pair (2,new SimpleGraphics(new Circle(0,0,1))));
    gf.pda.push(make_pair (2,new SimpleGraphics(new Square(-2,-2,2))));

    gf.compose();

    LONGS_EQUAL(-2,get<1>(gf.pda.top())->getBoundingBox().llx());
    LONGS_EQUAL(-2,get<1>(gf.pda.top())->getBoundingBox().lly());
    LONGS_EQUAL(1,get<1>(gf.pda.top())->getBoundingBox().urx());
    LONGS_EQUAL(1,get<1>(gf.pda.top())->getBoundingBox().ury());
}

TEST (GraphicsFactory, compose_2) {
    GraphicsFactory gf;
    gf.pda.push(make_pair (0,new CompositeGraphics));
    CompositeGraphics * cg = new CompositeGraphics;
    cg->add(new SimpleGraphics(new Circle(0,0,1)));
    cg->add(new SimpleGraphics(new Square(-2,-2,2)));
    gf.pda.push(make_pair (1,cg));
    gf.pda.push(make_pair (1,new SimpleGraphics(new Rectangle(-1,-1,1,3))));
    gf.compose();

    Graphics *h = get<1>(gf.pda.top());
    DescriptionVisitor dv;
    h->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==dv.getDescription());
}

TEST (GraphicsFactory, fileContentsAsString) {
    GraphicsFactory gf;
	std::string contents = gf.fileContentsAsString("f1.txt");

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);
}

TEST (GraphicsFactory, extractGraphicsFromOneLine_sq) {
    GraphicsFactory gf;
    string contents = gf.fileContentsAsString("sq1.txt");
	int level;
	Graphics * graphics = gf.extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (string("S(-2,-2,2)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());

}

TEST (GraphicsFactory, extractGraphicsFromOneLine_cir) {
    GraphicsFactory gf;
	string contents = gf.fileContentsAsString("cir1.txt");
	int level;
	Graphics * graphics = gf.extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (string("C(0,0,1)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());

}

TEST (GraphicsFactory, extractGraphicsFromOneLine_rect) {
    GraphicsFactory gf;
    string contents = gf.fileContentsAsString("rec1.txt");
	int level;
	Graphics * graphics = gf.extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (string("R(-1,-1,1,3)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());
}

TEST (GraphicsFactory, extractGraphicsFromOneLine_composite) {
    GraphicsFactory gf;
    string contents = gf.fileContentsAsString("f1.txt");
	int level;
	Graphics * graphics = gf.extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (0 != graphics);

    std::string ans("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = gf.extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (1, level);
	CHECK (0 != graphics);

    ans = string("");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = gf.extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (2, level);
	CHECK (string("C(0,0,1)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = gf.extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (2, level);
	CHECK (string("S(-2,-2,2)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = gf.extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (1, level);
	CHECK (string("R(-1,-1,1,3)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    CHECK(ans == contents);
    CHECK(contents.empty());
}

TEST (GraphicsFactory, buildGraphicsFromFile_simple) {
    GraphicsFactory gf;
    Graphics * graphics = gf.buildGraphicsFromFile("rec1.txt");
    CHECK (string("R(-1,-1,1,3)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());
}

TEST (GraphicsFactory, buildGraphicsFromFile_composite) {
    GraphicsFactory gf;
    Graphics * graphics = gf.buildGraphicsFromFile("f1.txt");

    DescriptionVisitor dv;
    graphics->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==dv.getDescription());
}

#endif // UTHW3_H_INCLUDED
