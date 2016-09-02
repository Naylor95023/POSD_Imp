#ifndef UTHW3_H_INCLUDED
#define UTHW3_H_INCLUDED
#include "GraphicsFactory.h"
#include <string>
using namespace std;

//1.
TEST(buildGraphicsFromFile, file_not_exist) {
    GraphicsFactory gf;
    try{
        gf.buildGraphicsFromFile("FilenotExist.txt");
        //cout << "get file";
    }catch(string s){
        //cout << "exception detection";
        CHECK(s == string("File not exist!!!"))
    }
}

//2.
TEST(buildGraphicsFromFile, correctly_construct) {
    GraphicsFactory gf;
    Graphics * result;

     try{
        result = gf.buildGraphicsFromFile("f1.txt");
    }catch(string s){
        CHECK(s == string("File not exist!!!"))
    }
    DescriptionVisitor dv;
    result -> accept(dv);
    string ans("Comp R(-2,-2,3,4)\n");
    ans += string("  Comp R(-2,-2,3,3)\n");
    ans += string("    C(0,0,1)\n");
    ans += string("    S(-2,-2,2)\n");
    ans += string("  R(-1,-1,1,3)\n");
    CHECK(dv.getDescription() == ans);
    //cout << dv.getDescription();
}

//3.
TEST(fileContentsAsString, FileAsString){
    GraphicsFactory gf;
    string ans("Comp R(-2,-2,3,4)\n");
    ans += string("  Comp R(-2,-2,3,3)\n");
    ans += string("    C(0,0,1)\n");
    ans += string("    S(-2,-2,2)\n");
    ans += string("  R(-1,-1,1,3)\n");
    CHECK(gf.fileContentsAsString("f1.txt") == ans);

}

//4.
TEST(extractGraphicsFromOneLine, correct_simpleFraphics){
    GraphicsFactory gf;
    Graphics * result;
    DescriptionVisitor dvR,dvS,dvC;
    int level = 0;

    //rec
    string s("R(0,0,1,1)");
    result = gf.extractGraphicsFromOneLine(s, level);
    result -> accept(dvR);
    string ans("R(0,0,1,1)\n");
    CHECK(dvR.getDescription() == ans);
    LONGS_EQUAL(level,0);

    //squ
    s = "    S(0,0,1)";
    result = gf.extractGraphicsFromOneLine(s, level);
    result -> accept(dvS);
    ans = "S(0,0,1)\n";
    CHECK(dvS.getDescription() == ans);
    LONGS_EQUAL(level,2);

    //cir
    s = "  C(0,0,1)";
    result = gf.extractGraphicsFromOneLine(s, level);
    result -> accept(dvC);
    ans = "C(0,0,1)\n";
    CHECK(dvC.getDescription() == ans);
    LONGS_EQUAL(level,1);

}

//5
TEST(extractGraphicsFromOneLine, correct_compsiteFraphics){
    GraphicsFactory gf;
    Graphics * result;
    DescriptionVisitor dv;
    int level = 0;

    //comp
    string s("            Comp R(0,0,1,1)");
    result = gf.extractGraphicsFromOneLine(s, level);
    result -> accept(dv);
    string ans("Comp R(0,0,0,0)\n");
    CHECK(dv.getDescription() == ans);
    LONGS_EQUAL(level,6);

}

//6
TEST(compose, pop_until_level_equal){
    GraphicsFactory gf;
    DescriptionVisitor dv1,dv2;

    gf.getStack() -> push(make_pair(new CompositeGraphics(), 0));
    gf.getStack() -> push(make_pair(new CompositeGraphics(), 1));
    gf.getStack() -> push(make_pair(new SimpleGraphics(new Circle(0, 0, 1)), 2));
    gf.getStack() -> push(make_pair(new SimpleGraphics(new Square(-2, -2, 2)), 2));
    LONGS_EQUAL(gf.getStack() -> size(),4);
    gf.compose();
    LONGS_EQUAL(gf.getStack() -> size(),2);

    string ans("Comp R(-2,-2,3,3)\n");
    ans += string("  C(0,0,1)\n");
    ans += string("  S(-2,-2,2)\n");
    gf.getStack() -> top().first -> accept(dv1);
    CHECK(dv1.getDescription() == ans);

    gf.getStack() -> pop();
    gf.getStack() -> top().first -> accept(dv2);
    ans = "Comp R(0,0,0,0)\n";
    CHECK(dv2.getDescription() == ans);

}

//7
TEST(compose, pop_until_level_equal_end){
    GraphicsFactory gf;
    DescriptionVisitor dv1,dv2;

    gf.getStack() -> push(make_pair(new CompositeGraphics(), 0));
    gf.getStack() -> push(make_pair(new CompositeGraphics(), 1));
    gf.getStack() -> push(make_pair(new SimpleGraphics(new Circle(0, 0, 1)), 2));
    gf.getStack() -> push(make_pair(new SimpleGraphics(new Square(-2, -2, 2)), 2));
    LONGS_EQUAL(gf.getStack() -> size(),4);
    gf.compose();
    LONGS_EQUAL(gf.getStack() -> size(),2);
    gf.getStack() -> push(make_pair(new SimpleGraphics(new Rectangle(-1, -1, 1, 3)), 1));
    LONGS_EQUAL(gf.getStack() -> size(),3);

    string ans("R(-1,-1,1,3)\n");
    gf.getStack() -> top().first -> accept(dv1);
    CHECK(dv1.getDescription() == ans);

    gf.compose();
    gf.getStack() -> top().first -> accept(dv2);
    ans = string("Comp R(-2,-2,3,4)\n");
    ans += string("  Comp R(-2,-2,3,3)\n");
    ans += string("    C(0,0,1)\n");
    ans += string("    S(-2,-2,2)\n");
    ans += string("  R(-1,-1,1,3)\n");
    CHECK(dv2.getDescription() == ans);

}
#endif // UTHW3_H_INCLUDED
