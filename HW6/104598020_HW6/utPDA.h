#ifndef UTPDA_H_INCLUDED
#define UTPDA_H_INCLUDED

#include "cppunitlite/TestHarness.h"
#include <stack>
#include <string>
#include <tuple>

using namespace std;

class MyStack: public stack<int> {
public:
    MyStack():stack<int>(){}
    void pop() {
        if (stack<int>::empty())
            throw string("pop on empty");
        else
            stack<int>::pop();
    }
};

TEST (stack, first) {
    stack<int> pda;
    pda.push(0);
    pda.push(2);
    pda.push(2);
    pda.push(4);
    pda.push(4);
    pda.push(2);
    pda.push(2);
    pda.push(4);
    pda.push(4);

    LONGS_EQUAL(9, pda.size());
    LONGS_EQUAL(4, pda.top());
    pda.pop();

    LONGS_EQUAL(8, pda.size());
    LONGS_EQUAL(4, pda.top());
    pda.pop();

    LONGS_EQUAL(7, pda.size());
    LONGS_EQUAL(2, pda.top());
    pda.pop();

    for (int i=0; i<5; ++i)
        pda.pop();

    LONGS_EQUAL(1, pda.size());
    LONGS_EQUAL(0, pda.top());
    pda.pop();

    CHECK(pda.empty());
    LONGS_EQUAL(0, pda.size());
}

TEST (stack, poponempty) {
    stack<int> pda;
    CHECK(pda.empty());
    LONGS_EQUAL(0, pda.size());

    pda.pop();
}

TEST (MyStack, poponempty) {
    MyStack pda;
    CHECK(pda.empty());
    LONGS_EQUAL(0, pda.size());
    try {
        pda.pop();
        FAIL("exception not thrown");
    } catch (string s) {
        CHECK (string("pop on empty")==s);
    }
}

TEST (tuple, first) {
    auto gr = make_tuple (10,string("Comp"),string("R(-1-1,2,3)"));
    LONGS_EQUAL(10,get<0>(gr));
    CHECK(string("Comp")==get<1>(gr));
    CHECK(string("R(-1-1,2,3)")==get<2>(gr));
}

TEST (stack, triple) {
    stack<tuple<int, string, string>> pda;
    pda.push(make_tuple (0,string("Comp"),string("R(-2,-2,3,4)")));
    pda.push(make_tuple (2,string("Comp"),string("R(-2,-2,3,3)")));
    pda.push(make_tuple (4,string("C"),string("(0,0,1)")));
    pda.push(make_tuple (4,string("S"),string("(-2,-2,2)")));
    pda.push(make_tuple (2,string("R"),string("(-1,-1,1,3)")));
}

TEST (compose, first) {
    stack<pair<int, Graphics *>> pda;
    pda.push(make_pair (0,new CompositeGraphics));
    pda.push(make_pair (1,new CompositeGraphics));
    pda.push(make_pair (2,new SimpleGraphics(new Circle(0,0,1))));
    pda.push(make_pair (2,new SimpleGraphics(new Square(-2,-2,2))));

    compose(pda);

    LONGS_EQUAL(-2,get<1>(pda.top())->getBoundingBox().llx());
    LONGS_EQUAL(-2,get<1>(pda.top())->getBoundingBox().lly());
    LONGS_EQUAL(1,get<1>(pda.top())->getBoundingBox().urx());
    LONGS_EQUAL(1,get<1>(pda.top())->getBoundingBox().ury());

    pda.push(make_pair (1,new SimpleGraphics(new Rectangle(-1,-1,1,3))));
    compose(pda);

    Graphics *h = get<1>(pda.top());
    DescriptionVisitor dv;
    h->accept(dv);

    std::string ans("Comp R(-2,-2,3,4)\n");
    ans += std::string("  Comp R(-2,-2,3,3)\n");
    ans += std::string("    C(0,0,1)\n");
    ans += std::string("    S(-2,-2,2)\n");
    ans += std::string("  R(-1,-1,1,3)\n");
    CHECK(ans==dv.getDescription());
}
#endif // UTPDA_H_INCLUDED
