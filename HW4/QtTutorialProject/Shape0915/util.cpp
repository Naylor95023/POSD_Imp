#include "util.h"
#include <fstream>
#include "CompositeGraphics.h"
#include "SimpleGraphics.h"
#include "Circle.h"
#include "Square.h"
#include "Rectangle.h"
#include <sstream>
#include <stack>
#include <utility>

using namespace std;

int areaSum(std::vector<Shape *> v) {
    int sum = 0;

    for(auto e : v)
        sum += e->area();
    return sum;
}
