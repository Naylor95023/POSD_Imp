#ifndef UTEXTRACTGRAPHICS_H_INCLUDED
#define UTEXTRACTGRAPHICS_H_INCLUDED

#include "cppunitlite/TestHarness.h"
#include <string>
#include "util.h"

using namespace std;

TEST (fileContentsAsString, first) {
	std::string contents = fileContentsAsString("f1.txt");

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,("f1.txt");
	int level;
	Graphics * graphics = extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (0 != graphics);

    std::string ans("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (1, level);
	CHECK (0 != graphics);

    ans = string("");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (2, level);
	CHECK (string("C(0,0,1)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (2, level);
	CHECK (string("S(-2,-2,2)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (1, level);
	CHECK (string("R(-1,-1,1,3)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    CHECK(ans == contents);
    CHECK(contents.empty());2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    int pos=0;
    pos=contents.find_first_of(newline, pos);
    LONGS_EQUAL(17,pos);
}

TEST (extractGraphicsFromOneLine, first) {
	string contents = fileContentsAsString("f1.txt");
	int level;
	Graphics * graphics = extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (0 != graphics);

    std::string ans("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (1, level);
	CHECK (0 != graphics);

    ans = string("");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (2, level);
	CHECK (string("C(0,0,1)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (2, level);
	CHECK (string("S(-2,-2,2)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==contents);

    graphics = extractGraphicsFromOneLine(contents, level);
    LONGS_EQUAL (1, level);
	CHECK (string("R(-1,-1,1,3)")==static_cast<SimpleGraphics *>(graphics)->shape()->describe());

    ans = string("");
    CHECK(ans == contents);
    CHECK(contents.empty());
}

TEST (extractGraphicsFromOneLine, sq1) {
	string contents = fileContentsAsString("sq1.txt");
	int level;
	Graphics * graphics = extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (string("S(-2,-2,2)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());
}

TEST (extractGraphicsFromOneLine, cir1) {
	string contents = fileContentsAsString("cir1.txt");
	int level;
	Graphics * graphics = extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (string("C(0,0,1)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());
}

TEST (extractGraphicsFromOneLine, rec1) {
	string contents = fileContentsAsString("rec1.txt");
	int level;
	Graphics * graphics = extractGraphicsFromOneLine(contents, level);
	LONGS_EQUAL (0, level);
	CHECK (string("R(-1,-1,1,3)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());
}

TEST (extractGraphicsFromOneLine, sh1) {
	string contents = fileContentsAsString("sh1.txt");
    try {
        int level;
        extractGraphicsFromOneLine(contents, level);
        FAIL("Should not reach here");
    } catch (string s) {
        CHECK (string("undefined graphics") == s);
    }
}

TEST (buildGraphicsFromFile, simple) {
    Graphics * graphics = buildGraphicsFromFile("rec1.txt");
    CHECK (string("R(-1,-1,1,3)") == static_cast<SimpleGraphics *>(graphics)->shape()->describe());
}

TEST (buildGraphicsFromFile, composite) {
    Graphics * graphics = buildGraphicsFromFile("f1.txt");

    DescriptionVisitor dv;
    graphics->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==dv.getDescription());
}
#endif // UTEXTRACTGRAPHICS_H_INCLUDED
